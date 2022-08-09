#include "includes/lighting.hpp"
#include "includes/threeDtransformations.hpp"
#include <iostream>

void Dolighting(cube& mesh, tCoord cameraPosition, tCoord lightPosition)
{
  for (auto& tr: mesh.triangles)
  {
	  light(tr, cameraPosition, lightPosition);
  }
}
void light(triangle& tr, tCoord cameraPosition,tCoord lightPosition)
{
  tCoord lightColor = tCoord(1.0f, 1.0f, 1.0f);
  //ambient 
  float ambient_strength = 0.4;
  tCoord ambient = lightColor * ambient_strength; 

  //diffuse 

  //calculating normals 
	tCoord vec1, vec2,normal ;

	vec1 = tr.tri[1] - tr.tri[0];
	vec2 = tr.tri[2] - tr.tri[0];
	normal = vec1.cross(vec2);
	normal.normalize();

	//calculating light position

	tCoord midPoint = (tr.tri[0] + tr.tri[1] + tr.tri[2]) * 0.3333; //treating the midpoint of a triangle to represent the whole surface
	tCoord lightVec = lightPosition - midPoint; //vector from point to light source 
//	tCoord temp_lightVec = lightVec;
	lightVec.normalize();

	float diff = fmax(lightVec.dot(normal),0.0);

	tCoord diffuse = lightColor * diff; 

	//specular 
	/*
	float specular_strength = 0.5;

	//calculating the viewPosition
 	tCoord viewDir = cameraPosition - midPoint;
 	viewDir.normalize();

 	tCoord reflectDir = normal * (temp_lightVec.dot(normal)) * 2.0f - temp_lightVec;

 	float spec = pow(fmax(reflectDir.dot(viewDir),0), 0.025)  ;
	
// 	//std::cout<<spec<<std::endl;
// //float 	spec = 1;
 	tCoord specular = lightColor * (spec * specular_strength) ; 

// 	// wrappin up

// //	ambient.show();
// //	std::cout<<std::endl;
// 	diffuse.show();
// 	std::cout<<std::endl;
// 	specular.show();
// 	std::cout<<std::endl<<std::endl;
//  	
 	//tCoord temp= ambient + diffuse + specular ;
	*/
     
      tCoord temp = ambient + diffuse ;

	  tr.color = Color(temp.x*tr.color.r,temp.y * tr.color.g, temp.z * tr.color.b);


}
