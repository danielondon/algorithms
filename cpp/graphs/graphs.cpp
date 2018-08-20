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
    cout << "removing edge " << endl;
    {
        EXPECT_TRUE(g.removeEdge(1, 2));
    }
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