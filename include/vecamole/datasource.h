/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#ifndef VECAMOLE_DATASOURCE_H
#define VECAMOLE_DATASOURCE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int vecamole_register_datasources(const char *dir, int recurse);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECAMOLE_DATASOURCE_H */
