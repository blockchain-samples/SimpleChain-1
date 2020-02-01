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
