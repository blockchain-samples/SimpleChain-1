#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <sstream>

class Block {
public:
    std::string prevHash;
    Block(uint32_t indexIn, const std::string &dataIn);
    std::string getHash();
    void mineBlock(uint32_t difficulty);
    std::string calculateHash() const;
    friend std::ostream &operator<<(std::ostream &stream, Block block);
private:
    uint32_t index;
    int64_t nonce;
    std::string data;
    std::string hash;
    time_t _time;
};

#endif
