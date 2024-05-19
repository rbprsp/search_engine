///STL
#include <iostream>

//TEST Framework
#include <gtest/gtest.h>

//TEST Classes
#include <index.h>

void TestInvertedIndexFunctionality(const std::vector<std::string>& docs, const std::vector<std::string>& requests, const std::vector<std::vector<Entry>>& expected) 
{
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocsBase(docs);
    for(auto& request : requests) 
    {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvetedIndex, TestBasic)
{
    const std::vector<std::string> docs = //
    {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<Entry>> expected = //
    {
        {{0, 1}}, {{0, 1}, {1, 3}}
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}