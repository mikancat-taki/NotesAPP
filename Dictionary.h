#pragma once
#include <string>
#include <unordered_map>

class Dictionary {
public:
    Dictionary(const std::string& filePath);
    std::string lookup(const std::string& word);
private:
    std::unordered_map<std::string, std::string> entries;
};
