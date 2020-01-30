#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <string.h>

struct ECDSASignature {
  ECDSA_SIG* sig;
  EC_KEY* key;
};

ECDSASignature createECDSASignature(const unsigned char* data);
int verifyECDSASignature(ECDSA_SIG* signature, const unsigned char* data, EC_KEY* eckey);
