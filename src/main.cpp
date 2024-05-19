//STL
#include <iostream>
#include <memory>

//se classes
#include "converter/converter.h"
#include "utils/utils.h"

int main(int argc, char* argv[])
{

    std::unique_ptr<ConverterJSON> converter;
    
    try
    {
        std::make_unique<ConverterJSON>();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        Utils::PrintLogsLink();
        std::cin.get();
        return 1;
    }
    
    int resp = converter->GetResponsesLimit();

    std::cin.get();
    return 0;
}