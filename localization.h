#pragma once
#include <windows.h>
#include <map>
#include <string>

class Localizer {
private:
    std::map<std::string, std::map<std::string, std::wstring>> strings;
    std::string currentLang;
    
    void LoadStrings();
    std::string GetSystemLanguage();

public:
    Localizer();
    std::wstring Get(const std::string& key);
    std::string GetA(const std::string& key);
};

extern Localizer g_localizer;
