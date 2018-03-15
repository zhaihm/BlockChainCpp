#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
    static std::string GetTimestamp();
    static std::string Hex2Bin(const std::string& hex);
	static std::string RepeatString(std::string str, std::size_t n);
	static std::string SHA256(const std::string& str);
};

#endif