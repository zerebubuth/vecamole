/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/datasource.h"
#include <mapnik/datasource_cache.hpp>

int vecamole_register_datasources(const char *dir, int recurse) {
  if (dir == nullptr) {
    return 1;
  }

  try {
    std::string cpp_dir(dir);
    bool cpp_recurse(recurse);

    bool success = mapnik::datasource_cache::instance().register_datasources(cpp_dir, cpp_recurse);

    return success ? 0 : 1;

  } catch (...) {
  }

  return -1;
}

