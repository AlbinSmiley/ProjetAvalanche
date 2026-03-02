CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17 -Wall

all: testVecteur3D

testVecteur3D: Vecteur3D.o testVecteur3D.o

testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
Vecteur3D.o: Vecteur3D.cc Vecteur3D.h 