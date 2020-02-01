#include "RSAHelper.h"

RSA* getPrivateKeyFromString(char* privKey) {
  RSA* private_key;
  BIO* private_bio;

  private_bio = BIO_new_mem_buf(privKey, -1);
  if(private_bio == NULL) {
     std::cout << "Error getting public key BIO\n";
     exit(0);
  }

  private_key = PEM_read_bio_RSAPrivateKey(private_bio, NULL, NULL, NULL);
  if(private_key == NULL) {
     std::cout << "Error getting private key RSA\n";
     exit(0);
  }

  return private_key;
}

RSA* getPublicKeyFromString(char* pubKey) {
  RSA* public_key;
  BIO* public_bio;

  public_bio = BIO_new_mem_buf(pubKey, -1);
  if(public_bio == NULL) {
    std::cout << "Error getting public key BIO\n";
    exit(0);
  }

  public_key = PEM_read_bio_RSAPublicKey(public_bio, NULL, NULL, NULL);
  if(public_key == NULL) {
    std::cout << "Error getting public key RSA\n";
    exit(0);
  }
  
  return public_key;
}
