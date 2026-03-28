# -------- Compilateur --------
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc

# -------- Fichiers --------
SRC = src/Vecteur3D.cc
SRC += src/Particule.cc 
SRC += src/Aleatoire.cc  
SRC += src/Plan.cc
SRC += src/Source.cc  
SRC += src/Obstacle.cc
SRC += src/Dalle.cc
SRC += src/Systeme.cc
SRC += src/TextViewer.cc

# -------- Test --------

TEST = tests/testSysteme.cc
EXEC = build/bin/testSysteme
# TEST = tests/testVecteur3D.cc
# EXEC = build/bin/testVecteur3D
# TEST = tests/testParticule.cc
# EXEC = build/bin/testParticule
# TEST = tests/testAleatoire.cc
# EXEC = build/bin/testAleatoire
# TEST = tests/testObstacle.cc
# EXEC = build/bin/testObstacle
#TEST = tests/testSource.cc
#EXEC = build/bin/Source

all: $(EXEC)

$(EXEC): $(SRC) $(TEST)
	mkdir -p ./build/bin/
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run
