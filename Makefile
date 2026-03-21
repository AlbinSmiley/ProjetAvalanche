# -------- Compilateur --------
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc

# -------- Fichiers --------
SRC = src/Vecteur3D.cc
SRC += src/Particule.cc 
SRC += src/Aleatoire.cc 
SRC += src/Source.cc 
# TEST = tests/testVecteur3D.cc
# EXEC = build/bin/testVecteur3D
# TEST = tests/testParticule.cc
# EXEC = build/bin/testParticule
# TEST = tests/testAleatoire.cc
# EXEC = build/bin/testAleatoire
TEST = tests/testSource.cc
EXEC = build/bin/testSource

all: $(EXEC)

$(EXEC): $(SRC) $(TEST)
	mkdir -p ./build/bin/
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run
