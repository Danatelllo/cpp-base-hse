#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    const std::vector<int> data = {1, 2, 3, 4};
    auto answer = std::upper_bound(data.begin(), data.end(), 0);
    if (answer == data.end()) {
        return std::distance(data.begin(), answer) - 1;
    }
    if (answer == data.begin()) {
        return 2;
    }
    return 0;
}
