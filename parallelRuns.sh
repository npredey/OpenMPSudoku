#!/bin/sh

export OMP_NUM_THREADS=32
./parallel cases/worst-case.txt 32

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 32; done

for FILENAME in inputPuzzles/top95serial/*; do ./serial $FILENAME; done
