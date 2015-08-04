/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#ifndef VECAMOLE_CREATE_H
#define VECAMOLE_CREATE_H

#include <vecamole/map.h>
#include <vecamole/request.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// writer function called back for writing the vector tile, with
// the prototype int func(void *private, const char *data, int len)
// where private is the pointer which was passed to
// vecamole_create_tile and (data,len) describes the bytes to be
// written. it should return the number of bytes written, or -1 in
// case of error. note that returning 0 will be considered EOF and
// an error if len was > 0.
typedef int (*vecamole_tile_writer_func_t)(void *, const char *, int);

typedef enum {
  vecamole_image_format_JPEG = 0,
  vecamole_image_format_PNG
} vecamole_image_format_t;
  
typedef enum {
  vecamole_scaling_method_NEAR=0,
  vecamole_scaling_method_BILINEAR,
  vecamole_scaling_method_BICUBIC,
  vecamole_scaling_method_SPLINE16,
  vecamole_scaling_method_SPLINE36,
  vecamole_scaling_method_HANNING,
  vecamole_scaling_method_HAMMING,
  vecamole_scaling_method_HERMITE,
  vecamole_scaling_method_KAISER,
  vecamole_scaling_method_QUADRIC,
  vecamole_scaling_method_CATROM,
  vecamole_scaling_method_GAUSSIAN,
  vecamole_scaling_method_BESSEL,
  vecamole_scaling_method_MITCHELL,
  vecamole_scaling_method_SINC,
  vecamole_scaling_method_LANCZOS,
  vecamole_scaling_method_BLACKMAN
} vecamole_scaling_method_t;

typedef struct vecamole_create_options {
  double scale_factor;
  unsigned int offset_x, offset_y;
  double area_threshold;
  vecamole_image_format_t image_format;
  vecamole_scaling_method_t scaling_method;
  double simplify_distance;
} vecamole_create_options_t;

vecamole_create_options_t *vecamole_create_options_default();

int vecamole_create_tile(
  void *writer_private,
  vecamole_tile_writer_func_t *writer,
  vecamole_map_t *map,
  vecamole_request_t *request,
  vecamole_create_options_t *options);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECAMOLE_CREATE_H */
