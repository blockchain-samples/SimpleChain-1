#include "Block.h"
#include "sha256.h"

Block::Block() {

}

Block::Block(std::string previousHash) {
  prevHash = previousHash;
  _time = time(nullptr);
  hash = calculateHash();
}

std::string Block::getHash() {
  return hash;
}

void Block::mineBlock(uint32_t difficulty) {
  merkleRoot = getMerkleRoot(transactions);
  char cstr[difficulty + 1];
  for(uint32_t i = 0; i < difficulty; i++) {
    cstr[i] = '0';
  }
  cstr[difficulty] = '\0';
  std::string str(cstr);

  do {
    nonce++;
    hash = calculateHash();
  } while(hash.substr(0, difficulty) != str);

  std::cout << "Block mined: " << hash << "\n";
}

std::string Block::calculateHash() const {
  std::stringstream ss;
  ss << prevHash << time << nonce << merkleRoot;

  return sha256(ss.str());
}

int Block::addTransaction(Transaction transaction) {
  // Make sure transaction isn't NULL
  if(transaction.transactionId.empty() && strlen(transaction.sender) == 0 && strlen(transaction.recipient)) {
    std::cout << "Transaction is NULL\n";
    return false;
  }


  // If genesis block, ignore
  if(!(prevHash.compare("0") == 0)) {
    if(transaction.processTransaction() != 1) {
      std::cout << "Transaction Failed!\n";
      return false;
    }
  }
  transactions.push_back(transaction);
  std::cout << "Transaction Added to Block\n";
  return 1;
}

std::ostream &operator<<(std::ostream &stream, Block block) {
  stream << "  {\n";
  stream << "    Hash: " << block.hash << "\n";
  stream << "    Previous Hash: " << block.prevHash << "\n";
  stream << "    Data: " << block.data << "\n";
  stream << "    Time Stamp: " << block._time << "\n";
  stream << "    Nonce: " << block.nonce << "\n";
  stream << "  }\n";
}
