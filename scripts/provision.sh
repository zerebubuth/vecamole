#!/bin/bash

add-apt-repository -y ppa:mapnik/nightly-trunk;
apt-get update;
apt-get install -y libmapnik-dev="3.0.0+dev20150801.git.6b05f19-1~trusty1" ;

apt-get install -y git build-essential automake autoconf libtool;

apt-get install -y protobuf-compiler libprotobuf-dev;
