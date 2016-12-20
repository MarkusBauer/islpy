#!/usr/bin/env bash

python configure.py --cxxflags "-O3,-flto" --ldflags "-O3,-flto"
CC=clang CXX=clang++ python setup.py build
