#include "word2vec.h"

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> answer;
    int64_t meaning_nearest = 0;
    int64_t vector_product;
    if (vectors.size() >= 2) {
        answer.push_back(words[1]);
        for (size_t j = 0; j < vectors[0].size(); ++j) {
            meaning_nearest += static_cast<int64_t>(vectors[0][j]) * static_cast<int64_t>(vectors[1][j]);
        }
    }
    for (size_t i = 2; i < vectors.size(); ++i) {
        vector_product = 0;
        for (size_t j = 0; j < vectors[0].size(); ++j) {
            vector_product += static_cast<int64_t>(vectors[0][j]) * static_cast<int64_t>(vectors[i][j]);
        }
        if (vector_product > meaning_nearest) {
            meaning_nearest = vector_product;
            answer.clear();
            answer.push_back(words[i]);
        } else if (vector_product == meaning_nearest) {
            answer.push_back(words[i]);
        }
    }
    return answer;
}
