
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#define _CRT_SECURE_NO_WARNINGS
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "BarChart.h"

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    Point tl(100, 100);           // to become top left  corner of window
    My_window win(tl, 1200, 700, "Canvas");    // make a simple window
    BarChart bc;
    bc.init();
    bc.ChartShow(win);
    win.quit_for_button();       // give control to the display engine
    return 0;
}

//------------------------------------------------------------------------------