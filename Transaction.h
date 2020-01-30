#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include "sha256.h"
#include "ECDSA.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"

class Transaction {
public:
  std::string transactionId;
  char* sender;
  char* recipient;
  float value;
  ECDSA_SIG* signature;
  EC_KEY* key;
  std::vector<TransactionInput> inputs;
  std::vector<TransactionOutput> outputs;
  Transaction(char* from, char* to, float val, std::vector<TransactionInput> in);
  void generateSignature(char* privKey);
  int verifySignature();
private:
  int sequence = 0;
  std::string calculateHash();
};

#endif
