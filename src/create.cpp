/* This file is part of Vecamole.
 * Copyright (c) Matt Amos <zerebubuth@gmail.com>. All rights reserved.
 * Redistribution allowed under the terms of the 2-clause BSD license
 * distributed with the source code, or available at
 * http://github.com/zerebubuth/vecamole/blob/master/COPYING
 */

#include "vecamole/create.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <vector_tile_backend_pbf.hpp>
#include <vector_tile_processor.hpp>

vecamole_create_options_t *vecamole_create_options_default() {
  try {
    vecamole_create_options_t *ptr = new struct vecamole_create_options;

    ptr->path_multiplier = 16;
    ptr->scale_factor = 1.0;
    ptr->offset_x = 0;
    ptr->offset_y = 0;
    ptr->area_threshold = 0.1;
    ptr->image_format = vecamole_image_format_JPEG;
    ptr->scaling_method = vecamole_scaling_method_NEAR;
    ptr->simplify_distance = 0.0;
    ptr->scale_denominator = 0.0;

    return ptr;

  } catch (...) {
    // bad alloc should be the only thing which is thrown
    return nullptr;
  }
}

int vecamole_create_options_delete(vecamole_create_options_t *ptr) {
  if (ptr != nullptr) {
    delete ptr;
    return 0;
  }

  return 1;
}

namespace {
struct callback_buffered_stream 
  : public google::protobuf::io::CopyingOutputStream {
  callback_buffered_stream(void *writer_private,
                           vecamole_tile_writer_func_t writer)
    : m_writer_private(writer_private)
    , m_writer(writer) {}

  virtual ~callback_buffered_stream() {}

  virtual bool Write(const void *buffer, int size) {
    return m_writer(m_writer_private, static_cast<const char *>(buffer), size) == size;
  }

private:
  void *m_writer_private;
  vecamole_tile_writer_func_t m_writer;
};

const std::string formats[] = {
  std::string("jpeg"),
  std::string("png")
};
} // anonymous namespace

int vecamole_create_tile(
  void *writer_private,
  vecamole_tile_writer_func_t writer,
  vecamole_map_t *c_map,
  vecamole_request_t *c_request,
  vecamole_create_options_t *opts) {

  using backend_type = mapnik::vector_tile_impl::backend_pbf;
  using renderer_type = mapnik::vector_tile_impl::processor<backend_type>;
  using tile_type = vector_tile::Tile;

  mapnik::Map *map = static_cast<mapnik::Map *>(c_map);
  mapnik::request *req = static_cast<mapnik::request *>(c_request);
  int total_len = -1;

  if ((map != nullptr) && (req != nullptr)) {
    tile_type tile;
    backend_type backend(tile, opts->path_multiplier);
    renderer_type renderer(backend, *map, *req,
                           opts->scale_factor, opts->offset_x, opts->offset_y,
                           opts->area_threshold, formats[opts->image_format],
                           mapnik::scaling_method_e(opts->scaling_method));

    renderer.set_simplify_distance(opts->simplify_distance);
    renderer.apply(opts->scale_denominator);

    callback_buffered_stream stream(writer_private, writer);
    google::protobuf::io::CopyingOutputStreamAdaptor adaptor(&stream);
    tile.SerializeToZeroCopyStream(&adaptor);

    int64_t byte_count = adaptor.ByteCount();
    assert(byte_count <= int64_t(std::numeric_limits<int>::max()));
    total_len = int(byte_count);
  }

  return total_len;
}

