#include "utils.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#else
    #error "Unsupported platform"
#endif

//hyperlink
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>

void Utils::PrintLogsLink()
{
    #if defined(_WIN32) || defined(_WIN64)
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::filesystem::path exe_path(buffer);

        std::string link = std::filesystem::canonical(exe_path).parent_path().string() + "/logs/";
        callPrinter(link);
    #elif defined(__linux__)
        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
        std::filesystem::path exe_path = std::string(buffer, (count > 0) ? count : 0);
        std::string link = std::filesystem::canonical(exe_path).parent_path().string() + "/logs/";
        callPrinter(link);
    #elif defined(__APPLE__)
        char buffer[PATH_MAX];
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) == 0) 
        {
            std::string link = std::filesystem::canonical(exe_path).parent_path().string() + "/logs/";
            callPrinter(link);
        } 
        else 
            return "./logs/";
    #else
        #error "Unsupported platform"
    #endif
}

void Utils::callPrinter(std::string link)
{
    using namespace ftxui;
    auto document =
    hbox({
        text("For more information check logs "),
        text("folder") | hyperlink(link) | underlined | color(Color::Blue),
        text(".")
    });
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
}
