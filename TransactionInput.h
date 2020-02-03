#ifndef TRANSACTIONINPUT_H
#define TRANSACTIONINPUT_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include "TransactionOutput.h"

class TransactionInput {
public:
  std::string transactionOutputId;
  TransactionOutput UTXO;
  TransactionInput();
  TransactionInput(std::string transactionOutId);
private:
};

#endif
