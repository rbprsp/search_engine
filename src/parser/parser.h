#ifndef __JSONCONVERTER_H__
#define __JSONCONVERTER_H__

#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <filesystem>
#include <stdexcept>

#include <json.hpp>

using nlohmann::json;

class Parser
{
private:
    const std::string cfg_name = "config.json";
    const std::string rq_name =  "requests.json";
    const std::string se_name =  "Search Engine";
    bool parsed = false;

    void generateConfig();
    bool parseRequests();
    bool parseConfig();

public:
    Parser();
    bool getParserState();
};

#endif