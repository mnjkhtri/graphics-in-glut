#include <iostream>
#include "threeDtransformations.hpp"
using namespace std;

int main()
{
    //Coordinates of a cube (will act as a buffer)
    const int COUNT = 24;
    tCoord coordinates[] = 
    {
        tCoord(0,0,0), tCoord(0,0,500), tCoord(0,500,500), tCoord(0,500,0),
        tCoord(0,0,0), tCoord(0,0,500), tCoord(500,0,0), tCoord(500,0,500),
        tCoord(0,500,0), tCoord(0,500,500), tCoord(500,500,500), tCoord(500,500,0),
        tCoord(0,0,500), tCoord(0,500,500), tCoord(500,0,500), tCoord(500,500,500),
        tCoord(0,0,0), tCoord(0,500,0), tCoord(500,0,0), tCoord(500,500,0),
        tCoord(500,0,0), tCoord(500,0,500), tCoord(500,500,500), tCoord(500,500,0)
    };

    tCoord reference(5,0,0);
    tCoord Nvector(1,0,0);
    tCoord Vvector(0,1,0);

    tMatrix ourViewMatrix;
    viewMatrix(&ourViewMatrix, &reference, &Nvector, &Vvector);
    DoviewMatrix(&ourViewMatrix, coordinates, COUNT);
    
    DocabinetMatrix(30, coordinates, COUNT);


}