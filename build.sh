#!/bin/sh

cmake -S . -G "Unix Makefiles" -B build
make -C build