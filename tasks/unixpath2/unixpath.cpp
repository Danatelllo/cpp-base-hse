#include "unixpath.h"
UnixPath::UnixPath(std::string initial_dir) {
    start_dir_ = NormalizePath(initial_dir, initial_dir);
    current_dir_ = start_dir_;
}
size_t UnixPath::SearchSlash(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[str.size() - 1 - i] == '/') {
            return str.size() - 1 - i;
        }
    }
    return 0;
}
std::string UnixPath::NormalizePath(std::string& current_working_dir, std::string& path) {
    if (std::count(path.begin(), path.end(), '/') == 0) {
        return current_working_dir;
    }
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
void UnixPath::ChangeDirectory(std::string path) {
    start_dir_ = path;
}
std::string UnixPath::GetAbsolutePath() {
    return NormalizePath(current_dir_, start_dir_);
}
std::string UnixPath::GetRelativePath() {
    if (std::count(start_dir_.begin(), start_dir_.end(), '/') == 0) {
        return ".";
    }
    std::string normal_path = NormalizePath(current_dir_, start_dir_);
    size_t current_dir__first_slash = SearchSlash(current_dir_);
    size_t normal_path_first_slash = SearchSlash(normal_path);
    size_t normal_path_second_slash = start_dir_.size();
    bool first_compare = true;
    while (true) {
        if (current_dir_.substr(current_dir__first_slash, current_dir_.size()) ==
            start_dir_.substr(normal_path_first_slash, normal_path_second_slash)) {
            if (!first_compare) {
                return "." + start_dir_.substr(normal_path_second_slash, normal_path_second_slash);
            } else {
                return ".";
            }
        } else {
            first_compare = false;
            if (normal_path_first_slash == 0) {
                return ".." + normal_path.substr();
            } else {
                normal_path_second_slash = normal_path_first_slash;
                normal_path_first_slash = SearchSlash(normal_path.substr(0, normal_path_first_slash));
            }
        }
    }
}