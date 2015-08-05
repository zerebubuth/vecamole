/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/map.h"
#include <mapnik/map.hpp>
#include <mapnik/load_map.hpp>
#include <stdexcept>
#include <iostream>

vecamole_map_t *vecamole_map_new(int width, int height) {
  try {
    mapnik::Map *ptr = new mapnik::Map(width, height);
    return static_cast<vecamole_map_t *>(ptr);

  } catch (...) {
    // bad alloc should be the only thing thrown by operator new
  }

  return nullptr;
}

int vecamole_map_delete(vecamole_map_t *map) {
  mapnik::Map *ptr = static_cast<mapnik::Map *>(map);

  if (ptr != nullptr) {
    delete ptr;
    return 0;
  }

  return 1;
}

int vecamole_map_register_fonts(vecamole_map_t *map, const char *dir, int recurse) {
  mapnik::Map *ptr = static_cast<mapnik::Map *>(map);

  if (ptr != nullptr) {
    try {
      std::string cpp_dir(dir);
      bool cpp_recurse(recurse);

      bool result = ptr->register_fonts(cpp_dir, cpp_recurse);

      return result ? 1 : 0;

    } catch (...) {
      // not sure what exceptions mapnik::Map::register_fonts could throw
      // but result is error regardless.
    }
  }

  return -1;
}

int vecamole_map_load_file(vecamole_map_t *map, const char *file, int strict, const char *base_path) {
  mapnik::Map *ptr = static_cast<mapnik::Map *>(map);

  if (ptr != nullptr) {
    try {
      std::string cpp_file(file);
      bool cpp_strict(strict);
      std::string cpp_base_path;
      if (base_path != nullptr) {
        cpp_base_path = base_path;
      }

      mapnik::load_map(*ptr, cpp_file, cpp_strict, cpp_base_path);

      return 0;

    } catch (...) {
      // not sure what exceptions mapnik::load_map could throw
      // but result is error regardless.
    }
  }

  return -1;
}

int vecamole_map_load_string(vecamole_map_t *map, const char *string, int strict, const char *base_path) {
  mapnik::Map *ptr = static_cast<mapnik::Map *>(map);

  if (ptr != nullptr) {
    try {
      std::string cpp_string(string);
      bool cpp_strict(strict);
      std::string cpp_base_path;
      if (base_path != nullptr) {
        cpp_base_path = base_path;
      }

      mapnik::load_map_string(*ptr, cpp_string, cpp_strict, cpp_base_path);

      return 0;

    } catch (const std::exception &e) {
      std::cerr << "EXCEPTION: " << e.what() << std::endl;

    } catch (...) {
      // not sure what exceptions mapnik::load_map could throw
      // but result is error regardless.
    }
  }

  return -1;
}
