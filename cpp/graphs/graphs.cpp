#include "graph.h"
using namespace std;
using namespace graphs;

int main()
{
    cout<<"Graphs "<<endl<<endl;

    Graph<int> g;
    //Node<int> node(1,1); // this should be forbidden, since is private and only graph can create it.
    auto nodeId1 = g.addNode(1);
    auto nodeId2 = g.addNode(2);
    auto nodeId3 = g.addNode(3);
    g.addEdge(nodeId1, nodeId2, 10);
    g.addEdge(nodeId1, nodeId3, 20);
    auto nodeId4 = g.addNode(4);
    g.addEdge(nodeId2, nodeId4, 10);
    g.print(nodeId1);
    cout << "removing node 2" << endl;
    {
        g.removeNode(nodeId2);
    }
    g.print(nodeId1);
    cout << "Adding node 2 and edge to 4 again" << endl;
    {
        nodeId2 = g.addNode(2);
        g.addEdge(nodeId2, nodeId4, 10);
    }
    g.print(nodeId1);
    cout << "removing node 4" << endl;
    {
        g.removeNode(nodeId4);
    }
    g.print(nodeId1);
    cout << "Adding node 4 and edge 2 again" << endl;
    {
        nodeId4 = g.addNode(4);
        g.addEdge(nodeId2, nodeId4, 10);
    }
    g.print(nodeId1);

    cout << "Adding edge from 1 to 2 again" << endl;
    {
        g.addEdge(nodeId1, nodeId2, 15);
    }
    g.print(nodeId1);

    cout << "finishing program" << endl;
        
    return 0;
}