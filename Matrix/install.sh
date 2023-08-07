#!/bin/bash
VERSION=1.0.1
LIBNAME=libmatrixcpp
FILENAME=${LIBNAME}.so.${VERSION}

g++ -fPIC -c matrix.cpp
echo 'matrix.o generated'
g++ -shared -Wl,-soname,${LIBNAME}.so -o ${FILENAME} matrix.o
echo 'libmatrixcpp.so.1.0.1 generated'

cp ${FILENAME} /usr/local/lib/
echo 'library file copied'
ln -s /usr/local/lib/${FILENAME} /usr/local/lib/${LIBNAME}.so
echo 'successfully linked'
ldconfig
echo 'done.'
