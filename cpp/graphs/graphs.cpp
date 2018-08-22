#include "gtest/gtest.h"
#include "graph.h"
using namespace std;
using namespace graphs;

TEST(GraphTest, AddingNode)
{
    Graph<int> g;
    EXPECT_TRUE(g.addNode(1));
    EXPECT_FALSE(g.addNode(1));
    EXPECT_EQ(1, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());
}

TEST(GraphTest, RemovingNode)
{
    Graph<int> g;
    EXPECT_TRUE(g.addNode(1));
    EXPECT_TRUE(g.removeNode(1));
    EXPECT_FALSE(g.removeNode(2));
    EXPECT_EQ(0, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());
}

TEST(GraphTest, AddingEdgeRemovingNode)
{
    Graph<int> g;
    EXPECT_TRUE(g.addNode(1));
    EXPECT_TRUE(g.addNode(2));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_EQ(2, g.getNodesCount());
    EXPECT_EQ(1, g.getEdgesCount());

    // Removing Node
    EXPECT_TRUE(g.removeNode(2));
    EXPECT_EQ(1, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());
    
    // Remove non existing node
    EXPECT_FALSE(g.removeNode(3));
}

TEST(GraphTest, AddingEdgeRemovingEdge)
{
    Graph<int> g;
    EXPECT_TRUE(g.addNode(1));
    EXPECT_TRUE(g.addNode(2));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_EQ(2, g.getNodesCount());
    EXPECT_EQ(1, g.getEdgesCount());

    // Removing edge
    EXPECT_TRUE(g.removeEdge(1, 2));
    EXPECT_EQ(2, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());

    // Remove non existing edge
    EXPECT_FALSE(g.removeEdge(1, 2));
}

TEST(GraphTest, AddingRemovingEdges_DoNotCreateNewChildrenOrParents)
{
    Graph<int> g;
    EXPECT_TRUE(g.addNode(1));
    EXPECT_TRUE(g.addNode(2));
    EXPECT_TRUE(g.addNode(3));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_TRUE(g.addEdge(1, 3, 10));
    EXPECT_TRUE(g.addEdge(2, 3, 10));

    EXPECT_EQ(3, g.getNodesCount());
    EXPECT_EQ(3, g.getEdgesCount());

    // Removing edge
    EXPECT_TRUE(g.removeEdge(1, 2));

    EXPECT_EQ(3, g.getNodesCount());
    EXPECT_EQ(2, g.getEdgesCount());

    // Adding Edge Again
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_EQ(3, g.getNodesCount());
    EXPECT_EQ(3, g.getEdgesCount());

    // Removing Node 
    EXPECT_TRUE(g.removeNode(2));
    EXPECT_EQ(2, g.getNodesCount());
    EXPECT_EQ(1, g.getEdgesCount());
    
    //Check Null
    EXPECT_NE(nullptr, g.getNode(1));
    EXPECT_EQ(nullptr, g.getNode(2));
    EXPECT_NE(nullptr, g.getNode(3));

    EXPECT_EQ(nullptr, g.getEdge(1, 2));
    EXPECT_NE(nullptr, g.getEdge(1, 3));
    EXPECT_EQ(nullptr, g.getEdge(2, 3));

    // Adding Edge and nodes Again
    EXPECT_TRUE(g.addNode(2));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_TRUE(g.addEdge(2, 3, 10));
    EXPECT_EQ(3, g.getNodesCount());
    EXPECT_EQ(3, g.getEdgesCount());

    //Check Null
    EXPECT_NE(nullptr, g.getNode(1));
    EXPECT_NE(nullptr, g.getNode(2));
    EXPECT_NE(nullptr, g.getNode(3));

    EXPECT_NE(nullptr, g.getEdge(1, 2));
    EXPECT_NE(nullptr, g.getEdge(1, 3));
    EXPECT_NE(nullptr, g.getEdge(2, 3));

    // Check that nodes, do not create unnecessary children or parent
    EXPECT_EQ(2, g.getNode(1)->getChildrenCount()); 
    EXPECT_EQ(0, g.getNode(1)->getParentsCount());    
        
    EXPECT_EQ(1, g.getNode(2)->getChildrenCount()); 
    EXPECT_EQ(1, g.getNode(2)->getParentsCount());    

    EXPECT_EQ(0, g.getNode(3)->getChildrenCount());
    EXPECT_EQ(2, g.getNode(3)->getParentsCount());
}

