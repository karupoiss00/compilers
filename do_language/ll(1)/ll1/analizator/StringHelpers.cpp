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