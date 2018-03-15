#include "BlockManager.h"
#include "Logger.h"
#include "Util.h"
#include <stdio.h>
#include <stdlib.h>

#define MAGIC       0xD5E8A97F
#define HASH_ALG    "sha256"
#define HASH_LEN    32
#define BLK_SIZE    (13 + HASH_LEN)

BlockManager::BlockManager(const std::string& fileName)
{
    _blockFile = fopen(fileName.c_str(), "w+b");
    if (_blockFile == NULL) {
        Logger::Error("Open block file failed");
        return;
    }

	std::string indexFileName = fileName + ".idx";
	_indexFile = fopen(indexFileName.c_str(), "w+b");
	if (_indexFile == NULL) {
		Logger::Error("Open index file failed");
		return;
	}

    Logger::Debug("BlockManager created");
}

BlockManager::~BlockManager()
{
    fclose(_blockFile);
	fclose(_indexFile);
    Logger::Debug("BlockManager destroyed");
}

void BlockManager::AddBlock(const std::string& data, bool isGenesis/* = false*/)
{
    Logger::Debug("Adding block");

	if (isGenesis) {
		WriteBlock(data, Util::RepeatString("00", HASH_LEN));
		UpdateIndex(0, data.length(), 1);
	}
	else {
		fseek(_indexFile, 0, SEEK_SET);

		int maxBlock, zpos, ofs, len;
		fread(&maxBlock, 4, 1, _indexFile);
		zpos = maxBlock * 8 - 4;
		fseek(_indexFile, zpos, SEEK_SET);
		fread(&ofs, 4, 1, _indexFile);
		fread(&len, 4, 1, _indexFile);

		// Read last block and calculate hash
		char blockData[256] = { 0 };
		fseek(_blockFile, ofs, SEEK_SET);
		fread(blockData, 1, len, _blockFile);

		char hash[256] = { 0 };
		std::string blockStr(blockData);
		strncpy(hash, Util::SHA256(blockStr).c_str(), sizeof(hash));

		// Add new block to the end of the chain
		fseek(_blockFile, 0, SEEK_END);
		int pos = ftell(_blockFile);
		WriteBlock(data, hash);

		UpdateIndex(pos, data.length(), maxBlock + 1);
	}
}

void BlockManager::WriteBlock(const std::string& data, const std::string& prevHash)
{
    Logger::Debug("Writing block");

	const int magic = MAGIC;
	const char version = 1;
	const int dataLength = data.size();

    fwrite(&magic, 4, 1, _blockFile);									  // Magic
    fwrite(&version, 1, 1, _blockFile);                                    // Version
    fwrite(Util::GetTimestamp().c_str(), 4, 1, _blockFile);                // Timestamp
    fwrite(prevHash.c_str(), HASH_LEN, 1, _blockFile);      // Previous Hash
    fwrite(&dataLength, 4, 1, _blockFile);								  // Data Length
    fwrite(data.c_str(), 1, data.size(), _blockFile);					  // Data
}

void BlockManager::UpdateIndex(int pos, int dataLen, int count)
{
	fseek(_indexFile, 0, SEEK_SET);
	size_t sizeWritten = fwrite(&count, 4, 1, _indexFile);		// Record count
	char buffer[100];
	Logger::Debug(std::string("Size written = ") + itoa(sizeWritten, buffer, 10));
	
	fseek(_indexFile, 0, SEEK_END);
	fwrite(&pos, 4, 1, _indexFile);			// Offset

	int len = dataLen + BLK_SIZE;
	fwrite(&len, 4, 1, _indexFile);			// Length
}