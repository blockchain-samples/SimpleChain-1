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

std::ostream &operator<<(std::ostream &stream, Block block) {
  stream << "  {\n";
  stream << "    Hash: " << block.hash << "\n";
  stream << "    Previous Hash: " << block.prevHash << "\n";
  stream << "    Data: " << block.data << "\n";
  stream << "    Time Stamp: " << block._time << "\n";
  stream << "    Nonce: " << block.nonce << "\n";
  stream << "  }\n";
}
