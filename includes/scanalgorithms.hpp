#ifndef SCAN_INCLUDED
#define SCAN_INCLUDED

#include<bits/stdc++.h>
#include "twoDtransformations.hpp"
#include "threeDtransformations.hpp"
#include "Angel.hpp"
#include <string>

void LineDDA(Coord, Coord);
void LineBresenham(Coord, Coord);
void Circle(Coord, int);
void Ellipse(Coord, int, int);
void Square(Coord, Coord, Coord, Coord);
void putPixel(int , int , int, int, int);

void RasterizeTriangle(tCoord vertices1, tCoord vertices2, tCoord vertices3, std::unordered_map<std::string,float>& zbuffer, Color co);
void DrawAFloor(cube array_of_vertices, std::unordered_map<std::string,float>& zbuffer, Color co);
#endif
