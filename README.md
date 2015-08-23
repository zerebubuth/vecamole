# Vecamole

A simple C library to wrap [Mapnik](http://mapnik.org)'s vector tile creating and rendering functions.

## Motivation

Mapnik is an awesome library which does a huge number of things and exports a very rich API in C++ and Python (and [Ruby](https://github.com/mapnik/Ruby-Mapnik), [C](https://github.com/springmeyer/mapnik-c-api)). However, sometimes you only need a very small part of that API and it's easier to hide away a lot of the richness and complexity for a smaller, simpler and easier to manage interface. This is an attempt to do that for Mapnik's vector tile creation and rendering functionality.

## Installation

These installation instructions assume you're running Ubuntu 14.04, but will probably work with some adaptation on other flavours of Linux. If you're not running Linux then YMMV, and it might be easier to run Vagrant as described in the next section.

Firstly, you'll need Mapnik. I recommend using the same version as I'm using:

```
sudo add-apt-repository -y ppa:mapnik/nightly-trunk
sudo apt-get update
sudo apt-get install libmapnik-dev="3.0.0+dev20150801.git.6b05f19-1~trusty1"
```

And you'll need a few essential libraries and tools:

```
sudo apt-get install git build-essential automake autoconf libtool protobuf-compiler libprotobuf-dev
```

Next, make sure you've got all the submodules installed:

```
git submodule update --init --recursive
```

After all of that, it should be a standard autotools build:

```
./autogen.sh
./configure
make
make check
make install
```

Note that I seem to occasionally get some issues with parallel builds, so please check a single-threaded build if you find your builds are failing. Better still, contribute a patch to fix it!

## Using Vagrant

In order to make getting started easier, the repository contains a [Vagrant](https://www.vagrantup.com/) configuration. To get started using this requires only Vagrant itself to be installed on your system, and all the crazy PPA stuff is confined to a VM. After installing Vagrant itself, you should be able to get a VM ready for development by running:

```
vagrant up
```

And then running the build inside it:

```
vagrant ssh
cd /vagrant
./autogen.sh
./configure
make
make check
```

## Contributing

Contributions are very welcome! Please send pull requests to the [Github project](https://github.com/zerebubuth/vecamole/pulls) or via email to me. If you find any bugs, build issues or other problems then please report them on [Github issues](https://github.com/zerebubuth/vecamole/issues/new). The coding style for the project is pretty loose, but generally [1TBS](https://en.wikipedia.org/wiki/Indent_style#Variant:_1TBS) with a 2-space indent.
