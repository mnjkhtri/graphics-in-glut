#include "includes/lighting.hpp"
#include "includes/threeDtransformations.hpp"
#include <iostream>

tCoord Dolighting(Material material, Light light, triangle& tr, tCoord cameraPosition)
{
  //ambient 
  tCoord ambient = material.ambient * light.ambient; 

  //diffuse 

  //calculating normals 
	tCoord vec1, vec2,normal ;

	vec1 = tr.tri[1] - tr.tri[0];
	vec2 = tr.tri[2] - tr.tri[0];
	normal = vec1.cross(vec2);
	normal.normalize();

	//calculating light position

	tCoord midPoint = (tr.tri[0] + tr.tri[1] + tr.tri[2]) * 0.3333; //treating the midpoint of a triangle to represent the whole surface
	tCoord lightVec = light.position - midPoint; //vector from point to light source 
	tCoord temp_lightVec = lightVec;
	lightVec.normalize();

	float diff = fmax(lightVec.dot(normal),0.0);


	tCoord diffuse = light.diffuse * (material.diffuse * diff);


	//specular 

	//calculating the viewPosition
	tCoord viewDir = cameraPosition - midPoint;
	viewDir.normalize();

	tCoord reflectDir = normal * (temp_lightVec.dot(normal)) * 2.0f - temp_lightVec;

	float spec = pow(fmax(reflectDir.dot(viewDir),0), material.shininess);
	
	//std::cout<<spec<<std::endl;
//float 	spec = 1;
	tCoord specular = light.specular * (material.specular * spec);

	// wrappin up

//	ambient.show();
//	std::cout<<std::endl;
/*	diffuse.show();
	std::cout<<std::endl;
	specular.show();
	std::cout<<std::endl<<std::endl;
*/ 	
//	tCoord final = ambient + diffuse + specular ;
    tCoord final = ambient + diffuse;
	return final;


}
