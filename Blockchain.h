#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <map>
#include "Transaction.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "Block.h"

class Block;

class Blockchain {
public:
    Blockchain();
    void addBlock(Block newBlock);
    int isChainValid();
    friend std::ostream &operator<<(std::ostream &stream, Blockchain chain);
private:
    uint32_t difficulty;
    std::vector<Block> chain;
    Block getLastBlock();
};

#endif
