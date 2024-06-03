#include <json.hpp>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <sstream>

#include "converter.h"

using nlohmann::json;

ConverterJSON::ConverterJSON()
{
    this->file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/logs.txt", true);
    this->logger = std::make_shared<spdlog::logger>("ConverterJSON", this->file_sink);

    spdlog::set_default_logger(this->logger);

    if(this->validateConfig())
    {
        if(!this->readAllDocs() || !this->readRequests() || !this->readResponLimit())
        {
            logger->critical("Error while parsing .json file."); 
            throw std::runtime_error("Unable to read configuration file.");
        }
    }
    else
    {
       logger->critical("Can't find config path | Can't validate .json format in config file."); 
       throw std::runtime_error("Unable to read configuration file.");
    }
}

bool ConverterJSON::validateConfig()
{
    json j;
    std::ifstream file(this->config_file_name);

    if(!file.is_open())
    {
        logger->critical("Unable to open config file.");
        return false;
    }

    logger->info("Config file was found.");

    try
    {
        file >> j;
        file.close();
        logger->info("Config file read successfully.");
    }
    catch(const std::exception& e)
    {
        logger->critical("Invalid .json format in config.json. Error: {}.", e.what());
        file.close();
        return false;
    }

    return true;
}

bool ConverterJSON::readAllDocs()
{
    json j;
    std::ifstream file(this->config_file_name);

    file >> j;
    file.close();

    namespace fs = std::filesystem;
    if(!j["files"].empty())
    {
        size_t file_counter = 0;
        for(std::string doc_id : j["files"])
        {
            fs::path doc = doc_id;
            if(!fs::exists(doc))
            {
                logger->warn("File not exists.");
                continue;
            }
            else
            {
                logger->info("Working on file.");
                std::ifstream file(doc);
                if(!file.is_open())
                {
                    logger->warn("Unable to open file.");
                    continue;
                }
                else
                {
                    this->docs.push_back(doc.string());
                    file_counter++;
                    file.close();
                }
            }
        }

        if(file_counter == 0)
        {
            logger->critical("No valid input files.");
            return false;
        }
    }
    else
    {
        logger->critical("No input files.");
        return false;
    }

    logger->info("Text from files was successfully added.");
    return true;
}

bool ConverterJSON::readResponLimit()
{
    json j;
    std::ifstream file(this->config_file_name);

    file >> j;
    file.close();

    if(!j["config"]["max_responses"].empty())
    {
        try
        {
            this->max_responses = j["config"]["max_responses"].get<int>();
            logger->info("max_responses value parsed successfully.");
            return true;
        }
        catch(const std::exception& e)
        {
            logger->critical("Error while parsing max_reponses value. Error {}.", e.what());
            return false;   
        }
    }

    return true;
}

bool ConverterJSON::readRequests()
{
    json j;
    std::ifstream file(this->requests_file_name);

    if(!file.is_open())
    {
        logger->critical("Unable to open %s file.", this->requests_file_name);
        return false;
    }

    try
    {
        file >> j;
        file.close();
    }
    catch(const std::exception& e)
    {
        logger->critical("Invalid .json format. Error {}.", e.what());
        return false;   
    }

    if(!j["requests"].empty())
    {
        for(auto& words : requests)
            this->requests.push_back(words);
    }
    else
    {
        logger->error("No valid requests.");
        return false;
    }

    logger->info("Requests parsed successfully.");
    return true;
}

std::vector<std::string> ConverterJSON::GetTextFromDocs()
{
    return this->docs;
}

int ConverterJSON::GetResponsesLimit()
{
    return this->max_responses;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    return this->requests;
}

std::string CreateRequestId(int i)
{
    std::ostringstream oss;
    oss << "request" <<std::setw(3) << std::setfill('0') << i;
    return oss.str();
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>>answers)
{
    nlohmann::ordered_json j;
    std::ofstream file(this->answers_file_name);

    size_t answers_size = answers.size();
    for(int i = 0; i < answers_size; i++)
    {
        std::string request_id = CreateRequestId(i);
        nlohmann::ordered_json req;
        if(freq_dictionary.find(requests[i]) != freq_dictionary.end())
        {
            req[request_id]["result"] = "true";
            for(int j = 0; j < answers[i].size(); j++)
            {
                nlohmann::ordered_json relevance;
                relevance["docid"] = answers[i][j].first, relevance["rank"] = answers[i][j].second;
                req[request_id]["relevance"].push_back(relevance);
            }
        }
        else
            req[request_id]["result"] = "false";

        j["answers"].push_back(req);
    }

    file << std::setw(4) << j;
    logger->info("answers.json created successfully.");
}