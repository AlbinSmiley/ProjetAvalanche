#!/bin/bash
set -e

echo "=== Build ==="

cmake -S . -B build
cmake --build build

echo "=== OK — exécutables dans build/bin/ ==="
echo ""
echo "Les éxutables sont les suivants :
  build/bin/
    ├── chute_libre
    ├── exerciceP12
    ├── exerciceP9
    ├── simulation
    ├── testAleatoire
    ├── testObstacle
    ├── testP5
    ├── testParticule
    ├── testSource
    ├── testSysteme
    ├── testTextViewer
    └── testVecteur3D"
