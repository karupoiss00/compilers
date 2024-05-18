#pragma once
#include <vector>
#include <string>

std::vector<std::string> Split(const std::string& str, const std::string& separator);

inline void ltrim(std::string& s);

inline void rtrim(std::string& s);

std::string RemoveSpacesInBeginAndEndOfWord(const std::string& str);