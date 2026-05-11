#!/bin/bash
set -e

echo "=== Build ==="
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel "$(nproc)"

echo "=== OK — exécutables dans build/bin/ ==="
