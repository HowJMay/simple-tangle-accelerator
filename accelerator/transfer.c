#include "apis.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static ta_core_t ta_core;

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Please prvides `message` and `tag`.");
    return EXIT_FAILURE;
  }

  char *json_result;
  const char *pre_json_template =
      "{\"value\":100,"
      "\"message\":\"%s\",\"tag\":\"%s\"}";
  char *pre_json[strlen(pre_json_template) + NUM_TRYTES_SIGNATURE];

  snprintf(pre_json, strlen(pre_json_template) + NUM_TRYTES_SIGNATURE, pre_json_template, argv[1], argv[2]);

  // Initialize configurations with default value
  if (ta_config_default_init(&ta_core.info, &ta_core.tangle, &ta_core.cache, &ta_core.service) != SC_OK) {
    return EXIT_FAILURE;
  }

  if (ta_config_set(&ta_core.cache, &ta_core.service) != SC_OK) {
    return EXIT_FAILURE;
  }

  if (api_send_transfer(&ta_core.tangle, &ta_core.service, pre_json, &json_result) != RC_OK) {
    printf("api_send_transfer failed.");
    return EXIT_FAILURE;
  }
  printf("%s\n", json_result);
  return EXIT_SUCCESS;
}