#include "Dictionary.h"
#include <fstream>
#include <sstream>

Dictionary::Dictionary(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line, src, tgt;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (std::getline(ss, src, ',') && std::getline(ss, tgt)) {
            entries[src] = tgt;
        }
    }
}

std::string Dictionary::lookup(const std::string& word) {
    auto it = entries.find(word);
    if (it != entries.end()) return it->second;
    return "";
}
