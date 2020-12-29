
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#define _CRT_SECURE_NO_WARNINGS
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "AnalogClock.h"
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    Point tl(100, 100);           // to become top left  corner of window
    Back_window win(tl, 1200, 700, "Canvas");    
    AnalogClock alc;
    win.attach(alc);
    while (1)
    {
        alc.update();
        Fl::wait();
        Fl::redraw();
        Sleep(1000); 
        if (win.judge())
            break;
    }
    return 0;
}

//------------------------------------------------------------------------------