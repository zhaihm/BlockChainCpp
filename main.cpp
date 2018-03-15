#include "BlockManager.h"
#include "Util.h"
#include <stdio.h>

int main()
{
    BlockManager bm("blockchain.dat");
    bm.AddBlock("The first block", true);
    bm.AddBlock("The second block", false);
    bm.AddBlock("The third block", false);

	// Test SHA 256
	// printf("%s\n", Util::SHA256("message").c_str());

	// Test Hex2Bin
	//printf("Hex2Bin: %s\n", Util::Hex2Bin("ab530a13e45914982b79f9b7e3fba994cfd1f3fb22f71cea1afbf02b460c6d1d").c_str());

    return 0;
}