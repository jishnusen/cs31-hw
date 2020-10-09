#!/bin/bash

files=(`unzip -Z1 $1`)
required_names=("compile_error.cpp" "logic_error.cpp" "original.cpp" "report.txt")

for t in ${files[@]}; do
  [[ " ${required_names[@]} " =~ " ${t} " ]] && echo "Found: ${t}" || echo "Unknown File: ${t}"
done

