#include <GL/glut.h>
#include <iostream>
#include "includes/scanalgorithms.hpp"

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();  
}
int round(float x)
{
    return int(x+0.5);
}
//All lines with positive slopes
void LineDDA(Coord first, Coord second)
{
    int x1 = first.x;
    int yy = first.y;
    int x2 = second.x;
    int y2 = second.y;

    int dx = x2 - x1;
    int dy = y2 - yy;
 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float xinc = dx / (float) steps;
    float yinc = dy / (float) steps;
 
    float x = x1;
    float y = yy;
    for (int i = 0; i <= steps; i++)
    {
        putPixel (round(x),round(y));
        x += xinc;
        y += yinc;
    }
}
//Positive slopes with lower part of quadrant
void LineBresenham(Coord first, Coord second)
{
    int x1 = first.x;
    int yy = first.y;
    int x2 = second.x;
    int y2 = second.y;

    int dy = y2-yy;
    int dx = x2-x1;
    float m = (float)dy/dx;;
    int steps;

    int twoDy = 2*dy;
    int twoDyDx = 2*(dy-dx);

    int par;
    int x = x1;
    int y = yy;
    putPixel(x,y);
    if (m <= 1)
    {
        //The lower part of the quandrant
        steps = dx;
        //the y increment will be floating:
        par = 2*dy-dx;
        for (int k = 0; k < steps; ++k)
        {
            x += 1;
            if (par < 0)
            {
                par += twoDy;
                y += 0;
            }
            else
            {
                par += twoDyDx;
                y += 1;
            }
            putPixel(x,y);
        }
    }
    if (m > 1)
    {
        //The upper part of the quadrant
    }
}
//All circles
void Circle(Coord center, int r)
{

    int xr = center.x;
    int yr = center.y;
    int x = 0;
    int y = r;
    int p = 1-r;

    putPixel(xr+x,yr+y);
    putPixel(xr+x,yr-y);
    putPixel(xr-x,yr+y);
    putPixel(xr-x,yr-y);
    putPixel(xr+y,yr+x);
    putPixel(xr+y,yr-x);
    putPixel(xr-y,yr+x);
    putPixel(xr-y,yr-x);
    while (x < y)
    {
        x += 1;
        if (p < 0)
        {
            p += 2*x+1;
        }
        else
        {
            y -= 1;
            p += 2*(x-y)+1;
        }
        putPixel(xr+x,yr+y);
        putPixel(xr+x,yr-y);
        putPixel(xr-x,yr+y);
        putPixel(xr-x,yr-y);
        putPixel(xr+y,yr+x);
        putPixel(xr+y,yr-x);
        putPixel(xr-y,yr+x);
        putPixel(xr-y,yr-x);
    }
}
//All ellipses
void Ellipse(Coord center, int rx, int ry)
{
    int xr = center.x;
    int yr = center.y;
    int rx2 = rx*rx;
    int ry2 = ry*ry;
    int tworx2 = 2*rx2;
    int twory2 = 2*ry2;
    int x = 0;
    int y = ry;
    int px = 0;
    int py = tworx2*y;
    putPixel(xr+x,yr+y);
    putPixel(xr+x,yr-y);
    putPixel(xr-x,yr+y);
    putPixel(xr-x,yr-y);

    int p = round(ry2-(rx2*ry)+(0.25*rx2));
    
    while (px < py)
    {
        x += 1;
        px += twory2;
        if (p < 0)
        {
            p += ry2+px;
        }
        else
        {
            y -= 1;
            py -= tworx2;
            p += ry2+px-py;
        }
        putPixel(xr+x,yr+y);
        putPixel(xr+x,yr-y);
        putPixel(xr-x,yr+y);
        putPixel(xr-x,yr-y);
    }

    p = round(ry2*(x+0.5)*(x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2);
    while (y > 0)
    {
        y -= 1;
        py -= tworx2;
        if (p > 0)
        {
            p += rx2-py;
        }
        else
        {
            x += 1;
            px += twory2;
            p += rx2-py+px;
        }
        putPixel(xr+x,yr+y);
        putPixel(xr+x,yr-y);
        putPixel(xr-x,yr+y);
        putPixel(xr-x,yr-y);
    }
}
//Need vertices in order
void Square(Coord first, Coord second, Coord third, Coord forth)
{
    LineDDA(first, second);
    LineDDA(first, forth);
    LineDDA(second, third);
    LineDDA(forth, third);
}
