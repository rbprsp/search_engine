#include "logger.h"
#include <color.hpp>

int logger::logger_level = f_warning | f_error | f_success | f_log;

void logger::error(std::string message)
{
    if(logger_level & f_error)
        std::cerr << hue::red << "[-] " << hue::reset << message << std::endl;
}

void logger::warning(std::string message)
{
    if(logger_level & f_warning)
        std::clog << hue::yellow << "[!] " << hue::reset << message << std::endl;
}

void logger::log(std::string message)
{
    if(logger_level & f_log)
        std::clog << "[*] " << message << std::endl;
}

void logger::success(std::string message)
{
    if(logger_level & f_success)
        std::clog << hue::green << "[+] " << hue::reset << message << std::endl;
}
