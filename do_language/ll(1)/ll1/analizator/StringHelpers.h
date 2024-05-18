#pragma once
#include <vector>
#include <string>

std::vector<std::string> Split(const std::string& str, const std::string& separator);

inline void ltrim(std::string& s, unsigned char removedChar);

inline void rtrim(std::string& s, unsigned char removedChar);

std::string RemoveSpacesInBeginAndEndOfWord(const std::string& str, unsigned char removedChar);