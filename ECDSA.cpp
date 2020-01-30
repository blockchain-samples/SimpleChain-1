#include "ECDSA.h"

struct ECDSASignature createECDSASignature(const unsigned char* data) {
  struct ECDSASignature credentials;
  int function_status = -1;
  EC_KEY *eckey=EC_KEY_new();
  if (NULL == eckey) {
    printf("Failed to create new EC Key\n");
    exit(0);
  } else {
    credentials.key = eckey;
    EC_GROUP *ecgroup= EC_GROUP_new_by_curve_name(NID_secp192k1);
    if (NULL == ecgroup) {
      printf("Failed to create new EC Group\n");
      exit(0);
    } else {
      int set_group_status = EC_KEY_set_group(eckey,ecgroup);
      const int set_group_success = 1;
      if (set_group_success != set_group_status) {
          printf("Failed to set group for EC Key\n");
          exit(0);
      } else {
        const int gen_success = 1;
        int gen_status = EC_KEY_generate_key(eckey);
        if (gen_success != gen_status) {
          printf("Failed to generate EC Key\n");
          exit(0);
      } else {
          ECDSA_SIG* signature = ECDSA_do_sign(data, strlen((char*) data), eckey);
          if (NULL == signature) {
            printf("Failed to generate EC Signature\n");
            exit(0);
          } else {
              credentials.sig = signature;
              EC_GROUP_free(ecgroup);
              return credentials;
            }
        }
      }
        EC_GROUP_free(ecgroup);
    }
    EC_KEY_free(eckey);
  }
  exit(0);
}

int verifyECDSASignature(ECDSA_SIG* signature, const unsigned char* data, EC_KEY* eckey) {
  int function_status;
  int verify_status = ECDSA_do_verify(data, strlen((char*) data), signature, eckey);
  const int verify_success = 1;
  if (verify_success != verify_status)
  {
      printf("Failed to verify EC Signature\n");
      function_status = -1;
  }
  else
  {
      function_status = 1;
  }
  return function_status;
}
