#include "Transaction.h"


Transaction::Transaction(char* from, char* to, float val, std::vector<TransactionInput> in) {
  sender = from;
  recipient = to;
  value = val;
  inputs = in;
}

std::string Transaction::calculateHash() {
  sequence++;
  std::stringstream ss;
  ss << sender << recipient << value << sequence;
  return sha256(ss.str());
}

void Transaction::generateSignature(char* privKey) {
  std::string senderString(sender);
  std::string recipientString(recipient);

  std::string dataString = senderString + recipientString + std::to_string(value);
  const unsigned char *data = (unsigned char*) dataString.c_str();
  struct ECDSASignature credentials = createECDSASignature(data);
  signature = credentials.sig;
  key = credentials.key;
}

int Transaction::verifySignature() {
  std::string senderString(sender);
  std::string recipientString(recipient);
  std::string dataString = senderString + recipientString + std::to_string(value);
  const unsigned char *data = (unsigned char*) dataString.c_str();
  return verifyECDSASignature(signature, data, key);
}