TEST(GraphTest, GetMaxDepth)
{
    Graph<int> g;
    for (int i = 10; i >= 1; --i)
        EXPECT_TRUE(g.addNode(i));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_TRUE(g.addEdge(1, 3, 20));
    EXPECT_TRUE(g.addEdge(2, 3, 10));
    EXPECT_TRUE(g.addEdge(2, 4, 10));
    EXPECT_TRUE(g.addEdge(3, 9, 10));
    EXPECT_TRUE(g.addEdge(4, 7, 10));
    EXPECT_TRUE(g.addEdge(4, 5, 10));
    EXPECT_TRUE(g.addEdge(5, 6, 10));
    EXPECT_TRUE(g.addEdge(7, 8, 10));
    EXPECT_TRUE(g.addEdge(2, 6, 10));

    EXPECT_EQ(10, g.getNodesCount());
    EXPECT_EQ(10, g.getEdgesCount());

    EXPECT_EQ(5, g.getMaxDepth());
}


TEST(GraphTest, UndirectedGraph)
{
    Graph<int> g(false);
    for (int i = 10; i >= 1; --i)
        EXPECT_TRUE(g.addNode(i));
    EXPECT_TRUE(g.addEdge(1, 2, 10));
    EXPECT_TRUE(g.addEdge(1, 3, 20));
    EXPECT_TRUE(g.addEdge(2, 3, 10));
    EXPECT_TRUE(g.addEdge(2, 4, 10));
    EXPECT_TRUE(g.addEdge(3, 9, 10));
    EXPECT_TRUE(g.addEdge(4, 7, 10));
    EXPECT_TRUE(g.addEdge(4, 5, 10));
    EXPECT_TRUE(g.addEdge(5, 6, 10));
    EXPECT_TRUE(g.addEdge(7, 8, 10));
    EXPECT_TRUE(g.addEdge(2, 6, 10));

    EXPECT_NO_THROW(g.print(1));
    EXPECT_NO_THROW(g.print(4));
    EXPECT_NO_THROW(g.print(8));

    // Directed Graph, then 10 edges x 2
    EXPECT_EQ(10, g.getNodesCount());
    EXPECT_EQ(20, g.getEdgesCount());
    // Remove Edge
    EXPECT_TRUE(g.removeEdge(1, 2));
    // Both Edges Should be removed
    EXPECT_EQ(18, g.getEdgesCount());
    // No edges should exist
    EXPECT_FALSE(g.removeEdge(1, 2));
    EXPECT_FALSE(g.removeEdge(2, 1));
}

TEST(GraphTest, PrimsAlgorithm)
{
    Graph<int> g(false);
    for (int i = 6; i >= 1; --i)
        EXPECT_TRUE(g.addNode(i));
    EXPECT_TRUE(g.addEdge(1, 2, 4));
    EXPECT_TRUE(g.addEdge(1, 6, 2));
    EXPECT_TRUE(g.addEdge(2, 3, 6));
    EXPECT_TRUE(g.addEdge(2, 6, 3));
    EXPECT_TRUE(g.addEdge(3, 4, 3));
    EXPECT_TRUE(g.addEdge(3, 6, 1));
    EXPECT_TRUE(g.addEdge(4, 5, 12));
    EXPECT_TRUE(g.addEdge(5, 6, 14));

    auto minimumSpanningTree = prims(g);
    EXPECT_EQ(g.getNodesCount() - 1, minimumSpanningTree.size());
    EXPECT_EQ( 21, getCostPath(minimumSpanningTree));
    EXPECT_NO_THROW(printPath(minimumSpanningTree));
}

TEST(GraphTest, DijkstraAlgorithm)
{
    // https://www.youtube.com/watch?v=gdmfOwyQlcI
    Graph<int> g(false);
    for (int i = 7; i >= 1; --i)
        EXPECT_TRUE(g.addNode(i));
    EXPECT_TRUE(g.addEdge(1, 2, 4));
    EXPECT_TRUE(g.addEdge(1, 3, 3));
    EXPECT_TRUE(g.addEdge(1, 5, 7));
    EXPECT_TRUE(g.addEdge(2, 3, 6));
    EXPECT_TRUE(g.addEdge(2, 4, 5));
    EXPECT_TRUE(g.addEdge(3, 4, 11));
    EXPECT_TRUE(g.addEdge(3, 5, 8));
    EXPECT_TRUE(g.addEdge(4, 5, 2));
    EXPECT_TRUE(g.addEdge(4, 6, 2));
    EXPECT_TRUE(g.addEdge(4, 7, 10));
    EXPECT_TRUE(g.addEdge(5, 7, 5));
    EXPECT_TRUE(g.addEdge(6, 7, 3));

    auto path = dijkstra(g, 1, 6);
    EXPECT_EQ(11, getCostPath(path));
    EXPECT_EQ(3, path.size());
    EXPECT_NO_THROW(printPath(path));
}
