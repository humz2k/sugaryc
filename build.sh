#!/usr/bin/env bash

cd ext/bdwgc
make -f makefile.direct clean
make -f makefile.direct
cd ..

cd cstdlib
make clean
make all -j
cd ..

cd stdlib
make clean
make libsgc.a -j
cd ..

cd pycparser
rm -rf lextab.py
rm -rf yacctab.py
python3 _build_tables.py
cd ..

cd examples
make clean
make -j
cd ..
