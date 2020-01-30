#include "Blockchain.h"

Blockchain::Blockchain() {
  chain.emplace_back(Block(0, "Genesis Block"));
  difficulty = 5;
}

void Blockchain::addBlock(Block newBlock) {
  newBlock.prevHash = getLastBlock().getHash();
  newBlock.mineBlock(difficulty);
  chain.push_back(newBlock);
}

Block Blockchain::getLastBlock() const {
  return chain.back();
}

int Blockchain::isChainValid() {
  for(long i = 1; i < chain.size(); i++) {
    Block currentBlock = chain[i];
    Block previousBlock = chain[i - 1];

    if(currentBlock.getHash().compare(currentBlock.calculateHash()) != 0) {
      std::cout << "Current Hashes do not match, exiting...\n";
      return 0;
    }

    if(previousBlock.getHash().compare(currentBlock.prevHash) != 0) {
      std::cout << "Previous Hashes do not match, exiting...\n";
      return 0;
    }
  }

  return 1;
}

void Blockchain::print() {
  std::cout << "[\n";
  for(long i = 1; i < chain.size(); i++) {
    Block currentBlock = chain[i];
    currentBlock.print();
  }
  std::cout << "]\n";
}
