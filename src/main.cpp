#include <iostream>

#include "parser/parser.h"
#include "converter/converter.h"

int main(int argc, char* argv[])
{
    Parser* parser = new Parser();

    if(!parser->getParserState())
    {
        delete parser;
        return 1;
    }
        
    ConverterJSON* converter = new ConverterJSON;

    converter->GetTextFromDocs();

    delete parser;
    std::cin.get();
    
    return 0;
}
