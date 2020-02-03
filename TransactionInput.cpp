#include "TransactionInput.h"

TransactionInput::TransactionInput() {
  
}

TransactionInput::TransactionInput(std::string transactionOutId) {
  transactionOutputId = transactionOutId;
}
