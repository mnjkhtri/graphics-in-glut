#ifndef THREE_INCLUDED
#define THREE_INCLUDED

#include<bits/stdc++.h>

#include "twoDtransformations.hpp"
#include "scanalgorithms.hpp"
class tCoord
{
    public:
        float x;
        float y;
        float z;
        float h;
		tCoord(){}
        tCoord(float, float, float);
        tCoord(float, float, float, float);
		float dot(tCoord);
		tCoord operator* (float);
		tCoord operator + (tCoord);
		tCoord operator - (tCoord);
		tCoord cross(tCoord);
		void normalize();
        void show();
};

class tMatrix
{
    public:
        float a11, a12, a13, a14;
        float a21, a22, a23, a24;
        float a31, a32, a33, a34;
        float a41, a42, a43, a44; 
        tMatrix();  
        tMatrix(float, float, float, float, float, float, float, float, float);
        void add(tMatrix *toadd);
        void product(float val);  
        void multiply(tMatrix *tomul);
        void assignMatrix(tMatrix *toassign);
        void show();
};

void ttranslateMatrix(tMatrix* ourMatrix, float tx, float ty, float tz);

void trotateMatrix(tMatrix* ourMatrix, float theta, tCoord vec);

void toriginscaleMatrix(tMatrix* ourMatrix, float sx, float sy, float sz);

void tpivotscaleMatrix(tMatrix* ourMatrix, float sx, float sy, float sz, tCoord pivot);

void tdoTransform(tCoord* arr, tMatrix* ourMatrix);

void viewMatrix(tMatrix *unitMatrix, tCoord *reference, tCoord *Nvector, tCoord *Vvector);

void DoviewMatrix(tMatrix *ourViewMatrix, tCoord *vertices, int noOfVertices);

void DocabinetMatrix(float phi, tCoord *vertices, int noOfVertices);

void DocavalierMatrix(float phi, tCoord *vertices, int noOfVertices);

void DoperspectiveMatrix(tCoord *vanishpoint, tCoord *vertices, int noOfVertices);

void DoTranslateMatrix(float tx, float ty, float tz, tCoord *vertices, int noOfVertices);

void DoRotateMatrix(float theta, tCoord axis, tCoord *vertices, int noOfVertices);
//void Dozbuffer(std::vector<bool>& zbuffer,tCoord* coordinates, int noOfVertices,tCoord cameraPosition = tCoord(0,0,0));

std::vector<bool> Dozbuffer(tCoord* coordinates, int noOfVertices,tCoord cameraPosition = tCoord(0,0,0));

void Plotvertices(tCoord *coordinates,std::vector<bool>& zbuffer, int COUNT);


#endif
