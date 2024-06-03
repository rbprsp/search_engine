//class header
#include "inverted.h"

//STL
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>
#include <optional>
#include <atomic>

//Entry operator overload
bool Entry::operator==(const Entry& other) const
{
    return (doc_id == other.doc_id && count == other.count);
}

void InvertedIndex::UpdateDocsBase(std::vector<std::string> input_docs)
{
    if(docs.size() != 0)
        docs.erase(docs.begin(), docs.end());
    for(auto& doc : input_docs)
    {
        std::ifstream file(doc);
        if(file.is_open())
        {
            std::string line = "", content = "";
            while(std::getline(file, line))
                content += line + "\n";
            this->docs.push_back(content);
            file.close();
        }
        else
        {
            if(doc.size() != 0 )
                this->docs.push_back(doc);
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> result;  // this will be returned
    std::vector<std::thread> threads;
    std::mutex result_mutex;

    int docs_size = this->docs.size(); // get docs size | not calling .size() on every loop cycle
    std::vector<std::optional<Entry>> temp_results(docs_size);

    auto check_document = [this, &word, &temp_results](int i)
    {
        int word_count = this->CountWordEntry(this->docs.at(i), word);
        if(word_count != 0)
        {
            {
            Entry e{};
            e.doc_id = i;
            e.count = word_count;
            temp_results[i] = e;
            }
        }
    };

    // run threads
    for(int i = 0; i < docs_size; ++i)
        threads.emplace_back(check_document, i);

    // wait for thread
    for(auto& thread : threads)
    {
        if(thread.joinable())
            thread.join();
    }

    // collect non-zero data
    for(const auto& opt_entry : temp_results)
    {
        if(opt_entry.has_value())
        {
            std::lock_guard<std::mutex> lock(result_mutex);
            result.push_back(opt_entry.value());
        }
    }

    std::lock_guard<std::mutex> lock(result_mutex);

    return result;
}


int InvertedIndex::CountWordEntry(std::string& text, std::string word)
{
    std::string lower_text = text, lower_word = word;
    std::vector<std::thread> threads;
    std::atomic_int result(0);
    
    if(this->case_sensitive)
    {
        std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);
        std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
    }

    std::istringstream iss(word);
    std::vector<std::string> words;
    std::string temp;

    while (iss >> temp)
        words.push_back(temp);

    auto words_cout = words.size();

    auto entries = [&lower_text, &result](const std::string _w)
    {
        std::regex word_regex("\\b" + _w + "\\b");
        auto words_begin = std::sregex_iterator(lower_text.begin(), lower_text.end(), word_regex);
        auto words_end = std::sregex_iterator();

        result += std::distance(words_begin, words_end);
    };

    for(const auto& w : words)
        threads.emplace_back(entries, w);

    for(auto &thread : threads)
        thread.join();

    return result.load();
}

void InvertedIndex::EnableCaseSensitive()  {    this->case_sensitive = true;    }
void InvertedIndex::DisableCaseSensitive() {    this->case_sensitive = false;   }