#include "unixpath.h"
#include <string>

size_t SearchSlash(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[str.size() - 1 - i] == '/') {
            return str.size() - 1 - i;
        }
    }
    return 0;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (std::count(path.begin(), path.end(), '.') == 0) {
        std::string right_path;
        for (size_t j = 0; j < path.size(); ++j) {
            if (path[j] == '/' && (j + 1 < path.size()) && path[j + 1] != '/') {
                right_path += path[j];
            } else if (path[j] != '/') {
                right_path += path[j];
            }
        }
        if (right_path.empty()) {
            return "/";
        } else {
            return right_path;
        }
    } else {
        std::string right_path = static_cast<std::string>(current_working_dir);
        for (size_t j = 0; j < path.size(); ++j) {
            if ((path[j] == '.') && (j + 1 < path.size()) && (path[j + 1] == '.')) {
                right_path = right_path.substr(0, SearchSlash(right_path));
            } else if ((path[j] == '/') && (j + 1 < path.size()) && (path[j + 1] != '/') && (path[j + 1] != '.') &&
                       (((!right_path.empty()) && (right_path[right_path.size() - 1] != '/')) || right_path.empty())) {
                right_path += path[j];
            } else if ((path[j] != '/') && (path[j] != '.')) {
                right_path += path[j];
            }
        }
        if (right_path.empty()) {
            return "/";
        } else {
            return right_path;
        }
    }
}