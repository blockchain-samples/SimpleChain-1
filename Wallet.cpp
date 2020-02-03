#include "Wallet.h"

Wallet::Wallet() {
  generateKeyPair();
}

int Wallet::generateKeyPair() {
  std::cout << "Generating Key Pair...\n";
  size_t pri_len;            // Length of private key
  size_t pub_len;            // Length of public key
  char* pri_key;             // Private key
  char* pub_key;             // Public key
  char* err;                 // Buffer for any error messages

  RSA *keypair = RSA_generate_key(4096, 3, NULL, NULL);

  // To get the C-string PEM form:
  BIO *pri = BIO_new(BIO_s_mem());
  BIO *pub = BIO_new(BIO_s_mem());

  PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
  PEM_write_bio_RSAPublicKey(pub, keypair);

  pri_len = BIO_pending(pri);
  pub_len = BIO_pending(pub);

  pri_key = (char*) malloc(pri_len + 1);
  pub_key = (char*) malloc(pub_len + 1);

  BIO_read(pri, pri_key, pri_len);
  BIO_read(pub, pub_key, pub_len);

  pri_key[pri_len] = '\0';
  pub_key[pub_len] = '\0';

  privateKey = pri_key;
  publicKey = pub_key;

  // free memory
  BIO_free(pri);
  BIO_free(pub);

  // printf("\n%s\n%s\n", pri_key, pub_key);
  // printf("done.\n");
}

float Wallet::getBalance() {
  float total = 0;

  for(std::map<std::string, TransactionOutput>::iterator it = SimpleChainUTXOs.begin(); it != SimpleChainUTXOs.end(); it++) {
    TransactionOutput UTXO = it->second;
    // Doesn't pass this check
    if(UTXO.isMine(publicKey) == 1) {
      UTXOs.insert(std::pair<std::string, TransactionOutput>(UTXO.id, UTXO));
      total += UTXO.value;
    }
  }
  return total;
}

Transaction Wallet::sendFunds(char* recip, float val) {
  // if wallet balance is less than value
  if(getBalance() < val) {
    // Return dummy transaction to be checked outside function call
    std::cout << "Not enough funds for transaction!\n";
    std::vector<TransactionInput> v;
    Transaction dummy = Transaction("0", "0", 0, v);
    return dummy;
  }

  // Inputs and total
  std::vector<TransactionInput> in;
  float total = 0;

  std::map<std::string, TransactionOutput>::iterator it;

  // Loop wallet UTXOs and add to total
  for(it = UTXOs.begin(); it != UTXOs.end(); it++) {
    TransactionOutput UTXO = it->second;
    total += UTXO.value;
    in.push_back(TransactionInput(UTXO.id));
    if(total > val) break;
  }

  for(int i = 0; i < in.size(); i++) {
    std::cout<< "sendFunds id: " << in[i].transactionOutputId << "\n";
  }

  // Create transaction
  Transaction newTransaction(publicKey, recip, val, in);
  newTransaction.generateSignature(privateKey);

  // Erase used inputs from wallet UTXOs
  for(int i = 0; i < in.size(); i++) {
    UTXOs.erase(in[i].transactionOutputId);
  }

  return newTransaction;
}
