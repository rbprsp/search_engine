#include "parser.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void Parser::generateConfig()
{
    if(std::filesystem::exists(cfg_name))
        return;
    else
    {
        spdlog::warn("Config file not found. Create one? [Y\\N]:");
        
        char choice = ' ';
        while (true)
        {
            std::cout << "  > ";
            std::cin >> choice;
            if(choice == 'y' || choice == 'Y')
            {
                std::ofstream file(cfg_name);
                if(file.is_open())
                {
                    spdlog::info("Config file successfully created.");

                    json data;
                    data["config"]["name"] = se_name;
                    data["config"]["version"] = "1.0.0";
                    data["config"]["max_responses"] = 5;
                    data["files"] = {"your file's path here"};
                    
                    file << data.dump(4);
                    file.close();
                    return;
                }else
                {
                    spdlog::error("Unable to create config file.");
                    return;
                }
            }
            else
                break;
        }
    }
}

bool Parser::parseRequests()
{
    std::ifstream file(rq_name);
    if(!file.is_open())
    {
        spdlog::error("Unable to open request file.");
        return false;
    }

    json j;
    try
    {
        file >> j;
        file.close();
    }
    catch (...)
    {
        spdlog::error("Invalid .json format in requests file.");
        file.close();
        return false;
    }

    if(!j["requests"].empty())
    {
        size_t sz = j["requests"].size();
        if (sz > 1000)
        {
            spdlog::error("Too many requests. | max_requests count: 1000.");
            return false;
        }
    }
    else
    {
        spdlog::error("No words in the request.");
        return false;
    }

    spdlog::info("Request was parsed successfully.");
    return true;
}

bool Parser::parseConfig()
{
    if(!std::filesystem::exists(cfg_name))
    {
        spdlog::error("Config file not exists.");
        return false;
    }

    std::ifstream file(cfg_name);
    if(!file.is_open())
    {
        spdlog::error("Unable to open config file.");
        return false;
    }

    json j;
    try
    {
        file >> j;
        file.close();
    }
    catch (...)
    {
        spdlog::error("Invalid .json format in config file.");
        file.close();
        return false;
    }

    if(j["config"]["name"].empty() || j["config"]["name"] != se_name)
    {
        spdlog::error("Unknown engine name.");
        return false;
    }
    
    if (!j["config"]["version"].empty())
    {
        const std::regex version_regex(R"((\d+)\.(\d+)\.(\d+)$)");
        std::string version = j["config"]["version"];
        if(!std::regex_search(version, version_regex))
        {
            spdlog::error("Engine version not found.");
        return false;
        }
    }

    if (!j["config"]["max_responses"].empty())
    {
        int tmp;
        try 
        {
            tmp = j["config"]["max_responses"].get<int>();
            if (tmp < 0)
                throw std::invalid_argument("value should be in range 0 -> 1000");
        }
        catch (const std::exception& e) 
        {
            spdlog::error("Incorrect max_responses data: %s", std::string(e.what()).c_str());
            return false;
        }

    }
    else
    {
        spdlog::error("Incorrect max_responses value.");
        return false;
    }

    if (j["files"].empty())
    {
        spdlog::error("No input files found.");
        return false;
    }

    spdlog::info("Config was parsed successfully.");
    return true;

}

Parser::Parser()
{
    generateConfig();
    if (!parseConfig())
    {
        spdlog::error("Error while parsing config file.");
        return;
    }
    if (!parseRequests())
    {
        spdlog::error("Error while parsing requests file.");
        return;
    }

    parsed = true;
}

bool Parser::getParserState()
{
    return parsed;
}