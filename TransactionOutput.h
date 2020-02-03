#ifndef TRANSACTIONOUTPUT_H
#define TRANSACTIONOUTPUT_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include "sha256.h"

class TransactionOutput {
public:
  std::string id;
  char* recipient;
  float value;
  std::string parentTransactionId;
  TransactionOutput();
  TransactionOutput(char* recip, float val, std::string parentTransId);
  int isMine(char* pubKey);
private:
};

#endif
