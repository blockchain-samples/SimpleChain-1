#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>


RSA* getPrivateKeyFromString(char* privKey);
RSA* getPublicKeyFromString(char* pubKey);
