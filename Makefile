# CXX = g++
# CC = $(CXX)
# CXXFLAGS = -std=c++17 -Wall
#
# all: testVecteur3D
#
# testVecteur3D: Vecteur3D.o testVecteur3D.o
#
# testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
# Vecteur3D.o: Vecteur3D.cc Vecteur3D.h 

# -------- Compilateur --------
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc   # <-- important

# -------- Fichiers --------
SRC = src/Vecteur3D.cc
TEST = tests/testVecteur3D.cc
EXEC = testVecteur3D

all: $(EXEC)

$(EXEC): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run
