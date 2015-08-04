/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#ifndef VECAMOLE_MAP_H
#define VECAMOLE_MAP_H

#include <vecamole/map.h>
#include <vecamole/request.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void vecamole_map_t;

vecamole_map_t *vecamole_map_new(int width, int height);

int vecamole_map_delete(vecamole_map_t *map);

int vecamole_map_register_fonts(vecamole_map_t *map, const char *dir, int recurse);

int vecamole_map_load_file(vecamole_map_t *map, const char *file, int strict, const char *base_path);

int vecamole_map_load_string(vecamole_map_t *map, const char *string, int strict, const char *base_path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECAMOLE_MAP_H */
