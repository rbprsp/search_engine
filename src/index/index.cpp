//class header
#include "index.h"

//STL
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>

//Entry operator overload
bool Entry::operator==(const Entry& other) const
{
    return (doc_id == other.doc_id && count == other.count);
}

void InvertedIndex::UpdateDocsBase(std::vector<std::string> input_docs)
{
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
            this->docs.push_back(doc);
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> result;
    std::vector<std::thread> threads;
    std::mutex result_mutex;

    auto check_document = [this, &result, &word, &result_mutex](int i)
    {
        int word_count = this->CountWordEntry(this->docs.at(i), word);
        if(word_count != 0)
        {
            Entry e{};
            e.doc_id = i;
            e.count = word_count;
            std::lock_guard<std::mutex> lock(result_mutex);
            result.push_back(e);
        }
    };

    // run threads
    int docs_size = this->docs.size(); // get docs size | not calling .size() on every loop cycle

    for(int i = 0; i < docs_size; ++i)
        threads.emplace_back(check_document, i);

    // wait for threads
    for(auto& thread : threads)
    {
        if(thread.joinable())
            thread.join();
    }

    return result;
}


int InvertedIndex::CountWordEntry(std::string& text, std::string word)
{
    std::string lower_text = "", lower_word = "";
    if(true)
    {
        lower_text = text;
        lower_word = word;

        std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);
        std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
    }

    std::regex word_regex("\\b" + lower_word + "\\b");
    auto words_begin = std::sregex_iterator(lower_text.begin(), lower_text.end(), word_regex);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}
//todo
// void InvertedIndex::EngineCaseSensitive(bool case_sensitive)
// {
//     this->case_sensetive = case_sensetive;
// }