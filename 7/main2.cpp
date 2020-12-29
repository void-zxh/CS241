
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "righttriangle.h"

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    Point tl(100, 100);           // to become top left  corner of window
    Simple_window win(tl, 600, 600, "Canvas");    // make a simple window
    double sz = 50;
    double zx = 300, zy = 300,sqr2=sqrt(2);
    righttriangle ri1(zx - sz, zy - sz - sz * sqr2, 2 * sz, 2 * sz), ri2(zx + sz, zy - sz - sz * sqr2, 2 * sz, 2 * sz);
    righttriangle ri3(zx + sz + sz * sqr2, zy - sz, 2 * sz, 2 * sz), ri4(zx + sz + sz * sqr2, zy + sz, 2 * sz, 2 * sz);
    righttriangle ri5(zx + sz, zy + sz + sz * sqr2, 2 * sz, 2 * sz), ri6(zx - sz, zy + sz + sz * sqr2, 2 * sz, 2 * sz);
    righttriangle ri7(zx - sz - sz * sqr2, zy + sz, 2 * sz, 2 * sz), ri8(zx - sz - sz * sqr2, zy - sz, 2 * sz, 2 * sz);

    //Type1
    ri1.set_angle(0); ri2.set_angle(45); ri3.set_angle(90); ri4.set_angle(135);
    ri5.set_angle(180); ri6.set_angle(-135); ri7.set_angle(-90); ri8.set_angle(-45);

    //Type2
    //ri1.set_angle(-90); ri2.set_angle(-45); ri3.set_angle(0); ri4.set_angle(45);
    //ri5.set_angle(90); ri6.set_angle(135); ri7.set_angle(180); ri8.set_angle(-135);
    

    ri1.set_color(Color::black); ri2.set_color(Color::black);
    ri3.set_color(Color::black); ri4.set_color(Color::black);
    ri5.set_color(Color::black); ri6.set_color(Color::black); 
    ri7.set_color(Color::black); ri8.set_color(Color::black);

    ri1.set_fill_color(Color::blue); ri2.set_fill_color(Color::green);
    ri3.set_fill_color(Color::red); ri4.set_fill_color(Color::yellow); 
    ri5.set_fill_color(Color::magenta) ;ri6.set_fill_color(Color::cyan); 
    ri7.set_fill_color(Color::dark_cyan); ri8.set_fill_color(Color::dark_blue);
    
    win.attach(ri1); win.attach(ri2);
    win.attach(ri3); win.attach(ri4); 
    win.attach(ri5); win.attach(ri6); 
    win.attach(ri7); win.attach(ri8);
    win.wait_for_button();       // give control to the display engine
    return 0;
}

//------------------------------------------------------------------------------
