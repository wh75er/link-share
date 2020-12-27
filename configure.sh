#!/bin/bash

# Конфигурационный файл для CI

TYPE=Debug

if [[ -n $1 ]]; then
  echo "Overriding TYPE=$TYPE with $1..."
  TYPE=$1
fi

echo "Configured TYPE=$TYPE"

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=$TYPE ..

exit 0
