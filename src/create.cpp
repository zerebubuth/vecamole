/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/create.h"

vecamole_create_options_t *vecamole_create_options_default() {
  try {
    vecamole_create_options_t *ptr = new struct vecamole_create_options;

    ptr->scale_factor = 1.0;
    ptr->offset_x = 0;
    ptr->offset_y = 0;
    ptr->area_threshold = 0.1;
    ptr->image_format = vecamole_image_format_JPEG;
    ptr->scaling_method = vecamole_scaling_method_NEAR;
    ptr->simplify_distance = 0.0;

    return ptr;

  } catch (...) {
    // bad alloc should be the only thing which is thrown
    return nullptr;
  }
}

int vecamole_create_tile(
  void *writer_private,
  vecamole_tile_writer_func_t *writer,
  vecamole_map_t *map,
  vecamole_request_t *request,
  vecamole_create_options_t *options) {
  return -1;
}

