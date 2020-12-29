#pragma GCC optimize(2)
#include "Graph_Basic.h"
#include "Graph_Divided.h"
#include "Graph_Generator.h"
#include "Graph_Dataloader.h"
#include "Graph_Partition.h"
using namespace std;

Graph_Basic Mgraph,Ugraph;
Graph_Divided Dgraph;
Graph_Generator gg;
Graph_Dataloader gd;
Graph_Partition gp;

int main()
{
    gg.generate();
    gd.dataload(Mgraph);
    Ugraph.Undirected_build(Mgraph);
    gp.setState(BruteForce_MODE);
    gp.pre_build();
    Ugraph.Dfs_seg(gp);
    gd.check_datawrite(Ugraph);
    Dgraph.build(Mgraph,Ugraph.segmation_out());
    gd.subgraph_datawrite(Dgraph);
    gd.shortest_path(Dgraph);
    return 0;
}