/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/request.h"
#include <mapnik/request.hpp>

vecamole_request_t *vecamole_request_new(int width, int height,
                                         double xmin, double ymin,
                                         double xmax, double ymax) {
  try {
    mapnik::box2d<double> extent(xmin, ymin, xmax, ymax);
    mapnik::request *ptr = new mapnik::request(width, height, extent);
    return static_cast<vecamole_request_t *>(ptr);

  } catch (...) {
    // bad alloc should be the only thing thrown by operator new
  }

  return nullptr;
}

vecamole_request_t *vecamole_request_zxy(int width, int height,
                                         int z, int x, int y) {
  // TODO: implement
  return nullptr;
}

int vecamole_request_delete(vecamole_request_t *request) {
  mapnik::request *ptr = static_cast<mapnik::request *>(request);

  if (ptr != nullptr) {
    delete ptr;
    return 0;
  }

  return 1;
}

void vecamole_request_set_buffer_size(vecamole_request_t *request, int buffer_size) {
  mapnik::request *ptr = static_cast<mapnik::request *>(request);

  if (ptr != nullptr) {
    ptr->set_buffer_size(buffer_size);
  }
}
