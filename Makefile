BlockChain: main.o BlockManager.o Logger.o
	CC -o BlockChain main.o BlockManager.o Logger.o Util.o -lstdc++

main.o: main.cpp
	CC -c main.cpp

BlockChain.o: BlockManager.cpp BlockManager.h
	CC -c BlockManager.cpp

Logger.o: Logger.cpp Logger.h
	CC -c Logger.cpp

Util.o: Util.cpp Util.h
	CC -c Util.cpp

clean:
	rm BlockChain main.o BlockManager.o Logger.o