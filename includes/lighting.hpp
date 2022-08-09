#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include"threeDtransformations.hpp"

struct Material
{
	tCoord ambient;
	tCoord diffuse;
	tCoord specular;

	float shininess;
};

struct Light 
{
	tCoord position;

	tCoord ambient;
	tCoord diffuse;
	tCoord specular;
};

void light(triangle& tr,tCoord cameraPosition,tCoord lightPosition );
void Dolighting(cube& mesh, tCoord cameraPosition, tCoord lightPosition);




#endif

