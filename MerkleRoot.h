#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"
#include "sha256.h"

class Transaction;

std::string getMerkleRoot(std::vector<Transaction> transactions);
