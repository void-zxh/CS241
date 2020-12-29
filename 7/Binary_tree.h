#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

struct CircleNode:Shape
{
	int l;
	CircleNode() {}
	CircleNode(Point p, int rr) :r(rr) { add(Point(p.x - r, p.y - r)); }
	void draw_lines() const
	{
		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}
private:
	int r;
};

struct TriangleNode :Shape
{
	int l;
	TriangleNode() {}
	TriangleNode(Point p, int rr) :r(rr) { add(p); add(Point(p.x - r, p.y + 2 * r)); add(Point(p.x + r, p.y + 2 * r)); }
	void draw_lines() const
	{
		if (fill_color().visibility()) {    // fill
			fl_color(fill_color().as_int());
			fl_polygon(point(0).x, point(0).y, point(1).x, point(1).y, point(2).x, point(2).y);
		}

		if (color().visibility()) {    // lines on top of fill
			fl_color(color().as_int());
			fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
			fl_line(point(1).x, point(1).y, point(2).x, point(2).y);
			fl_line(point(2).x, point(2).y, point(0).x, point(0).y);
		}
	}
private:
	int r;
};

class Binary_tree :public Shape
{
private:
	int levels,cou;
	CircleNode *cir[305];
	Lines li;

public:
	Binary_tree(int le = 0) { levels = le; cou = pow(2, levels) - 1; }
	void work()
	{
		//Shape::add(Point(300, 300));
		//Shape::add(Point(400, 200));
		//Shape::add(Point(400, 400));
		Point x,y;
		double r=10,lo;
		if (levels == 0) return;
		cir[1]=new CircleNode(Point(600, 80), r);
		cir[1]->l = pow(2, levels - 1) * 30 + cou * 10;
		cir[1]->set_color(Color::black);
		cir[1]->set_fill_color(Color::magenta);
		for(int i=2;i<=cou;i++)
			if (i & 1)
			{
				x = cir[i / 2]->point(0);
				lo = cir[i / 2]->l;
				cir[i] = new CircleNode(Point(x.x+r+lo/2, x.y+r+50), r);
				cir[i]->l = (lo - 10)/2.0000000;
				cir[i]->set_color(Color::black);
				cir[i]->set_fill_color(Color::red);
			}
			else
			{
				x = cir[i / 2]->point(0);
				lo = cir[i / 2]->l;
				cir[i] = new CircleNode(Point(x.x+r-lo / 2, x.y+r+50), r);
				cir[i]->l = (lo - 10) / 2.000000;
				cir[i]->set_color(Color::black);
				cir[i]->set_fill_color(Color::yellow);
			}
		set_color(Color::black);
		for (int i = 1; i <= cou / 2; i++)
		{
			x = cir[i]->point(0);
			y = cir[i << 1]->point(0);
			li.add(Point(x.x + r, x.y + r), Point(y.x + r, y.y + r));
			x = cir[i]->point(0);
			y = cir[i << 1|1]->point(0);
			li.add(Point(x.x + r, x.y + r), Point(y.x + r, y.y + r));
		}
	}
	virtual void draw_lines()const
	{
		li.draw_lines();
		for (int i = 1; i <=cou; i++)
			cir[i]->draw_lines();
	}
};

class Triangle_Binary_tree :public Binary_tree
{
private:
	int levels, cou;
	TriangleNode* tri[305];
	Lines li;
public:
	Triangle_Binary_tree(int le = 0) { levels = le; cou = pow(2, levels) - 1; }
	void work()
	{
		//Shape::add(Point(300, 300));
		//Shape::add(Point(400, 200));
		//Shape::add(Point(400, 400));
		Point x,y;
		double r = 10, lo;
		if (levels == 0) return;
		tri[1] = new TriangleNode(Point(600, 380), r);
		tri[1]->l = pow(2, levels - 1) * 30 + cou * 10;
		tri[1]->set_color(Color::black);
		tri[1]->set_fill_color(Color::cyan);
		for (int i = 2; i <= cou; i++)
			if (i & 1)
			{
				x = tri[i / 2]->point(0);
				lo = tri[i / 2]->l;
				tri[i] = new TriangleNode(Point(x.x + lo / 2, x.y + 50), r);
				tri[i]->l = (lo - 10) / 2.0000000;
				tri[i]->set_color(Color::black);
				tri[i]->set_fill_color(Color::blue);
			}
			else
			{
				x = tri[i / 2]->point(0);
				lo = tri[i / 2]->l;
				tri[i] = new TriangleNode(Point(x.x - lo / 2, x.y + 50), r);
				tri[i]->l = (lo - 10) / 2.000000;
				tri[i]->set_color(Color::black);
				tri[i]->set_fill_color(Color::green);
			}
		set_color(Color::black);
		for (int i = 1; i <= cou / 2; i++)
		{
			x = tri[i]->point(0);
			y = tri[i << 1]->point(0);
			li.add(Point(x.x, x.y + r), Point(y.x, y.y + r));
			x = tri[i]->point(0);
			y = tri[i << 1 | 1]->point(0);
			li.add(Point(x.x, x.y + r), Point(y.x, y.y + r));
		}
	}
	void draw_lines()const
	{
		li.draw_lines();
		for (int i = 1; i <=cou; i++)
			tri[i]->draw_lines();
	}
};

#endif
