#ifndef WALLET_H
#define WALLET_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <map>
#include <vector>
#include "Transaction.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "SimpleChain.h"

class Transaction;

class Wallet {
public:
  char* privateKey;
  char* publicKey;
  std::map<std::string, TransactionOutput> UTXOs;
  Wallet();
  float getBalance();
  Transaction sendFunds(char* recip, float val);
private:
  int generateKeyPair();
};

#endif
