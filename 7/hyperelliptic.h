#pragma once
#ifndef HYPERELLIPTIC_H
#define HYPERELLIPTIC_H

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

class hyperelliptic
{
private:
	double a, b, m, n;
	int N,cou;
	Point slope[10005];
public:
	hyperelliptic(double aa = 0, double bb = 0, double mm = 0, double nn = 0, int NN = 0) :a(aa), b(bb), m(mm), n(nn), N(NN) { cou = 0; memset(slope, 0, sizeof(slope)); }
	void work()
	{
		using namespace Graph_lib;   // our graphics facilities are in Graph_lib
		Point tl(100, 100);           // to become top left  corner of window
		Simple_window win(tl, 600, 600, "Canvas");    // make a simple window
		double zx=300, zy = 300;
		double step = 2 * a / (1.00000000 * (N - 1));
		Lines li;
		for (int i = N-1; i >=0; i--)
			if((-a + i * step)>=0)
			{
				slope[++cou]=Point(zx +50*(-a + i * step), zy + 50*b * pow(1 - pow((-a + i * step) / a, m), 1.0000000 / n));
				slope[++cou] = Point(zx - 50 * (-a + i * step), zy + 50 * b * pow(1 - pow((-a + i * step) / a, m), 1.0000000 / n));
				if (i == N - 1) continue;
				slope[++cou] = Point(zx + 50 * (-a + i * step), zy - 50 * b * pow(1 - pow((-a + i * step) / a, m), 1.0000000 / n));
				slope[++cou] = Point(zx - 50 * (-a + i * step), zy - 50 * b * pow(1 - pow((-a + i * step) / a, m), 1.0000000 / n));
			}
		for (int i = 1; i <= cou; i++)
			for (int j = i + 1; j <= cou; j++)
				li.add(slope[i], slope[j]);
		li.set_color(Color::blue);
		win.attach(li);           // connect poly to the window
		win.wait_for_button();       // give control to the display engine
	}
};

#endif

