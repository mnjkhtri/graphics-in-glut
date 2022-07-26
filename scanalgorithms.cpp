#include <GL/glut.h>
#include <iostream>
#include <string>
#include "includes/scanalgorithms.hpp"


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
        Angel::putPixel(round(x),round(y), 1, Color(1.0f, 0.0f, 0.0f, 1.0f));
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
    Angel::putPixel(x,y);
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
            Angel::putPixel(x,y);
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

    Angel::putPixel(xr+x,yr+y);
    Angel::putPixel(xr+x,yr-y);
    Angel::putPixel(xr-x,yr+y);
    Angel::putPixel(xr-x,yr-y);
    Angel::putPixel(xr+y,yr+x);
    Angel::putPixel(xr+y,yr-x);
    Angel::putPixel(xr-y,yr+x);
    Angel::putPixel(xr-y,yr-x);
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
        Angel::putPixel(xr+x,yr+y);
        Angel::putPixel(xr+x,yr-y);
        Angel::putPixel(xr-x,yr+y);
        Angel::putPixel(xr-x,yr-y);
        Angel::putPixel(xr+y,yr+x);
        Angel::putPixel(xr+y,yr-x);
        Angel::putPixel(xr-y,yr+x);
        Angel::putPixel(xr-y,yr-x);
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
    Angel::putPixel(xr+x,yr+y);
    Angel::putPixel(xr+x,yr-y);
    Angel::putPixel(xr-x,yr+y);
    Angel::putPixel(xr-x,yr-y);

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
        Angel::putPixel(xr+x,yr+y);
        Angel::putPixel(xr+x,yr-y);
        Angel::putPixel(xr-x,yr+y);
        Angel::putPixel(xr-x,yr-y);
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
        Angel::putPixel(xr+x,yr+y);
        Angel::putPixel(xr+x,yr-y);
        Angel::putPixel(xr-x,yr+y);
        Angel::putPixel(xr-x,yr-y);
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

// draw triangle and fill accordingly
void RasterizeTriangle(tCoord vertices1, tCoord vertices2, tCoord vertices3,std::unordered_map<std::string,float>& zbuffer,Color co)
	{
		// not recommended but doing it anyways
		float height = 1000.0f;
		float width = 2000.0f;


		int x1 = vertices1.x, y1=vertices1.y;
		int x2 = vertices2.x, y2 = vertices2.y;
		int x3 = vertices3.x, y3 = vertices3.y;

		//finding out normals 

		tCoord vec1, vec2,normal ;

		vec1 = vertices2 - vertices1;
		vec2 = vertices3 - vertices1;
		normal = vec1.cross(vec2);


		// finding out d for eqn ax+by+cz+d = 0
		// a,b,c is given by the normal
		float d =   normal.x * vertices1.x + normal.y * vertices1.y + normal.z * vertices1.z ;


		auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };
		auto drawline = [&](int sx, int ex, int ny) 
		{ 
			//point clipping
			if(ny > height || ny < 0) 
				return ;

			if((sx<0 && ex < 0 )|| (sx>width && ex>width))
				return ;

			if (ex > width)
				ex = width;
			if(sx < 0)
				sx = 0;


			for (int i = sx; i <= ex; i++) 
			{
				//finding out z for the surface ax+by+cz+d = 0
				float z = (d - normal.x * i - normal.y *  ny)/normal.z;

				std::string key = std::to_string(i) +"+"+std::to_string(ny);

				//in case key is not found in the buffer we 
				if(zbuffer.find(key) == zbuffer.end())
				{
					zbuffer[key] = z;
					Angel::putPixel(i,ny,1,co);
				}

				else
				{
					if(zbuffer[key]>z)
					{
						zbuffer[key] = z;
						Angel::putPixel(i,ny,1,co);
					}
				}
			}

		};
		
		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		// Sort vertices
		if (y1>y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1>y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2>y3) { SWAP(y2, y3); SWAP(x2, x3); }


		t1x = t2x = x1; y = y1;   // Starting points
		dx1 = (int)(x2 - x1); 
		if (dx1<0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1);
		if (dx2<0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) {   // swap values
			SWAP(dx1, dy1);
			changed1 = true;
		}
		if (dy2 > dx2) {   // swap values
			SWAP(dy2, dx2);
			changed2 = true;
		}

		e2 = (int)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x<t2x) 
			{ minx = t1x; maxx = t2x; }
			else 
			{ minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i<dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)    
					break;
				else
					t2x += signx2;
			}
		next2:
			if (minx>t1x) minx = t1x; 
			if (minx>t2x) minx = t2x;

			if (maxx<t1x) maxx = t1x; 
			if (maxx<t2x) maxx = t2x;

			drawline(minx, maxx, y);    // Draw line from min to max points found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		// Second half
		dx1 = (int)(x3 - x2); 
		if (dx1<0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x<t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i<dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i<dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) 
						t2xp = signx2;
					else
						goto next4;
				}
				if (changed2) 
					break;
				else
					t2x += signx2;
			}
		next4:

			if (minx>t1x) minx = t1x;
			if (minx>t2x) minx = t2x;

			if (maxx<t1x) maxx = t1x; 
			if (maxx<t2x) maxx = t2x;

			drawline(minx, maxx, y);   										

			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y>y3) return;
		}
	}


