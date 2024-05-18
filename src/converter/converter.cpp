#include <json.hpp>
#include <fstream>
#include <filesystem>

#include "converter.h"

using nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextFromDocs()
{
    std::vector<std::string> textFromDocs;
    json j;
    std::ifstream file(this->configFileName);

    if(!file.is_open())
        throw std::runtime_error("Unable to open config file.");
    file >> j;
    file.close();

    for(std::string doc : j["files"])
    {
        std::string line, content;
        std::ifstream file(doc);

        if(!file.is_open())
            throw std::runtime_error("Unable to open document. Path: " + doc);

        while(std::getline(file, line))
            content += line + "\n";

        textFromDocs.push_back(content);
        file.close();
    }

    return textFromDocs;
}

int ConverterJSON::GetResponsesLimit()
{
    json j;

    std::ifstream file(this->configFileName);
    if(!file.is_open())
        throw std::runtime_error("Unable to open config file.");

    file >> j;
    file.close();

    return j["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> vs;
    return vs;
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>>answers)
{

}