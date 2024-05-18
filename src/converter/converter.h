#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <vector>
#include <string>
#include <iostream>

struct Entry
{
    size_t doc_id;
    size_t count;
};

class ConverterJSON
{
private:
    const std::string configFileName = "config.json";
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;

public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextFromDocs();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void PutAnswers(std::vector<std::vector<std::pair<int, float>>>answers);
};

#endif