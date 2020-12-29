
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Binary_tree.h"

//------------------------------------------------------------------------------

int main3()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    Point tl(100, 100);           // to become top left  corner of window
    Simple_window win(tl, 1200, 600, "Canvas");    // make a simple window
    int N;
    cin >> N;
    Binary_tree bnt(N);
    Triangle_Binary_tree tbt(N);
    bnt.work(); tbt.work();
    win.attach(bnt); win.attach(tbt);
    win.wait_for_button();       // give control to the display engine
    return 0;
}

//------------------------------------------------------------------------------
