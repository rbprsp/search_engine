#include "relative.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>

bool RelativeIndex::operator==(const RelativeIndex& other) const
{
    return (doc_id == other.doc_id && rank == other.rank);
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) 
{
    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries_input) 
    {
        std::map<int, int> abs_relevance;

        std::istringstream iss(query);
        std::string word;
        while (iss >> word) 
        {
            auto word_count = _index.GetWordCount(word);
            for (const auto& [doc_id, count] : word_count) 
                abs_relevance[doc_id] += count;
        }

        int max_abs_relevance = 0;
        for (const auto& [doc_id, relevance] : abs_relevance) 
        {
            if (relevance > max_abs_relevance) 
                max_abs_relevance = relevance;
        }

        std::vector<RelativeIndex> query_results;
        for (const auto& [doc_id, relevance] : abs_relevance) 
        {
            RelativeIndex ri;
            ri.doc_id = doc_id;
            ri.rank = static_cast<float>(relevance) / max_abs_relevance;
            query_results.push_back(ri);
        }

        std::sort(query_results.begin(), query_results.end(), [](const RelativeIndex& a, const RelativeIndex& b)
        {
            if (a.rank != b.rank)
                return a.rank > b.rank;
            else
                return a.doc_id < b.doc_id;
        });

        if (query_results.size() > 5)
            query_results.resize(5); 

        results.push_back(query_results);
    }
    return results;
}