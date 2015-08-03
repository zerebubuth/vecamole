#!/bin/bash

set -e

libtoolize
aclocal -I m4
autoreconf --force --install

echo "Now run ./configure"
