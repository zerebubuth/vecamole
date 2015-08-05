/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/request.h"
#include <mapnik/request.hpp>

#define MERCATOR_WORLD_SIZE (40075016.68)

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
  // sanity checking the range of tiles.
  if (z < 0) {
    return nullptr;
  }
  if (z > 30) {
    // TODO: include some sort of error message
    return nullptr;
  }

  const int max_coord = int(1) << z;
  if ((x < 0) || (x >= max_coord)) {
    return nullptr;
  }
  if ((y < 0) || (y >= max_coord)) {
    return nullptr;
  }

  const double xmin = MERCATOR_WORLD_SIZE * (double(x) / double(max_coord) - 0.5);
  const double ymin = MERCATOR_WORLD_SIZE * (0.5 - double(y+1) / double(max_coord));
  const double xmax = MERCATOR_WORLD_SIZE * (double(x+1) / double(max_coord) - 0.5);
  const double ymax = MERCATOR_WORLD_SIZE * (0.5 - double(y) / double(max_coord));

  return vecamole_request_new(width, height, xmin, ymin, xmax, ymax);
}

int vecamole_request_delete(vecamole_request_t *request) {
  mapnik::request *ptr = static_cast<mapnik::request *>(request);

  if (ptr != nullptr) {
    delete ptr;
    return 0;
  }

  return 1;
}

int vecamole_request_extent(vecamole_request_t *request,
                            double *xmin, double *ymin,
                            double *xmax, double *ymax) {
  mapnik::request *ptr = static_cast<mapnik::request *>(request);

  if (ptr != nullptr) {
    try {
      const mapnik::box2d<double> &extent = ptr->extent();

      *xmin = extent.minx();
      *ymin = extent.miny();
      *xmax = extent.maxx();
      *ymax = extent.maxy();
      return 0;

    } catch (...) {
      // pretty sure the above can't actually throw, though...
    }
  }

  return 1;
}

void vecamole_request_set_buffer_size(vecamole_request_t *request, int buffer_size) {
  mapnik::request *ptr = static_cast<mapnik::request *>(request);

  if (ptr != nullptr) {
    ptr->set_buffer_size(buffer_size);
  }
}
