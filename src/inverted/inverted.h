#ifndef __INVERTED_H__
#define __INVERTED_H__

#include <iostream>
#include <vector>
#include <map>

struct Entry
{
    size_t doc_id;
    size_t count;

    bool operator ==(const Entry& other) const;
};


class InvertedIndex
{
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    int CountWordEntry(std::string& text, std::string word);
    //bool is_case_sensitive = false;

public:
    InvertedIndex() = default;

    //void EngineCaseSensitive(bool case_sensitive);
    void UpdateDocsBase(std::vector<std::string> input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);
};

#endif