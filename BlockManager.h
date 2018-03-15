#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include <string>
#include <stdio.h>

class BlockManager
{
public:
    BlockManager(const std::string& fileName);
    ~BlockManager();

    void AddBlock(const std::string& data, bool isGenesis = false);
    void WriteBlock(const std::string& data, const std::string& prevHash);
	void UpdateIndex(int pos, int dataLen, int count);

private:
    FILE *_blockFile;
	FILE *_indexFile;
};

#endif