#pragma once
//#pragma warning(disable:4996)//visual studio 使用fopen,fscanf的限制
#define _CRT_SECURE_NO_WARNINGS
#ifndef BARCHART_H
#define BARCHART_H

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

const string month_name[15] = { "","January","February","March","April","May","June","July","Augest","September","October","November","December" };

struct My_window : Graph_lib::Window 
{
	My_window(Point xy, int w, int h, const string& title):
		Window(xy, w, h, title),
		quit_button(Point(x_max() - 70, 0), 70, 20, "quit", cb_quit),
		button_pushed(false), qui(Point(1150, 12), "quit"), back_rect(Point(0, 0), 3000, 3000), Quit_butt(Point(1130, 0), 70, 20)
	{
		attach(quit_button);
		back_rect.set_color(Color::white); back_rect.set_fill_color(Color::white);
		Quit_butt.set_color(Color::black); Quit_butt.set_fill_color(Color::blue);
		qui.set_color(Color::green); qui.set_font_size(15);
		attach(back_rect); attach(Quit_butt); attach(qui);
	}

	bool quit_for_button()
	{
		show();
		button_pushed = false;
		while (!button_pushed) Fl::wait();
		Fl::redraw();
		return button_pushed;
	}
private:
	Graph_lib::Button quit_button;     // the "next" button
	bool button_pushed;     // implementation detail
	Graph_lib::Rectangle back_rect, Quit_butt;
	Text qui;

	static void cb_quit(Graph_lib::Address, Graph_lib::Address pw) // callback for next_button
	{
		Graph_lib::reference_to<My_window>(pw).quit();
	}
	void quit()            // action to be done when next_button is pressed
	{
		button_pushed = true;
		hide();
	}
};


struct Axis_degree : Shape
{
	enum Orientation { x, y, z };
	Axis_degree(Orientation d, Point xy, int length, int n, string lab) :label(Point(0, 0), lab)
	{
		cou = 0;
		if (length < 0) error("bad axis length");
		switch (d) {
		case Axis::x:
		{
			ty = 0;
			Shape::add(xy); // axis line
			Shape::add(Point(xy.x + length+50, xy.y));
			// add notches
			int dist = length / n;
			int x = xy.x + dist;
			for (int i = 0; i < n; ++i) {
				notches.add(Point(x, xy.y), Point(x, xy.y - 5));
				pi[++cou] = Point(x, xy.y);
				x += dist;
			}
			// label under the line
			label.move(length / 2, xy.y + 50);
			int dis=dist/3;
			for (int i = 1; i <= 12; i++)
			{
				li[i] = new Text(Point(pi[i].x-2*dis, xy.y + 20), month_name[i]);
				li[i]->set_font_size(15);
				li[i]->set_color(Color::black);
			}
			break;
		}
		case Axis::y:
		{
			ty = 1;
			Shape::add(xy); // a y-axis goes up
			Shape::add(Point(xy.x, xy.y - length));

			if (1 < n) {      // add notches
				int dist = length / n;
				int y = xy.y - dist;
				for (int i = 0; i < n; ++i) {
					notches.add(Point(xy.x, y), Point(xy.x + 5, y));
					pi[++cou] = Point(xy.x, y);
					y -= dist;
				}
			}
			// label at top
			label.move(xy.x - 10, xy.y - length - 10);
			li[0] = new Text(Point(xy.x - 30, xy.y+7), strwork(0));
			li[0]->set_font_size(15);
			li[0]->set_color(Color::black);
			for (int i = 1; i <= 12; i++)
			{
				li[i] = new Text(Point(xy.x - 30, pi[i].y+7), strwork(i*2.5));
				li[i]->set_font_size(15);
				li[i]->set_color(Color::black);
			}
			break;
		}
		case Axis::z:
			error("z axis not implemented");
		}
	}

	string strwork(double x)
	{
		string xi = to_string(x);
		string re = "";
		int id = 0;
		while (xi[id] != '.')
			re = re + xi[id++];
		re = re + xi[id] + xi[id + 1];
		return re;
	}

	void draw_lines() const
	{
		Shape::draw_lines();
		if(ty)
			notches.draw();  // the notches may have a different color from the line
		label.draw();    // the label may have a different color from the line
		if (ty)
			li[0]->draw();
		for (int i = 1; i <= 12; i++)
			li[i]->draw();
	}

	void move(int dx, int dy)
	{
		Shape::move(dx, dy);
		notches.move(dx, dy);
		label.move(dx, dy);
	}

	void set_color(Color c)
	{
		Shape::set_color(c);
		notches.set_color(c);
		label.set_color(c);
	}

