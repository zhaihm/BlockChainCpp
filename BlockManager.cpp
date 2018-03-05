#include "BlockManager.h"
#include "Logger.h"
#include <stdio.h>

BlockManager::BlockManager(const std::string& fileName)
{
    _file = fopen(fileName.c_str(), "ab+");
    if (_file == NULL) {
        Logger::Error("Open file failed");
        return;
    }
    Logger::Debug("BlockManager created");
}

BlockManager::~BlockManager()
{
    fclose(_file);
    Logger::Debug("BlockManager destroyed");
}

void BlockManager::AddBlock(const std::string& data, bool isGenesis/* = false*/)
{
    Logger::Debug("Adding block");
}

void BlockManager::WriteBlock()
{
    Logger::Debug("Writing block");
}