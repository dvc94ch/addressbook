### README

A simple address management program with a command line interface for
my 2016 C programming class.

### Usage

```sh
./addressbook
```

### Getting started

Install dependencies using guix

```sh
guix environment --pure -l guix.scm
```

If you are using a git checkout generate build files with autotools. If you
are using a tarball you should skip this step.

```sh
autoreconf -vfi
```

```sh
mkdir build
cd build
../configure

make
```

Run and install with

```sh
./addressbook

make install
```

### Running the tests

```sh
make check
```

### License

Author: David Craven <david@craven.ch>
License: GPL-3.0
