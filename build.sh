#!/bin/bash

set -xe

cc -O3 -o spotlight spotlight.c -Iraylib/include raylib/lib/libraylib.a -lm