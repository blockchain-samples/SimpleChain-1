#include "Block.h"
#include "sha256.h"

Block::Block(uint32_t indexIn, const std::string &dataIn) {
  index = indexIn;
  data = dataIn;
  nonce = -1;
  _time = time(nullptr);
}

std::string Block::getHash() {
  return hash;
}

void Block::mineBlock(uint32_t difficulty) {
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

inline std::string Block::calculateHash() const {
  std::stringstream ss;
  ss << index << time << data << nonce << prevHash;

  return sha256(ss.str());
}

void Block::print() {
  std::cout << "  {\n";
  std::cout << "    Hash: " << hash << "\n";
  std::cout << "    Previous Hash: " << prevHash << "\n";
  std::cout << "    Data: " << data << "\n";
  std::cout << "    Time Stamp: " << _time << "\n";
  std::cout << "    Nonce: " << nonce << "\n";
  std::cout << "  }\n";
}
