#include "apis.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static ta_core_t ta_core;

static status_t find_transactions_obj_by_tag(const iota_client_service_t* const service, const char* const obj) {
  status_t ret = SC_OK;
  flex_trit_t tag_trits[NUM_FLEX_TRITS_TAG];
  find_transactions_req_t* req = find_transactions_req_new();
  transaction_array_t* res = transaction_array_new();
  if (req == NULL || res == NULL) {
    ret = SC_TA_OOM;
    goto done;
  }

  flex_trits_from_trytes(tag_trits, NUM_TRITS_TAG, (const tryte_t*)obj, NUM_TRYTES_TAG, NUM_TRYTES_TAG);
  if (find_transactions_req_tag_add(req, tag_trits) != RC_OK) {
    ret = SC_CCLIENT_INVALID_FLEX_TRITS;
    goto done;
  }

  ret = ta_find_transactions_obj_by_tag(service, req, res);
  if (ret) {
    goto done;
  }

  iota_transaction_t* txn = NULL;
  TX_OBJS_FOREACH(res, txn) {
    char msg[NUM_TRYTES_MESSAGE];
    tryte_t msg_tryte[NUM_TRYTES_MESSAGE];

    flex_trits_to_trytes(msg_tryte, NUM_TRYTES_MESSAGE, transaction_message(txn), NUM_FLEX_TRITS_MESSAGE,
                         NUM_FLEX_TRITS_MESSAGE);
    trytes_to_ascii(msg_tryte, NUM_TRYTES_MESSAGE, msg);
    printf("%s\n", (char*)msg);
  }

done:
  find_transactions_req_free(&req);
  transaction_array_free(res);
  return ret;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Please prvides `tag`.");
    return EXIT_FAILURE;
  }

  // Initialize configurations with default value
  if (ta_config_default_init(&ta_core.info, &ta_core.tangle, &ta_core.cache, &ta_core.service) != SC_OK) {
    return EXIT_FAILURE;
  }

  if (ta_config_set(&ta_core.cache, &ta_core.service) != SC_OK) {
    return EXIT_FAILURE;
  }

  if (find_transactions_obj_by_tag(&ta_core.service, argv[1]) != SC_OK) {
    printf("api_send_transfer failed.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}