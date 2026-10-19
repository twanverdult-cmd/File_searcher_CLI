#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> find_files(const fs::path& directory, const std::string& pattern) {
    std::vector<fs::path> matches;

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Error: Directory does not exist or is not a directory: " << directory << std::endl;
        return matches;
    }

    for (const auto& entry : fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied)) {
        if (fs::is_regular_file(entry.path())) {
            if (entry.path().filename().string().find(pattern) != std::string::npos) {
                matches.push_back(entry.path());
            }
        }
    }

    return matches;
}

void search_and_print(const std::string& dir, const std::string& pattern) {
    auto results = find_files(dir, pattern);

    if (results.empty()) {
        std::cout << "No matching files found." << std::endl;
        return;
    }
    std::cout << "Found " << results.size() << " match(es):" << std::endl;
    for (const auto& path : results) {
        std::cout << path.string() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // With arguments: one-shot search. Without: interactive loop.
    if (argc >= 3) {
        search_and_print(argv[1], argv[2]);
        return 0;
    }

    std::string dir, pattern;
    while (true) {
        std::cout << "Directory (empty = '.', 'q' = quit): ";
        if (!std::getline(std::cin, dir) || dir == "q") break;
        if (dir.empty()) dir = ".";

        std::cout << "Pattern: ";
        if (!std::getline(std::cin, pattern)) break;
        if (pattern.empty()) {
            std::cout << "Pattern cannot be empty." << std::endl;
            continue;
        }

        search_and_print(dir, pattern);
    }
    return 0;
}
