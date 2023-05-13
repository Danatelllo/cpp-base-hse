#include "palindrome.h"
#include <string>

bool IsPalindrome(const std::string& str) {
    int i = 0;
    int j = str.size() - 1;
    while (i < j) {
        if (str[i] == ' ') {
            ++i;
        } else if (str[j] == ' ') {
            --j;
        } else if (str[i] != str[j]) {
            return false;
        } else if (str[i] == str[j]) {
            ++i;
            --j;
        }
    }
    return true;
}
