#include "MerkleRoot.h"

std::string getMerkleRoot(std::vector<Transaction> transactions) {
  int count = transactions.size();
  std::vector<std::string> previousTreeLayer;
  for(int i = 0; i < transactions.size(); i++) {
    previousTreeLayer.push_back(transactions[i].transactionId);
  }

  std::vector<std::string> treeLayer = previousTreeLayer;
  while(count > 1) {
    treeLayer.clear();
    for(int i = 0; i < previousTreeLayer.size(); i++) {
      treeLayer.push_back(sha256(previousTreeLayer[i - 1] + previousTreeLayer[i]));
    }
    count = treeLayer.size();
    previousTreeLayer = treeLayer;
  }
  std::string merkleRoot = (treeLayer.size() == 1) ? treeLayer[0] : "";
  return merkleRoot;
}
