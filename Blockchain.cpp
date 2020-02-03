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
  // Generate difficulty string
  char cstr[difficulty + 1];
  for(uint32_t i = 0; i < difficulty; i++) {
    cstr[i] = '0';
  }
  cstr[difficulty] = '\0';
  std::string hashTarget(cstr);

  Block currentBlock, previousBlock;

  // Insert genesis transaction outputs UTXO
  std::map<std::string, TransactionOutput> tempUTXOs;
  tempUTXOs.insert(std::pair<std::string, TransactionOutput>(genesisTransaction.outputs[0].id, genesisTransaction.outputs[0]));

  // Loop chain and check hashes
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

      // Verify signature
      if(currentTransaction.verifySignature() != 1) {
        std::cout << "Signature on transaction " << std::to_string(t) << "is invalid\n";
        return 0;
      }

      // Check that inputs value matches outputs value
      if(currentTransaction.getInputsValue() != currentTransaction.getOutputsValue()) {
        std::cout << "Inputs are not equal to outputs on transaction " << std::to_string(t) << "\n";
        return 0;
      }

      // Loop through transaction inputs
      for(int j = 0; j < currentTransaction.inputs.size(); j++) {
        // Find UTXO is tempUTXOs that is referenced in the transaction
        std::map<std::string, TransactionOutput>::iterator it = tempUTXOs.find(currentTransaction.inputs[j].transactionOutputId);
        if(it == tempUTXOs.end()) {
          std::cout << "Referenced input on transaction " << std::to_string(t) << " is missing\n";
          return 0;
        }

        TransactionOutput tempOutput = it->second;

        // Check transaction inputs UTXO value is equal to chain UTXO value
        if(currentTransaction.inputs[j].UTXO.value != tempOutput.value) {
          std::cout << "Referenced input transaction " << std::to_string(t) << "is invalid\n";
          return 0;
        }

        // Remove current transaction input from tempUTXOs
        tempUTXOs.erase(currentTransaction.inputs[j].transactionOutputId);
      }

      // Insert current transaction outputs into tempUTXOs
      for(int j = 0; j < currentTransaction.outputs.size(); j++) {
        tempUTXOs.insert(std::pair<std::string, TransactionOutput>(currentTransaction.outputs[j].id, currentTransaction.outputs[j]));
      }

      // Check that recipients are equal
      if(currentTransaction.outputs[0].recipient != currentTransaction.recipient) {
        std::cout << "Transaction " << std::to_string(t) << "output recipient is not who is should be\n";
        return 0;
      }

      // Check that leftover transaction output matches sender
      if(currentTransaction.outputs[1].recipient != currentTransaction.sender) {
        std::cout << "Transaction " << std::to_string(t) << "output 'change' is not sender\n";
        return 0;
      }
    }
  }
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
