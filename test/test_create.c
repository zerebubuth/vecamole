#include "vecamole.h"
#include <stdlib.h>
#include <stdio.h>

#define ASSERT(p) { if (!(p)) {                          \
    fprintf(stderr, "Assertion (%s) failed at %s:%d.\n", \
            #p, __FILE__, __LINE__);                     \
    return 1;                                            \
    } }

static int writer_null(void *private, const char *data, int len) {
  return len;
}

int main(int argc, char *argv[]) {
  int status = 0;

  vecamole_map_t *map = vecamole_map_new(256, 256);
  ASSERT(map != NULL);

  vecamole_request_t *request = vecamole_request_zxy(256, 256, 0, 0, 0);
  ASSERT(request != NULL);

  /*
  vecamole_create_options_t *opts = vecamole_create_options_default();
  ASSERT(opts != NULL);

  status = vecamole_create_tile(NULL, &writer_null, map, request, opts);
  ASSERT(status == 0);

  ASSERT(vecamole_create_options_delete(opts) == 0);
  */

  ASSERT(vecamole_request_delete(request) == 0);
  ASSERT(vecamole_map_delete(map) == 0);

  return 0;
}
