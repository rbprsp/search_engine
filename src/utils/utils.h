#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <filesystem>

class Utils
{
public:
    static void PrintLogsLink();
private:
    static void callPrinter(std::string link);
};


#endif