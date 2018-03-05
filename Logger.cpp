#include "Logger.h"
#include <stdio.h>

void Logger::Debug(const std::string& msg)
{
    printf("[DEBUG]:%s\n", msg.c_str());
}

void Logger::Warn(const std::string& msg)
{
    printf("[WARN]:%s\n", msg.c_str());
}

void Logger::Error(const std::string& msg)
{
    printf("[ERROR]:%s\n", msg.c_str());
}