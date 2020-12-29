#pragma once
//#pragma warning(disable:4996)//visual studio 使用fopen,fscanf的限制
#define _CRT_SECURE_NO_WARNINGS
#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

const double PI = 3.1415926535;
const string cl_num[15] = { "","I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII" };
const int del_ti_x[15] = { 0 ,0,0,0,-2,-1,-10,-8,-10,-12,-8,-5,-10};
const int del_ti_y[15] = { 0 ,0,0,6,12,14,10,13,11,5,1,0,0};

struct Back_window : Graph_lib::Window
{
	Back_window(Point xy, int w, int h, const string& title) :
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

	int judge()
	{
		return button_pushed;
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
	Graph_lib::Button quit_button;     
	bool button_pushed;     // implementation detail
	Graph_lib::Rectangle back_rect, Quit_butt;
	Text qui;

	static void cb_quit(Graph_lib::Address, Graph_lib::Address pw) // callback for next_button
	{
		Graph_lib::reference_to<Back_window>(pw).quit();
	}

	void quit()            
	{
		button_pushed = true;
		hide();
	}
};

struct CircleNode :Shape
{
	int l;
	CircleNode() {}
	CircleNode(Point p, int rr) :r(rr) { add(Point(p.x - r, p.y - r)); }
	void draw_lines() const
	{
		/*if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}*/
		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}
private:
	int r;
};

struct needle_line:Shape
{
	Point p1, p2;
	needle_line(Point xx, Point yy) :p1(xx), p2(yy) {}
};

struct Needles :Shape
{
	Needles()
	{
		n = 0;
		memset(li, 0, sizeof(li));
	}
	void draw_lines() const
	{
		for (int i = 1; i <= n; i++)
		{
			fl_color(li[i]->color().as_int());
			fl_line(li[i]->p1.x, li[i]->p1.y, li[i]->p2.x, li[i]->p2.y);
		}
	}
	void set_add(Point p1, Point p2, Color col,int i)
	{
		if (n < 3)
		{
			li[++n] = new needle_line(p1, p2);
			li[n]->set_color(col);
		}
		else
			li[i]->p2 = p2;
	}
private:
	int n;
	needle_line* li[5];
};

class AnalogClock :public Shape
{
private:
	CircleNode pl;
	Point cet;
	Point h, m, s;
	Needles needle;
	Text* date_t, *clock_t;
	needle_line* li[15];
	Text* lab_li[15];

	string to_stringtime(int x)
	{
		string re = to_string(x);
		int li = re.size();
		if (li <= 1)
			re = '0' + re;
		return re;
	}

public:
	AnalogClock():pl(Point(600,380),280),cet(600,380)
	{
		date_t = NULL; clock_t = NULL;
		pl.set_color(Color::black);
		pl.set_fill_color(Color::white);
		double theta;
		for (int i = 1; i <= 12; i++)
		{
			theta = i * 1.0000 * 30 / 180 * PI;
			li[i] = new needle_line(Point(cet.x + sin(theta) * 280,cet.y-cos(theta)*280), Point(cet.x + sin(theta) * 255, cet.y - cos(theta) * 255));
			li[i]->set_color(Color::black);
			lab_li[i] = new Text(Point(cet.x + sin(theta) * 225+del_ti_x[i], cet.y - cos(theta) * 225+del_ti_y[i]), cl_num[i]);
			lab_li[i]->set_font(Font::times);
			lab_li[i]->set_font_size(20);
			lab_li[i]->set_color(Color::black);
		}
	}

	void update()
	{
		time_t tim;
		time(&tim);
		struct tm* ti;
		ti = localtime(&tim);
		if (date_t == NULL)
		{
			date_t = new Text(Point(530, 40), to_string(1900+ti->tm_year) + string(".") + to_string(ti->tm_mon + 1) + string(".") + to_string(ti->tm_mday));
			date_t->set_font_size(30); date_t->set_color(Color::black);
		}
		else
			date_t->set_label(to_string(1900+ti->tm_year) + string(".") + to_string(ti->tm_mon + 1) + string(".") + to_string(ti->tm_mday));
		if (clock_t == NULL)
		{
			clock_t = new Text(Point(530, 70), to_stringtime(ti->tm_hour) + string(":") + to_stringtime(ti->tm_min) + string(":") + to_stringtime(ti->tm_sec));
			clock_t->set_font_size(30); clock_t->set_color(Color::black);
		}
		else
			clock_t->set_label(to_stringtime(ti->tm_hour) + string(":") + to_stringtime(ti->tm_min) + string(":") + to_stringtime(ti->tm_sec));
		int lh=120, lm=180, ls=240;
		double teh, tem, tes;
		teh = ((ti->tm_hour%12) + ti->tm_min * 1.0000 / 60) * 1.0000 * 30 / 180 * PI;
		tem = (ti->tm_min * 1.0000 + ti->tm_sec * 1.0000 / 60) * 1.0000 * 6 / 180 * PI;
		tes = ti->tm_sec * 1.0000 * 6 / 180 * PI;
		h = Point(cet.x + sin(teh)*lh, cet.y - cos(teh)*lh);
		m = Point(cet.x + sin(tem) * lm, cet.y - cos(tem) * lm);
		s = Point(cet.x + sin(tes) * ls, cet.y - cos(tes) * ls);
		needle.set_add(cet, h,Color::green,1); needle.set_add(cet, m,Color::blue,2); needle.set_add(cet, s,Color::red,3);
	}

	void draw_lines()const
	{
		date_t->draw(); clock_t->draw();
		pl.draw_lines();needle.draw_lines();
		for (int i = 1; i <= 12; i++)
		{
			fl_color(li[i]->color().as_int());
			fl_line(li[i]->p1.x, li[i]->p1.y, li[i]->p2.x, li[i]->p2.y);
			lab_li[i]->draw();
		}
	}
};

#endif

