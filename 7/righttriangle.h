#pragma once
#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

const double pi = 3.1415926535;

class righttriangle:public Shape
{
private:
    double x, y, w, h;
public:
    int ty;
	righttriangle(double xx=0,double yy=0,double ww=0,double hh=0):x(xx),y(yy),w(ww),h(hh) {}

    void set_angle(int t) { ty = t; work(); }

    double cosx(int x)
    {
        if (x < 0) x = -x;
        switch (x)
        {
        case 0: return 1;
        case 45:case 315: return sqrt(2)/2.000000;
        case 90:case 270: return 0;
        case 135:case 225: return -sqrt(2)/2.0000000;
        case 180:case 360: return -1;
        }
    }

    double sinx(int x)
    {
        return cosx(90 - x);
    }

    void work()
    {
        /*Shape::add(Point(x, y));
        Shape::add(Point(x + w * cosi(pi * ty / 180), y + w * sin(pi * ty / 180)));
        Shape::add(Point(x - h * sin(pi * ty / 180), y + h * cos(pi * ty / 180)));*/
        
        Shape::add(Point(x, y));
        Shape::add(Point(x + w * cosx(ty), y + w * sinx(ty)));
        Shape::add(Point(x - h * sinx(ty), y + h * cosx(ty)));

        //for (int i = 0; i < 3; i++)
        //    cout << point(i).x <<' '<< point(i).y << endl;

        
    }

    void draw_lines()const
	{
        if (fill_color().visibility()) {    // fill
            fl_color(fill_color().as_int());
            fl_polygon(point(0).x, point(0).y, point(1).x, point(1).y,point(2).x,point(2).y);
        }

        if (color().visibility()) {    // lines on top of fill
            fl_color(color().as_int());
            fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
            fl_line(point(1).x, point(1).y, point(2).x, point(2).y);
            fl_line(point(2).x, point(2).y, point(0).x, point(0).y);
        }
	}
};

#endif
