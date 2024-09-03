#!/usr/bin/sh

NEW_FILE_NUM=$(($(find ./tests/input -type f | wc -l) + 1))
touch ./tests/input/case"$NEW_FILE_NUM".txt ./tests/output/case"$NEW_FILE_NUM".txt
cp input.txt ./tests/input/case"$NEW_FILE_NUM".txt
cp output.txt ./tests/output/case"$NEW_FILE_NUM".txt