ACLOCAL_AMFLAGS=-I m4
AM_LDFLAGS = @BOOST_LDFLAGS@
AM_CPPFLAGS = \
	-Iinclude -Iprivate_include \
	-Ideps/mapnik-vector-tile/src -Ideps/protozero/include \
	-DMAPNIK_VECTOR_TILE_LIBRARY \
	-DCLIPPER_INTPOINT_IMPL='mapnik::geometry::point<cInt>' \
	-DCLIPPER_PATH_IMPL='mapnik::geometry::line_string<cInt>' \
	-DCLIPPER_PATHS_IMPL='mapnik::geometry::multi_line_string<cInt>' \
	-DCLIPPER_IMPL_INCLUDE='<mapnik/geometry.hpp>' \
	@BOOST_CPPFLAGS@ @MAPNIK_CPPFLAGS@ @PROTOC_CPPFLAGS@

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

lib_LTLIBRARIES = \
	libvecamole.la

libvecamole_la_SOURCES = \
	deps/mapnik-vector-tile/src/vector_tile_backend_pbf.cpp \
	deps/mapnik-vector-tile/src/vector_tile_compression.cpp \
	deps/mapnik-vector-tile/src/vector_tile_datasource.cpp \
	deps/mapnik-vector-tile/src/vector_tile_processor.cpp \
	deps/mapnik-vector-tile/src/vector_tile_util.cpp \
	deps/mapnik-vector-tile/src/vector_tile_datasource_pbf.cpp \
	deps/mapnik-vector-tile/src/vector_tile_projection.cpp \
	src/vector_tile.pb.cc \
	src/clipper.cpp \
	src/map.cpp \
	src/request.cpp \
	src/create.cpp \
	src/datasource.cpp

libvecamole_la_LIBADD = \
	@MAPNIK_LIBS@ @PROTOC_LIBS@

check_PROGRAMS = \
	test/test_create \
	test/test_request_zxy

TESTS = $(check_PROGRAMS)

test_test_create_SOURCES = test/test_create.c
test_test_create_CPPFLAGS = -Iinclude
test_test_create_LDADD = libvecamole.la
test_test_request_zxy_SOURCES = test/test_request_zxy.c
test_test_request_zxy_CPPFLAGS = -Iinclude
test_test_request_zxy_LDADD = libvecamole.la

BUILT_SOURCES = \
	private_include/vector_tile.pb.h \
	private_include/clipper.hpp \
	src/vector_tile.pb.cc \
	src/clipper.cpp

CLEANFILES = $(BUILT_SOURCES)

src/vector_tile.pb.cc: private_include/vector_tile.pb.h

private_include/vector_tile.pb.h: deps/mapnik-vector-tile/proto/vector_tile.proto
	$(AM_V_GEN)@PROTOC_BIN@ -Ideps/mapnik-vector-tile/proto --cpp_out=src $< && \
	mkdir -p private_include && \
	mv src/vector_tile.pb.h private_include/

src/clipper.cpp: deps/clipper/cpp/clipper.cpp
	$(AM_V_GEN)cp $< $@ && \
	perl -i -p -e "s/\.X/\.x/g;" $@ && \
	perl -i -p -e "s/\->X/\->x/g;" $@ && \
	perl -i -p -e "s/cInt X;/cInt x;/g;" $@ && \
	perl -i -p -e "s/double X;/double x;/g;" $@ && \
	perl -i -p -e "s/X\(x\)/x\(_x\)/g;" $@ && \
	perl -i -p -e "s/X\(\(/x\(\(/g;" $@ && \
	perl -i -p -e "s/double x = 0/double _x = 0/g;" $@ && \
	perl -i -p -e "s/cInt x = 0/cInt _x = 0/g;" $@ && \
	perl -i -p -e "s/\.Y/\.y/g;" $@ && \
	perl -i -p -e "s/\->Y/\->y/g;" $@ && \
	perl -i -p -e "s/cInt Y;/cInt y;/g;" $@ && \
	perl -i -p -e "s/double Y;/double y;/g;" $@ && \
	perl -i -p -e "s/Y\(y\)/y\(_y\)/g;" $@ && \
	perl -i -p -e "s/Y\(\(/y\(\(/g;" $@ && \
	perl -i -p -e "s/cInt          Y;/cInt          y;/g;" $@ && \
	perl -i -p -e "s/double y = 0/double _y = 0/g;" $@ && \
	perl -i -p -e "s/cInt y = 0/cInt _y = 0/g;" $@

private_include/clipper.hpp: deps/clipper/cpp/clipper.hpp
	$(AM_V_GEN)cp $< $@ && \
	perl -i -p -e "s/\.X/\.x/g;" $@ && \
	perl -i -p -e "s/\->X/\->x/g;" $@ && \
	perl -i -p -e "s/cInt X;/cInt x;/g;" $@ && \
	perl -i -p -e "s/double X;/double x;/g;" $@ && \
	perl -i -p -e "s/X\(x\)/x\(_x\)/g;" $@ && \
	perl -i -p -e "s/X\(\(/x\(\(/g;" $@ && \
	perl -i -p -e "s/double x = 0/double _x = 0/g;" $@ && \
	perl -i -p -e "s/cInt x = 0/cInt _x = 0/g;" $@ && \
	perl -i -p -e "s/\.Y/\.y/g;" $@ && \
	perl -i -p -e "s/\->Y/\->y/g;" $@ && \
	perl -i -p -e "s/cInt Y;/cInt y;/g;" $@ && \
	perl -i -p -e "s/double Y;/double y;/g;" $@ && \
	perl -i -p -e "s/Y\(y\)/y\(_y\)/g;" $@ && \
	perl -i -p -e "s/Y\(\(/y\(\(/g;" $@ && \
	perl -i -p -e "s/cInt          Y;/cInt          y;/g;" $@ && \
	perl -i -p -e "s/double y = 0/double _y = 0/g;" $@ && \
	perl -i -p -e "s/cInt y = 0/cInt _y = 0/g;" $@

