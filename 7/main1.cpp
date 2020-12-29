
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "hyperelliptic.h"

//------------------------------------------------------------------------------

int main()
{
    double a, b, m, n;
    int N;
    cin >> a >> b >> m >> n >> N;
    hyperelliptic hyp(a,b,m,n,N);
    hyp.work();
    return 0;
}

//------------------------------------------------------------------------------
