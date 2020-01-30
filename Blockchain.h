#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include "Block.h"

class Blockchain {
public:
    Blockchain();
    void addBlock(Block newBlock);
    int isChainValid();
    void print();
private:
    uint32_t difficulty;
    std::vector<Block> chain;
    Block getLastBlock() const;
};

#endif
