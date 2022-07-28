#!/usr/bin/bash
g++ -I includes $1 Angel.cpp twoDtransformations.cpp threeDtransformations.cpp scanalgorithms.cpp glad.c -o glout -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm -lassimp
./glout
rm glout
