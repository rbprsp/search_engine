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
    InvertedIndex ii;
    std::vector<std::string> qs = cj.GetRequests();
    ii.UpdateDocsBase(cj.GetTextFromDocs());
    
    SearchServer ss(ii);
    cj.PutAnswers(ss.search(qs));

    return 0;
}