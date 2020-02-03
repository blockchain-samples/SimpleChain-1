#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <map>
#include <vector>
#include "sha256.h"
#include "Blockchain.h"
#include "Block.h"
#include "Wallet.h"
#include "Transaction.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"

class Transaction;

extern std::map<std::string, TransactionOutput> SimpleChainUTXOs;
extern float SimpleChainMinimumTransaction;
extern Transaction genesisTransaction;

void printChainUTXOS();
