/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#ifndef VECAMOLE_REQUEST_H
#define VECAMOLE_REQUEST_H

#include <vecamole/map.h>
#include <vecamole/request.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void vecamole_request_t;

vecamole_request_t *vecamole_request_new(int width, int height,
                                         double xmin, double ymin,
                                         double xmax, double ymax);

vecamole_request_t *vecamole_request_zxy(int width, int height,
                                         int z, int x, int y);

int vecamole_request_delete(vecamole_request_t *request);

void vecamole_request_set_buffer_size(vecamole_request_t *request, int buffer_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECAMOLE_REQUEST_H */
