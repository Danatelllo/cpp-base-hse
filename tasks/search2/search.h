#pragma once

#include <string_view>
#include <vector>
#include "search.h"
#include <unordered_map>
#include <cmath>
#include <string>
#include <unordered_set>
#include <iostream>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count);
    static bool CompareMeaning(std::vector<double>& meaning1, std::vector<double>& meaning2);
    void SearchWords(const std::string& row,
                     std::unordered_map<std::string, std::unordered_map<size_t, std::vector<size_t>>>& repository,
                     const std::vector<std::string> query_words, size_t begin, size_t end);
    static bool Compare(std::vector<double>& meaning1, std::vector<double>& meaning2);
    bool Equal(const std::string& str1, const std::string& str2);
    std::string_view text;
};
