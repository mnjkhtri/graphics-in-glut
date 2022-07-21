#!/usr/bin/bash
g++ -I includes scanalgorithms.cpp twoDtransformations.cpp threeDtransformations.cpp $1 -o glout -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXrandr -lpthread -lXi
./glout
rm glout
