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
    cout << "removing node 2" << endl;
    {
        EXPECT_TRUE(g.removeNode(2));
    }
    EXPECT_EQ(1, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());
    
    // Remove unexisting node
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
    cout << "removing edge " << endl;
    {
        EXPECT_TRUE(g.removeEdge(1, 2));
    }
    EXPECT_EQ(2, g.getNodesCount());
    EXPECT_EQ(0, g.getEdgesCount());

    // Remove unexisting edge
    EXPECT_FALSE(g.removeEdge(1, 2));
}