#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include <string>

class BlockManager
{
public:
    BlockManager(const std::string& fileName);
    ~BlockManager();

    void AddBlock(const std::string& data, bool isGenesis = false);
    void WriteBlock();

private:
    FILE *_file;
};

#endif