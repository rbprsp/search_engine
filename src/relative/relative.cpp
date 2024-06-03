#include "relative.h"

bool RelativeIndex::operator==(const RelativeIndex& other) const
{
    return (doc_id == other.doc_id && rank == other.rank);
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input)
{
    std::vector<std::vector<RelativeIndex>> results; // this will be returned
    
    for(const auto& query : queries_input)
        _index.freq_dictionary.insert_or_assign(query, _index.GetWordCount(query));

    for(auto& [word, entries] : _index.freq_dictionary)
    {
        std::vector<RelativeIndex> idx;
        for(auto& entry : entries)
        {
            
        }
    }

    return results;
}