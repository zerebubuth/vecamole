#!/bin/bash

set -e

function check {
    file="deps/$1/$2"
    if [ ! -f "$file" ]; then
	echo "Dependency on $1 appears to be missing. You might need to run 'git submodule update --init --recursive."
	exit 1
    fi
}

check "mapnik-vector-tile" "src/vector_tile_backend_pbf.hpp"
check "mapnik-vector-tile" "src/vector_tile_processor.hpp"
check "clipper" "cpp/clipper.hpp"
check "protozero" "include/protozero/pbf_reader.hpp"
check "protozero" "include/protozero/pbf_writer.hpp"

libtoolize
aclocal -I m4
autoreconf --force --install

echo "Now run ./configure"
