#!/usr/bin/env bash

cd cstdlib
make clean
make all
cd ..

cd stdlib
make clean
make libsgc.a
cd ..

cd pycparser
rm -rf lextab.py
rm -rf yacctab.py
python3 _build_tables.py
cd ..

cd examples
make clean
make
cd ..
