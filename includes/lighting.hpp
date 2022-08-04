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

tCoord Dolighting(Material material,Light light,triangle& tr,tCoord cameraPosition);




#endif

