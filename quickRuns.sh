#!/bin/sh

export OMP_NUM_THREADS=2

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 2 >> output/parallel2.txt; done

#grep -e '^Solved' output/fullRunParallel.txt > output/solvedParallel.txt

#awk '{gsub("Solved:", "");print}' output/solvedParallel.txt > timeOnly.txt

#echo $threads 'threads' > sum.txt
#awk '{ sum += $1 } END { print sum }' timeOnly.txt > sum.txt

export OMP_NUM_THREADS=4

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 4 >> output/parallel4.txt; done
export OMP_NUM_THREADS=8

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 8 >> output/parallel8.txt; done
export OMP_NUM_THREADS=16

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 16 >> output/parallel16.txt; done
export OMP_NUM_THREADS=32

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 32 >> output/parallel32.txt; done
export OMP_NUM_THREADS=64

for FILENAME in inputPuzzles/top95parallel/*; do ./parallel $FILENAME 64 >> output/parallel64.txt; done

