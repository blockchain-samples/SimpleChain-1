#include "SimpleChain.h"

std::map<std::string, TransactionOutput> SimpleChainUTXOs;
float SimpleChainMinimumTransaction = 0.1;
Wallet coinbase = Wallet();
Wallet walletA = Wallet();
Wallet walletB = Wallet();
std::vector<TransactionInput> v;
Transaction genesisTransaction = Transaction(coinbase.publicKey, walletA.publicKey, 100, v);

int main() {
  Blockchain simpleChain = Blockchain();
  genesisTransaction.generateSignature(coinbase.privateKey);
  genesisTransaction.transactionId = "0";
  genesisTransaction.outputs.push_back(TransactionOutput(genesisTransaction.recipient, genesisTransaction.value,
                                                    genesisTransaction.transactionId));

  SimpleChainUTXOs.insert(std::pair<std::string, TransactionOutput>(genesisTransaction.outputs[0].id, genesisTransaction.outputs[0]));

  std::cout << "Creating and mining genesis block...\n";
  Block genesis = Block("0");
  genesis.addTransaction(genesisTransaction);
  simpleChain.addBlock(genesis);
  printChainUTXOS();

  Block block1 = Block(genesis.getHash());
  std::cout << "Wallet A's balance is: " << walletA.getBalance() << "\n";
  std::cout << "Wallet A is attempting to send funds (40) to wallet B\n";
  Transaction newTransaction = walletA.sendFunds(walletB.publicKey, 40);
  if(newTransaction.value != 0) {
      block1.addTransaction(newTransaction);
  }
  simpleChain.addBlock(block1);
  std::cout << "Wallet A's Balance is: " << walletA.getBalance() << "\n";
  std::cout << "Wallet B's Balance is: " << walletB.getBalance() << "\n";
  printChainUTXOS();

  Block block2 = Block(block1.getHash());
  std::cout << "Wallet A is attempting to send more funds (1000) it has to wallet B...\n";
  newTransaction = walletA.sendFunds(walletB.publicKey, 1000);
  if(newTransaction.value != 0) {
    block2.addTransaction(newTransaction);
  }
  simpleChain.addBlock(block2);
  std::cout << "Wallet A's Balance is: " << walletA.getBalance() << "\n";
  std::cout << "Wallet B's Balance is: " << walletB.getBalance() << "\n";
  printChainUTXOS();

  Block block3 = Block(block2.getHash());
  std::cout << "Wallet B is attempting to send funds (20) to wallet A...\n";
  newTransaction = walletB.sendFunds(walletA.publicKey, 20);
  if(newTransaction.value != 0) {
    block3.addTransaction(newTransaction);
  }
  simpleChain.addBlock(block1);
  std::cout << "Wallet A's Balance is: " << walletA.getBalance() << "\n";
  std::cout << "Wallet B's Balance is: " << walletB.getBalance() << "\n";
  printChainUTXOS();
  int valid = simpleChain.isChainValid();
  // do something if not valid
  return 0;
}

void printChainUTXOS() {
  std::map<std::string, TransactionOutput>::iterator it;
  std::cout << "----------------UTXOS----------------\n\n";
  for(it = SimpleChainUTXOs.begin(); it != SimpleChainUTXOs.end(); it++) {
    std::cout << "UTXO ID: " << it->first << "\n";
    std::cout << "\t Value: " << std::to_string(it->second.value) << "\n\n";
  }
  std::cout << "-------------------------------------\n\n";
}
