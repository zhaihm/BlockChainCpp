#include "BlockManager.h"
#include <stdio.h>

int main()
{
    printf("I'm a demo of Block Chain!\n");

    BlockManager bm("blockchain.dat");
    bm.AddBlock("", true);
    bm.AddBlock("", false);
    bm.AddBlock("", false);

    return 0;
}