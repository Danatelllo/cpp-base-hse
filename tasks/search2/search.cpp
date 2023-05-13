#include "search.h"
void SearchEngine::BuildIndex(std::string_view new_text) {
    text = new_text;
}
bool SearchEngine::CompareMeaning(std::vector<double>& meaning1, std::vector<double>& meaning2) {
    return meaning1[0] < meaning2[0];
}
bool SearchEngine::Compare(std::vector<double>& meaning1, std::vector<double>& meaning2) {
    if (meaning1[2] == meaning2[2]) {
        return meaning1[0] < meaning2[0];
    } else {
        return meaning1[2] > meaning2[2];
    }
}
bool SearchEngine::Equal(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (size_t j = 0; j < str1.size(); ++j) {
        if (tolower(str1[j]) != tolower(str2[j])) {
            return false;
        }
    }
    return true;
}

void SearchEngine::SearchWords(
    const std::string& row,
    std::unordered_map<std::string, std::unordered_map<size_t, std::vector<size_t>>>& repository,
    const std::vector<std::string> query_words, size_t begin, size_t end) {
    std::string word;
    std::vector<std::string> found_words;
    std::int64_t word_counter = 0;
    for (size_t j = 0; j < row.size(); ++j) {
        if (isalpha(row[j])) {
            word += row[j];
        } else {
            if (!word.empty()) {
                word_counter += 1;
                for (const auto& query_word : query_words) {
                    if (Equal(word, query_word)) {
                        auto it = repository[query_word].find(begin);
                        if (it != repository[query_word].end()) {
                            it->second[0] += 1;
                        } else {
                            repository[query_word][begin].push_back(1);
                            repository[query_word][begin].push_back(end);
                            found_words.push_back(query_word);
                        }
                        break;
                    }
                }
            }
            word = "";
        }
    }
    if (!word.empty()) {
        word_counter += 1;
        for (const auto& query_word : query_words) {
            if (Equal(word, query_word)) {
                auto it = repository[query_word].find(begin);
                if (it != repository[query_word].end()) {
                    it->second[0] += 1;
                } else {
                    repository[query_word][begin].push_back(1);
                    repository[query_word][begin].push_back(end);
                    found_words.push_back(query_word);
                }
                break;
            }
        }
    }
    for (const auto& found_word : found_words) {
        repository[found_word][begin].push_back(word_counter);
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) {
    size_t quantity_rows = 0;
    std::vector<std::vector<double>> relevant;
    std::string word;
    std::vector<std::string_view> answer;
    std::vector<std::string> query_words;
    std::vector<std::vector<double>> pred_answer;
    std::string slice;
    std::unordered_set<std::string> n;
    size_t begin = 0;
    std::vector<double> m;
    std::unordered_map<std::string, std::unordered_map<size_t, std::vector<size_t>>> repository;
    //выковыриваю слова из начальной строки и кладу в query_words.
    for (size_t j = 0; j < query.size(); ++j) {
        if (isalpha(query[j])) {
            word += query[j];
        } else {
            n.insert(word);
            word = "";
        }
        if (j + 1 == query.size()) {
            if (!word.empty()) {
                n.insert(word);
            }
        }
    }
    for (auto j : n) {
        query_words.push_back(j);
    }
    // начинаю бежать по строке пока не встречу конец или не встречу конец строки, затем с помощью begin b и j режу
    // строку и передаю в функцию begin and j like begin and end в функцию избегая пустую строку и считая сколько вообще
    // строк quantity_rows += 1
    for (size_t j = 0; j < text.size(); ++j) {
        if (text[j] == '\n' || j == text.size() - 1) {
            if (j + 1 == text.size()) {
                slice = static_cast<std::string>(text.substr(begin, text.size() - begin));
                if (!slice.empty()) {
                    quantity_rows += 1;
                    SearchEngine::SearchWords(slice, repository, query_words, begin, j + 1);
                    begin = j + 1;
                }
            } else {
                slice = static_cast<std::string>(text.substr(begin, j - begin));
                if (!slice.empty()) {
                    SearchEngine::SearchWords(slice, repository, query_words, begin, j);
                    begin = j + 1;
                    quantity_rows += 1;
                }
            }
        }
    }
    // тут пытаюсь считать ответ, что делаю, бегу по словам из запроса, потом использую эти слова, как ключи и с помощью
    // слова достаю инфу о строке и сколько раз это слово встретилось в этой строке потом в relevant я пушу данные о
    // строке, начало, конец, релевантность (в смысле для одного вида строки)
    for (const auto& query_word : query_words) {
        for (const auto& row : repository[query_word]) {
            if (!(repository[query_word].empty()) &&
                std::log(double((quantity_rows) / repository[query_word].size())) > 0) {
                m.push_back(row.first);
                m.push_back(repository[query_word][row.first][1]);
                m.push_back(std::log2(double(quantity_rows) / repository[query_word].size()) *
                            (double(repository[query_word][row.first][0]) / repository[query_word][row.first][2]));
                relevant.push_back(m);
                m = {};
            }
        }
    }
    //теперь тут я сортирую relevant чтобы одинаковые строки, которые будут подсчитаны несколько раз для разных слов в
    //запросе в одной строке
    //
    std::sort(relevant.begin(), relevant.end());
    for (size_t j = 0; j < relevant.size(); ++j) {
        if (pred_answer.empty()) {
            pred_answer.push_back(relevant[j]);
        } else {
            if (relevant[j][0] == pred_answer[pred_answer.size() - 1][0]) {
                pred_answer[pred_answer.size() - 1][2] += relevant[j][2];

            } else {
                pred_answer.push_back(relevant[j]);
            }
        }
    }
    std::sort(pred_answer.begin(), pred_answer.end(), SearchEngine::Compare);
    for (size_t j = 0; j < std::min(results_count, pred_answer.size()); ++j) {
        if (pred_answer[j][2] > 0) {

            answer.push_back(text.substr(pred_answer[j][0], pred_answer[j][1] - pred_answer[j][0]));
        }
    }
    return answer;
}