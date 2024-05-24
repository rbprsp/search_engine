#ifndef __RELATIVE_H__
#define __RELATIVE_H__

//STL
#include <iostream>
#include <vector>

//local classes
#include "inverted.h"

struct RelativeIndex
{
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const;
};

class SearchServer
{
private:
    InvertedIndex _index;

public:
    SearchServer(InvertedIndex& idx) : _index(idx) {};
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
};

#endif