#include "StringHelpers.h"

std::vector<std::string> Split(const std::string& str, const std::string& separator)
{
    std::vector<std::string> strs;
    size_t startPos = 0;
    size_t endPos = str.find(separator);
    while (endPos != std::string::npos)
    {
        std::string partOfStr = str.substr(startPos, endPos - startPos);
        if (!partOfStr.empty())
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

std::vector<std::string> SplitWithEmptyStrings(const std::string& str, const std::string& separator)
{
    std::vector<std::string> strs;
    size_t startPos = 0;
    size_t endPos = str.find(separator);
    while (endPos != std::string::npos)
    {
        std::string partOfStr = str.substr(startPos, endPos - startPos);
        strs.push_back(partOfStr);
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

inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

std::string RemoveSpacesInBeginAndEndOfWord(const std::string& str)
{
    std::string newStr = str;
    ltrim(newStr);
    rtrim(newStr);
    return newStr;
}

std::string RemoveSubstringInBeginAndEndOfString(const std::string& str, const std::string& removedSubstring)
{
    if (str.length() == 0)
    {
        return "";
    }

    std::string newStr = str;
    if (str.substr(0, removedSubstring.length()) == removedSubstring)
    {
        newStr.erase(0, removedSubstring.length());
    }
    if (str.substr(str.length() - removedSubstring.length(), removedSubstring.length()) == removedSubstring)
    {
        newStr.erase(str.length() - removedSubstring.length() - 1, removedSubstring.length());
    }
    return newStr;
}