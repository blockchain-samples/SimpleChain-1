#include "Blockchain.h"
#include "Wallet.h"
#include "Transaction.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"

int main() {
  std::vector<TransactionInput> v;
  Wallet walletA = Wallet();
  Wallet walletB = Wallet();

  Blockchain simpleChain = Blockchain();

  Transaction transaction1 = Transaction(walletA.publicKey, walletB.publicKey, 5, v);
  transaction1.generateSignature(walletA.privateKey);
  std::cout << "Signature Verification returned: ";
  std::cout << transaction1.verifySignature() << "\n";

  // std::cout << "Mining block 1...\n";
  // simpleChain.addBlock(Block(1, "Genesis Block"));
  // simpleChain.isChainValid();
  //
  // std::cout << "Mining block 2...\n";
  // simpleChain.addBlock(Block(2, "Block 2 Data"));
  // simpleChain.isChainValid();
  //
  // std::cout << "Mining block 3...\n";
  // simpleChain.addBlock(Block(3, "Block 3 Data"));
  // simpleChain.isChainValid();
  //
  // std::cout << simpleChain;

  return 0;
}
