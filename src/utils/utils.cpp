#include "utils.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <dlfcn.h>
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
        std::filesystem::path exe_path = std::filesystem::read_symlink("/proc/self/exe");
        std::string link = exe_path.parent_path().string() + "/logs/";
        callPrinter(link);
    #elif defined(__APPLE__)
        Dl_info info;
        std::string link = "";
        if (dladdr(reinterpret_cast<void*>(get_executable_path), &info))
            link = std::filesystem::path(info.dli_fname).parent_path().string() + "/logs/";
        callPrinter(link);
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
