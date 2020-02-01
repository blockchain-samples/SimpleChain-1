#ifndef WALLET_H
#define WALLET_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

class Wallet {
public:
  char* privateKey;
  char* publicKey;
  Wallet();
private:
  int generateKeyPair();
};

#endif
