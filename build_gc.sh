#!/usr/bin/env bash

cd ext/bdwgc
make -f makefile.direct clean
make -f makefile.direct
cd ..