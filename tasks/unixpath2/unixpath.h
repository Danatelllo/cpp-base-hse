#pragma once

#include <string>
#include <string_view>
class UnixPath {
public:
    UnixPath(std::string initial_dir);

    void ChangeDirectory(std::string path);

    std::string GetAbsolutePath();
    std::string GetRelativePath();

private:
    std::string start_dir_;
    std::string current_dir_;
    size_t SearchSlash(const std::string& str);
    std::string NormalizePath(std::string& current_working_dir, std::string& path);
};
