# -------- Compilateur --------
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc

# -------- Fichiers --------
SRC = src/Vecteur3D.cc
SRC += src/Particule.cc 
# TEST = tests/testVecteur3D.cc
# EXEC = build/bin/testVecteur3D
TEST = tests/testParticule.cc
EXEC = build/bin/testParticule

all: $(EXEC)

$(EXEC): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run
