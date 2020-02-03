#include "Transaction.h"
#include <openssl/err.h>


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
  // Build message string
  std::string senderString(sender);
  std::string recipientString(recipient);
  std::string dataString = std::to_string(value);

  // Get RSA* from privkey
  RSA* private_key = getPrivateKeyFromString(privKey);

  // Message and signature length
  unsigned int mlen = dataString.length();
  unsigned int siglen = (unsigned int) RSA_size(private_key);

  // Allocate signature memory and convert message string to char*
  const unsigned char *data = (unsigned char*) dataString.c_str();
  unsigned char* sig = (unsigned char *) malloc(siglen);

  // Sign
  RSA_sign(NID_sha1, data, mlen, sig, &siglen, private_key);
  signature = sig;
  signatureLength = siglen;
}

int Transaction::verifySignature() {
  // Build message string
  std::string senderString(sender);
  std::string recipientString(recipient);
  std::string dataString = std::to_string(value);

  // Get RSA* from pubKey
  RSA* public_key = getPublicKeyFromString(sender);

  // Message and signature length
  unsigned int mlen = dataString.length();
  // unsigned int siglen = (unsigned int) RSA_size(public_key);

  // Convert message string to char*
  const unsigned char *data = (unsigned char*) dataString.c_str();

  // Sign
  int status = RSA_verify(NID_sha1, data, mlen, signature, signatureLength, public_key);
  if(status == 0) {
    FILE* errFile = fopen("errors.txt", "w+");
    ERR_print_errors_fp(errFile);
  }
  return status;
}

int Transaction::processTransaction() {
  if(verifySignature() == 0) {
    std::cout << "Transaction signature failed to verify!\n";
    return 0;
  }

  for(int i = 0; i < inputs.size(); i++) {
    auto it = SimpleChainUTXOs.find(inputs[i].transactionOutputId);
    inputs[i].UTXO = it->second;
  }

  if(getInputsValue() < SimpleChainMinimumTransaction) {
    std::cout << "Transaction Inputs too small: " << std::to_string(getInputsValue()) << "\n";
    return 0;
  }

  float leftOver = getInputsValue() - value;
  transactionId = calculateHash();
  outputs.push_back(TransactionOutput(recipient, value, transactionId));
  outputs.push_back(TransactionOutput(sender, leftOver, transactionId));

  for(int i = 0; i < outputs.size(); i++) {
      SimpleChainUTXOs.insert(std::pair<std::string, TransactionOutput> (outputs[i].id, outputs[i]));
  }

  for(int i = 0; i < inputs.size(); i++) {
    if(inputs[i].UTXO.id.empty()) continue;
    SimpleChainUTXOs.erase(inputs[i].UTXO.id);
  }

  return 1;
}

float Transaction::getInputsValue() {
  float total = 0;
  for(int i = 0; i < inputs.size(); i++) {
    if(inputs[i].UTXO.id.empty() && inputs[i].transactionOutputId.empty()) continue;
      total += inputs[i].UTXO.value;
  }

  return total;
}

float Transaction::getOutputsValue() {
  float total = 0;
  for(int i = 0; i < outputs.size(); i++) {
    total += outputs[i].value;
  }

  return total;
}
