#!/bin/sh



for FILENAME in output/*; do grep -e '^Solved' $FILENAME >> cleanedOutput/cleanedOutput.txt; done

for FILENAME in cleanedOutput/*; do awk '{gsub("Solved:", "");print}' cleanedOutput/cleanedOutput.txt > sumTimes.txt; done

