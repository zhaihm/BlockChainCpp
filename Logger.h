#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    static void Debug(const std::string& msg);
    static void Warn(const std::string& msg);
    static void Error(const std::string& msg);
};

#endif