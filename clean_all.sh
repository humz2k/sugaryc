#!/usr/bin/env bash

cd cstdlib
make clean
cd ..

cd pycparser
rm -rf lextab.py
rm -rf yacctab.py
cd ..

cd stdlib
make clean
cd ..

cd examples
make clean
cd ..

cd ext/bdwgc
make -f makefile.direct clean
cd ..