#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "inverted.h"
#include "relative.h"

class ConverterJSON
{
private:
    //config
    const std::string config_file_name = "config.json";
    const std::string requests_file_name = "requests.json";
    const std::string answers_file_name = "answers.json";
    const std::string search_engine_version = "1.0.0";
    const std::string searhc_engine_name = "search_engine";

    //data from files
    std::vector<std::string> docs;
    std::vector<std::string> requests;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
    int max_responses = 5;

    //logger
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink;
    std::shared_ptr<spdlog::logger> logger;

    

    bool readAllDocs();
    bool readResponLimit();
    bool readRequests();

public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextFromDocs();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void PutAnswers(std::vector<std::vector<RelativeIndex>> answers);

    void GenerateConfig();

    bool ValidateConfig();

    static inline const std::string log_file_name = "logs/logs.txt";
};

#endif