#ifndef __INDEX_H__
#define __INDEX_H__

#include <iostream>
#include <vector>
#include <map>

struct Entry
{
    size_t count;
    size_t doc_id;

    bool operator ==(const Entry& other) const;
};


class InvertedIndex
{
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    int CountWordEntry(std::string& text, std::string word);
    bool case_sensetive = false;

public:
    InvertedIndex() = default;

    void EngineCaseSensetive(bool case_sensetive);
    void UpdateDocsBase(std::vector<std::string> input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);
};

#endif