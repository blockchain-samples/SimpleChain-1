#include "Blockchain.h"

Blockchain::Blockchain() {
  difficulty = 5;
}

void Blockchain::addBlock(Block newBlock) {
  newBlock.mineBlock(difficulty);
  chain.push_back(newBlock);
}

Block Blockchain::getLastBlock() {
  return chain.back();
}

int Blockchain::isChainValid() {
  char cstr[difficulty + 1];
  for(uint32_t i = 0; i < difficulty; i++) {
    cstr[i] = '0';
  }
  cstr[difficulty] = '\0';
  std::string hashTarget(cstr);

  Block currentBlock, previousBlock;
  std::map<std::string, TransactionOutput> tempUTXOs;
  tempUTXOs.insert(std::pair<std::string, TransactionOutput>(genesisTransaction.outputs[0].id, genesisTransaction.outputs[0]));
  for(int i = 1; i < chain.size(); i++) {
    currentBlock = chain[i];
    previousBlock = chain[i - 1];

    // Compare current hash
    if(currentBlock.getHash().compare(currentBlock.calculateHash()) != 0) {
      std::cout << "Current hashes not equal\n";
      return 0;
    }

    // Compare previous hash
    if(previousBlock.getHash().compare(previousBlock.calculateHash()) != 0) {
      std::cout << "Previous hashes not equal\n";
      return 0;
    }

    // If hash is solved
    if(currentBlock.getHash().substr(0, difficulty).compare(hashTarget) != 0) {
      std::cout << "Block hasn't been mined yet!\n";
      return 0;
    }

    // Loop through blockchains transactions
    for(int t = 0; t < currentBlock.transactions.size(); t++) {
      Transaction currentTransaction = currentBlock.transactions[t];

      if(currentTransaction.verifySignature() != 1) {
        std::cout << "Signature on transaction " << std::to_string(t) << "is invalid\n";
        return 0;
      }

      if(currentTransaction.getInputsValue() != currentTransaction.getOutputsValue()) {
        std::cout << "Inputs are not equal to outputs on transaction " << std::to_string(t) << "\n";
        return 0;
      }

      for(int j = 0; j < currentTransaction.inputs.size(); j++) {
        for(std::map<std::string, TransactionOutput>::iterator it = tempUTXOs.begin(); it != tempUTXOs.end(); it++) {
          std::cout << "id to match:" << it->first << "\n";
        }
        std::cout << "id being checked: " << currentTransaction.inputs[j].transactionOutputId << "\n";
        std::map<std::string, TransactionOutput>::iterator it = tempUTXOs.find(currentTransaction.inputs[j].transactionOutputId);
        if(it == tempUTXOs.end()) {
          // Failing here
          std::cout << "Referenced input on transaction " << std::to_string(t) << "is missing\n";
          return 0;
        }

        TransactionOutput tempOutput = it->second;
        std::cout << "Checking if id is empty...\n";
        if(tempOutput.id.empty()) {
          std::cout << "Referenced input on transaction " << std::to_string(t) << "is missing\n";
          return 0;
        }

        if(currentTransaction.inputs[j].UTXO.value != tempOutput.value) {
          std::cout << "Referenced input transaction " << std::to_string(t) << "is invalid\n";
          return 0;
        }

        tempUTXOs.erase(currentTransaction.inputs[j].transactionOutputId);
      }

      for(int j = 0; j < currentTransaction.outputs.size(); j++) {
        tempUTXOs.insert(std::pair<std::string, TransactionOutput>(currentTransaction.outputs[j].id, currentTransaction.outputs[j]));
      }

      if(currentTransaction.outputs[0].recipient != currentTransaction.recipient) {
        std::cout << "Transaction " << std::to_string(t) << "output recipient is not who is should be\n";
        return 0;
      }

      if(currentTransaction.outputs[1].recipient != currentTransaction.sender) {
        std::cout << "Transaction " << std::to_string(t) << "output 'change' is not sender\n";
        return 0;
      }
    }
  }
  std::cout << "Blockchain is valid\n";
  return 1;
}

std::ostream &operator<<(std::ostream &stream, Blockchain bChain) {
  stream << "[\n";
  for(long i = 1; i < bChain.chain.size(); i++) {
    Block currentBlock = bChain.chain[i];
    stream << currentBlock;
  }
  stream << "]\n";
}
