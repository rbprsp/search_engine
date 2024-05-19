//class header
#include "index.h"

//STL
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>

//Entry operator overload
bool Entry::operator==(const Entry& other) const
{
    return (doc_id == other.doc_id && count == other.count);
}

void InvertedIndex::UpdateDocsBase(std::vector<std::string> input_docs)
{
    this->docs.erase(this->docs.begin(), this->docs.end());
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
            continue;
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> result;
    for(int i = 0; i < this->docs.size(); i++)
    {
        Entry e;
        e.count = this->CountWordEntry(docs.at(i), word);
        e.doc_id = i;

        result.push_back(e);
    }

    return result;
}

int InvertedIndex::CountWordEntry(std::string& text, std::string word)
{
    std::string lower_text = "", lower_word = "";
    if(!case_sensetive)
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

void InvertedIndex::EngineCaseSensetive(bool case_sensetive)
{
    this->case_sensetive = case_sensetive;
}