// Given a directed graph, design and algorithm to find out whether there is a 
// route between two nodes

#include "common.h"

using namespace std;

bool findRoute(Graph & g, shared_ptr<Vertex> node1, shared_ptr<Vertex> node2)
{
    if (node1 == node2)
        return true;
    
    bool res = false;
    for(auto & vertex : g.getNodes())
    {
        vertex->visited = false;
    }
    
    queue<weak_ptr<Vertex>> nodes;
    nodes.push(node1);
    
    while( !nodes.empty() )
    {
        auto vertex = nodes.front().lock();
        nodes.pop();
        for (auto & nodeWeak : vertex->adjacents)
        {
            auto node = nodeWeak.lock();
            if (node == node2)
                return true;
            
            if (!node->visited)
            {
                node->visited = true;
                nodes.push(node);
            }
        }
    }
    
    return res;
}



int main()
{
    cout<<"Find Root "<<endl<<endl;
    {
        Graph g;
        {
            auto vertex1 = g.addVertex(1, 1);
            auto vertex2 = g.addVertex(2, 2);
            auto vertex3 = g.addVertex(3, 3);
            auto vertex4 = g.addVertex(4, 4);
            auto vertex5 = g.addVertex(5, 5);
            g.addEdge(vertex1, vertex2, 1);
            g.addEdge(vertex1, vertex5, 1);
            g.addEdge(vertex2, vertex3, 1);
            g.addEdge(vertex3, vertex2, 1);
            g.addEdge(vertex3, vertex5, 1);
            g.addEdge(vertex4, vertex3, 1);
            g.addEdge(vertex5, vertex4, 1);
           
        }
        
        {
            auto vertex1 = g.getVertex(1);
            auto vertex2 = g.getVertex(4);
            
            bool res = findRoute(g, vertex1, vertex2);
            if (res)
                cout<<"Route exists between "<<vertex1->id<<" and "<< vertex2->id<<endl;
            else
                cout<<"Route doesn't exist between "<<vertex1->id<<" and "<< vertex2->id<<endl;
        }
        
        
        {
            auto vertex1 = g.getVertex(4);
            auto vertex2 = g.getVertex(1);
            
            bool res = findRoute(g, vertex1, vertex2);
            if (res)
                cout<<"Route exists between "<<vertex1->id<<" and "<< vertex2->id<<endl;
            else
                cout<<"Route doesn't exist between "<<vertex1->id<<" and "<< vertex2->id<<endl;
        }
        
        
        {
            auto vertex1 = g.getVertex(2);
            auto vertex2 = g.getVertex(5);
            
            bool res = findRoute(g, vertex1, vertex2);
            if (res)
                cout<<"Route exists between "<<vertex1->id<<" and "<< vertex2->id<<endl;
            else
                cout<<"Route doesn't exist between "<<vertex1->id<<" and "<< vertex2->id<<endl;
        }
        
        {
            auto vertex1 = g.getVertex(5);
            auto vertex2 = g.getVertex(2);
            
            bool res = findRoute(g, vertex1, vertex2);
            if (res)
                cout<<"Route exists between "<<vertex1->id<<" and "<< vertex2->id<<endl;
            else
                cout<<"Route doesn't exist between "<<vertex1->id<<" and "<< vertex2->id<<endl;
        }
        
        {
            auto vertex1 = g.getVertex(1);
            auto vertex2 = g.getVertex(1);
            
            bool res = findRoute(g, vertex1, vertex2);
            if (res)
                cout<<"Route exists between "<<vertex1->id<<" and "<< vertex2->id<<endl;
            else
                cout<<"Route doesn't exist between "<<vertex1->id<<" and "<< vertex2->id<<endl;
        }
        
        cout<<"Graph Destroying..."<<endl;
    }
    cout<<"Graph Destroyed"<<endl;
}