	Text label,*li[15];
	Lines notches;
	int cou,ty;
	Point pi[50];
};

struct Legend :Shape
{
	Graph_lib::Rectangle* out,*rec1,*rec2;
	Text* tex1, *tex2;

	Legend(Point xyi, int ww, int hh) 
	{
		out = new Graph_lib::Rectangle(xyi, ww, hh);
		rec1 = new Graph_lib::Rectangle(Point(xyi.x + 10, xyi.y + 10), ww / 3,hh / 6);
		rec2 = new Graph_lib::Rectangle(Point(xyi.x + 10, xyi.y + 30), ww / 3, hh / 6);
		tex1 = new Text(Point(xyi.x + 15 + ww / 3, xyi.y + 17), "NewYork");
		tex2 = new Text(Point(xyi.x + 15 + ww / 3, xyi.y + 37), "Austin");
	}
	void draw_lines()const
	{
		out->set_color(Color::black);
		out->draw_lines();
		tex1->set_color(Color::black); tex2->set_color(Color::black);
		tex1->set_font_size(12); tex2->set_font_size(12);
		rec1->set_color(Color::cyan); rec1->set_fill_color(Color::cyan);
		rec2->set_color(Color::magenta); rec2->set_fill_color(Color::magenta);
		tex1->draw(); tex2->draw();
		rec1->draw_lines(); rec2->draw_lines();
	}
};

class BarChart
{
private:
	double ny[15], aus[15],mn,ma;
	int cou_ny[15], cou_au[15];
	Graph_lib::Rectangle* rect_ny[15],*rect_au[15];
	Axis_degree* xi, *yi;
	Text title;
	Legend leg;
public:
	BarChart():title(Point(150,100),"Graph of average temperature in Austin and NewYork for 2016"),leg(Point(1000,200),100,50)
	{
		title.set_color(Color::black); title.set_font_size(35);
		mn =-9999; ma = -9999;
		memset(ny, 0, sizeof(ny)); memset(aus, 0, sizeof(aus));
		memset(cou_ny, 0, sizeof(cou_ny)); memset(cou_au, 0, sizeof(cou_au));
	}

	void init()
	{
		char t1[25],t2[25];
		double ti;
		int year, month, day;
		FILE* fp = fopen("NewYork.csv","r");
		fscanf(fp, "%s,%s,\n", t1, t2);
		while (~fscanf(fp, "%d/%d/%d,%lf ,\n", &year, &month, &day, &ti))
		{
			ny[month] += ti;
			cou_ny[month]++;
			//printf("%d/%d/%d,%lf \n", year, month, day, ti);
		}
		fclose(fp);

		fp = fopen("Austin.csv", "r");
		fscanf(fp, "%s,%s,\n", t1, t2);
		while (~fscanf(fp, "%d/%d/%d,%lf ,\n", &year, &month, &day, &ti))
		{
			aus[month] += ti;
			cou_au[month]++;
			//printf("%d/%d/%d,%lf \n", year, month, day, ti);
		}
		fclose(fp);
		for (int i = 1; i <= 12; i++)
		{
			ny[i] /= cou_ny[i]; mn = max(mn, ny[i]);
			aus[i] /= cou_au[i]; ma = max(ma, aus[i]);
			//printf("%lf %lf\n", ny[i], aus[i]);
		}
	}

	void ChartShow(My_window& win)
	{
		double xlen = 1000,ylen=450;
		int dis = xlen / 36,yh;
		xi = new Axis_degree(Axis_degree::x,Point(100,600), xlen, 12, "Month");
		yi = new Axis_degree(Axis_degree::y, Point(100, 600), ylen, 12, "Temperature");
		xi->set_color(Color::black); yi->set_color(Color::black);
		for (int i = 1; i <= 12; i++)
		{
			yh = ylen * ny[i] / mn;
			rect_ny[i] = new Graph_lib::Rectangle(Point(xi->pi[i].x - 2 * dis, xi->pi[i].y-yh), dis, yh);
			yh = ylen * aus[i] / ma;
			rect_au[i] = new Graph_lib::Rectangle(Point(xi->pi[i].x - dis, xi->pi[i].y-yh), dis, yh);
			rect_ny[i]->set_color(Color::cyan); rect_ny[i]->set_fill_color(Color::cyan);
			rect_au[i]->set_color(Color::magenta); rect_au[i]->set_fill_color(Color::magenta);
		}
		win.attach(title);
		for (int i = 1; i <= 12; i++)
		{
			win.attach(*rect_ny[i]);
			win.attach(*rect_au[i]);
		}
		win.attach(*xi); win.attach(*yi);
		win.attach(leg);
	}

};

#endif

