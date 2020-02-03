#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include "Transaction.h"
#include "MerkleRoot.h"

class Transaction;

class Block {
public:
    std::string merkleRoot;
    std::string prevHash;
    std::vector<Transaction> transactions;
    Block();
    Block(std::string previousHash);
    std::string getHash();
    void mineBlock(uint32_t difficulty);
    std::string calculateHash() const;
    int addTransaction(Transaction transaction);
    friend std::ostream &operator<<(std::ostream &stream, Block block);
private:
    uint32_t index;
    int64_t nonce;
    std::string data;
    std::string hash;
    time_t _time;
};

#endif
