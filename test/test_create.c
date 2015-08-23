/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

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

static const char *config = 
  "<!DOCTYPE Map>"
  "<Map srs=\"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs\">"
  "  <Layer name=\"point\" srs=\"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs\">"
  "    <StyleName>point</StyleName>"
  "    <Datasource>"
  "    <Parameter name=\"type\">csv</Parameter>"
  "    <Parameter name=\"inline\">"
  "type,WKT\n"
  "point,\"POINT (0 0)\"\n"
  "</Parameter>"
  "    </Datasource>"
  "  </Layer>"
  "</Map>";

int main(int argc, char *argv[]) {
  int len = 0;

  ASSERT(vecamole_register_datasources(MAPNIK_DEFAULT_INPUT_PLUGIN_DIR, 0) == 0);

  vecamole_map_t *map = vecamole_map_new(256, 256);
  ASSERT(map != NULL);

  ASSERT(vecamole_map_load_string(map, config, 0, "") == 0);

  vecamole_request_t *request = vecamole_request_zxy(256, 256, 0, 0, 0);
  ASSERT(request != NULL);

  vecamole_create_options_t *opts = vecamole_create_options_default();
  ASSERT(opts != NULL);

  len = vecamole_create_tile(NULL, &writer_null, map, request, opts);
  ASSERT(len > 0);

  ASSERT(vecamole_create_options_delete(opts) == 0);
  ASSERT(vecamole_request_delete(request) == 0);
  ASSERT(vecamole_map_delete(map) == 0);

  return 0;
}
