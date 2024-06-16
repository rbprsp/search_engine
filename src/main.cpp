//STL
#include <iostream>
#include <memory>

//se classes
#include "converter.h"
#include "inverted.h"
#include "relative.h"

int main(int argc, char* argv[])
{
    ConverterJSON cj;
    if(argc > 1)
    {
        if(std::strcmp(argv[1], "--config") == 0)
        {
            cj.GenerateConfig();
            std::cout << "Config file was created successfully." << std::endl;
            return 0;
        }
    }

    if(!cj.ValidateConfig())
    {
        std::cout << "ERROR: check logs folder. \""<< ConverterJSON::log_file_name << "\"" << std::endl;
        return 1;
    }

    InvertedIndex ii;
    std::vector<std::string> qs = cj.GetRequests();
    ii.UpdateDocsBase(cj.GetTextFromDocs());
    
    SearchServer ss(ii);
    ss.setMaxResponses(cj.GetResponsesLimit());
    cj.PutAnswers(ss.search(qs));

    return 0;
}