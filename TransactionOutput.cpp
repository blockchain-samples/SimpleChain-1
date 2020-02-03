#include "TransactionOutput.h"

TransactionOutput::TransactionOutput() {
  
}

TransactionOutput::TransactionOutput(char* recip, float val, std::string parentTransId) {
  recipient = recip;
  value = val;
  parentTransactionId = parentTransId;

  std::stringstream ss;
  std::string recipientString(recipient);
  ss << recipientString << std::to_string(value) << parentTransactionId;
  id = sha256(ss.str());
}

int TransactionOutput::isMine(char* pubKey) {
  if (pubKey == recipient) {
    return 1;
  }
  return 0;
}
