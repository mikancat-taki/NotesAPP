#include "TranslatorCore.h"
#include "Dictionary.h"
#include <string>
#include <unordered_map>
#include <cstring>

// 簡易辞書
static Dictionary dict("translator_data.csv");

const char* TranslateText(const char* text, const char* targetLang)
{
    static std::string result;
    result = dict.lookup(text);
    if (result.empty()) {
        result = "[未登録: " + std::string(text) + "]";
    }
    return result.c_str();
}
