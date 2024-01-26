#!/usr/bin/env bash

cd cstdlib
make clean
make all
cd ..
cd stdlib
make clean
make libsgc.a