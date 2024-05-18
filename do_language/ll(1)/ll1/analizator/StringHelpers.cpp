#include "StringHelpers.h"

std::vector<std::string> Split(const std::string& str, const std::string& separator)
{
    std::vector<std::string> strs;
    size_t startPos = 0;
    size_t endPos = str.find(separator);
    while (endPos != std::string::npos)
    {
        std::string partOfStr = str.substr(startPos, endPos - startPos);
        if (partOfStr.length() != 0)
        {
            strs.push_back(partOfStr);
        }
        startPos = endPos + separator.length();
        endPos = str.find(separator, startPos);
    }

    if (startPos != str.length())
    {
        std::string partOfStr = str.substr(startPos);
        strs.push_back(partOfStr);
    }

    return strs;
}

inline void ltrim(std::string& s, unsigned char removedChar)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [removedChar](unsigned char ch) {
        return ch != removedChar;
        }));
}

inline void rtrim(std::string& s, unsigned char removedChar)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [removedChar](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

std::string RemoveSpacesInBeginAndEndOfWord(const std::string& str, unsigned char removedChar)
{
    std::string newStr = str;
    ltrim(newStr, removedChar);
    rtrim(newStr, removedChar);

    return newStr;
}