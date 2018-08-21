
#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <atomic>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <functional>

using namespace std;

namespace graphs
{
    // Forward Declarations
    template <class T>
    class Edge;
    template <typename T>
    class Graph;
       
    template <class T>
    class Node
    {
    public:
        ~Node()
        {
            //cout << "Destroying Node " << data << endl;
        }
    private:
        // Avoid that a node can be constructed from the outside
        explicit Node(int _id, int _data) : id(_id), data(_data)
        {
            //cout << "Creating Node " << data << endl;
        }

        // It was not moved to a free function, because the method isDetached is private and then can not be accessed from the free function.
        void addOrReplace(vector<weak_ptr<Edge<T>>> & edges, weak_ptr<Edge<T>> const& newEdge)
        {
            auto nextAvailable = find_if(edges.begin(), edges.end(), [](const weak_ptr<Edge<T>>& e) { return e.expired() ? true : e.lock()->isDetached(); });
            // If there is some expired pointer, replace it
            if (nextAvailable != edges.end())
            {
                *nextAvailable = newEdge;
            }
            else
            {
                edges.push_back(newEdge);
            }
        }

        void addChild(weak_ptr<Edge<T>> to)
        {
            addOrReplace(m_children, to);
        }

        void addParent(weak_ptr<Edge<T>> from)
        {
            addOrReplace(m_parents, from);
        }

        set<int> getIds(vector<weak_ptr<Edge<T>>> const& edges, bool isTo, function<bool(int)> filter ) const
        {
            set<int> ids;
            for (auto const& edge_wptr : edges)
            {
                auto edge_sptr = edge_wptr.lock();
                if (edge_sptr)
                {
                    shared_ptr<Node<T>> node_sptr;
                    if (isTo)
                        node_sptr = edge_sptr->getTo().lock();
                    else
                        node_sptr = edge_sptr->getFrom().lock();
                    if (filter(node_sptr->getId()))
                        ids.insert(node_sptr->getId());
                }
            }
            return ids;
        }

        size_t getDepth(unordered_map<int, bool> & markedNodes) const
        {
            // Mark Node
            markedNodes.at(getId()) = true;

            size_t depth = 0;
            size_t maxDepth = 1;
            for (auto const& edge_wptr : m_children)
            {
                auto edge_sptr = edge_wptr.lock();
                if (edge_sptr)
                {
                    auto node_sptr = edge_sptr->getTo().lock();
                    depth = 1 + node_sptr->getDepth(markedNodes);
                }

                if (depth > maxDepth)
                    maxDepth = depth;
            }

            return maxDepth;
        }

    public:
        set<int> getChildrensIds(function<bool(int)> filter = [](int){return true;}) const { return getIds(m_children, true, filter); }
        set<int> getParentsIds(function<bool(int)> filter = [](int){return true;}) const { return getIds(m_parents, false, filter); }
        int getId() const { return id; }
        T getData() const { return data; }
        size_t getChildrenCount() const { return m_children.size(); }
        size_t getParentsCount() const { return m_parents.size(); }
        vector<shared_ptr<Edge<T>>> getChildren() const {
            vector<shared_ptr<Edge<T>>> edges;
            transform(m_children.begin(), m_children.end(), std::back_inserter(edges), [](auto const& edge) { return edge.lock(); });
            return edges;

        }
    private:
        int id;
        T data;
        vector<weak_ptr<Edge<T>>> m_children;
        vector<weak_ptr<Edge<T>>> m_parents;
        friend class Graph<T>;
    };

    template <class T, class U>
    bool removeFromUnorderedMap(unordered_map<U, T> & map, U id)
    {
        auto it = map.find(id);
        if (it != map.end())
        {
            map.erase(it);
            return true;
        }
        else
        {
            return false;
        }
    }

    string createEdgeId(int fromId, int toId)
    {
        return to_string(fromId) + string("-") + to_string(toId);
    }


    template <class T>
    class Edge
    {
    public:
        ~Edge()
        {
            //cout << "Destroying Edge" << endl;
        }
    private:
        explicit Edge(weak_ptr<Node<T>> _from, weak_ptr<Node<T>> _to, string _id, int _weight) : from(_from), to(_to), id(_id), weight(_weight) {}

        bool isDetached() const { return from.expired() || to.expired(); }
    public:
        const weak_ptr<Node<T>>& getFrom() const { return from; }
        const weak_ptr<Node<T>>& getTo() const { return to; }
        string getId() const { return id; }
        int getWeigth() const { return weight; }
    private:
        weak_ptr<Node<T>> from;
        weak_ptr<Node<T>> to;
        string id;
        int weight = 0;        
        friend class Graph<T>;
        friend class Node<T>;
    };

    // Get hashmap to keep track of nodes marked
    template<class T, class U>
    unordered_map<int, U> getNodesMarked(unordered_map<int, shared_ptr<Node<T>>> const& nodes, U defaultValue)
    {
        unordered_map<int, U> nodesMarked;
        transform(nodes.begin(), nodes.end(), std::inserter(nodesMarked, nodesMarked.end()), [defaultValue](auto const& map_type) { return std::make_pair(map_type.first, defaultValue); });
        return nodesMarked;
    }




    template<class T>
    class Graph
    {
        //template <class T>
        typedef pair<string, shared_ptr<Edge<T>>> PAIR_EDGE;

        //template <class T>
        struct LessThanByPairEdge
        {
            bool operator()(const PAIR_EDGE & lhs, const PAIR_EDGE & rhs) const
            {
                return lhs.second->getWeigth() < rhs.second->getWeigth();
            }
        };
    public:
        Graph (bool _isDirectedGraph = true) : isDirectedGraph(_isDirectedGraph)
        {}

        ~Graph()
        {
            //cout << "Destroying Graph" << endl;
        }

        // Add a node
        bool addNode(int id)
        {
            if (m_nodes.find(id) != m_nodes.end())
                return false;

            // We can not use make_shared, since it is not friend of Node class
            shared_ptr<Node<T>> node (new Node<T>(id, id));
            m_nodes[node->getId()] = node;
            return true;
        }

        // Remove a node
        bool removeNode(int id)
        {
            bool res = removeDetachedEdges(id);
            res &= removeFromUnorderedMap(m_nodes, id);
            return res;
        }

        // Get node
        const shared_ptr <Node<T>> getNode(int nodeId) const
        {
            if (m_nodes.find(nodeId) != m_nodes.end())
                return m_nodes.at(nodeId);
            else
                return nullptr;
        }

        // Add an edge
        bool addEdge(int fromId, int toId, int weigth)
        {
            auto from = m_nodes.find(fromId);
            auto to = m_nodes.find(toId);
            if (from != m_nodes.end() && to != m_nodes.end())
            {
                if(!addEdge(from->second, to->second,  weigth))
                    return false;

                // If is not directed graph, then add extra edge
                if (!isDirectedGraph)
                {
                    if(!addEdge(to->second, from->second,  weigth))
                        return false;
                }
                return true;
            }
            //cout << "Edge was not added. Some of the nodes do not exist" << endl;
            return false;
        }

        // Remove an edge
        bool removeEdge(int fromId, int toId)
        {
            if (isDirectedGraph)
                return removeFromUnorderedMap(m_edges, createEdgeId(fromId, toId));
            else
                return removeFromUnorderedMap(m_edges, createEdgeId(fromId, toId)) && removeFromUnorderedMap(m_edges, createEdgeId(toId, fromId));
        }

        // Get Edge
        const shared_ptr <Edge<T>> getEdge(int fromId, int toId) const
        {
            auto edgeId = createEdgeId(fromId, toId);
            if (m_edges.find(edgeId) != m_edges.end())
            {
                return m_edges.at(edgeId);
            }
            else
                return nullptr;
        }


        // Print Graph
        void print(int nodeId) const
        {
            cout<<"*****************"<<endl;
            cout << "Nodes " << getNodesCount() << " :: Edges " << getEdgesCount() << " :: Valid Edges "<< getValidEdges()<<endl;
            auto rootNode =  getNode(nodeId);
            if (rootNode)
            {
                // Track which nodes have been printed
                auto nodesMarked = getNodesMarked(m_nodes, false);
                printGraph(nodesMarked, rootNode->getId());
            }
            cout<<"*****************"<<endl;
        }

        size_t getMaxDepth() const
        {
            auto nodesMarked = getNodesMarked(m_nodes, false);
            size_t depth = 0;
            getMaxDepth(nodesMarked, depth);            
            return depth;
        }

        // Temporal function to check if there are any invalid edges
        int64_t getValidEdges() const
        {
            return count_if(m_edges.begin(), m_edges.end(), [](auto const& map_type) { return !map_type.second->isDetached(); });
        }

        auto getEdgesByPriority()
        {
            //priority_queue< shared_ptr<Edge<T>>, vector< shared_ptr<Edge<T>> >, LessThanByEdge<T>> priorityQueue;
            //priority_queue< shared_ptr<Edge<T>> > priorityQueue;
            priority_queue< PAIR_EDGE, vector< PAIR_EDGE >, LessThanByPairEdge > priorityQueue( m_edges.begin(), m_edges.end());

            return priorityQueue;
        }

        // Get amount of nodes
        size_t getNodesCount() const { return m_nodes.size(); }

        // Get amount of edges
        size_t getEdgesCount() const { return m_edges.size(); }
    private:
        // Helper function for adding edge
        bool addEdge(shared_ptr<Node<T>> from, shared_ptr<Node<T>> to, int weight)
        {
            // Check if the edge exist
            auto edgeId = createEdgeId(from->getId(), to->getId());
            if (m_edges.find(edgeId) != m_edges.end())
            {
                //cout << "edges already exist" << endl;
                return false;
            }
            // We can not use make_shared, since it is not friend of Edge class
            shared_ptr<Edge<T>> edge(new Edge<T>(from, to, edgeId, weight));
            m_edges[edgeId] = edge;
            from->addChild(edge);
            to->addParent(edge);
            return true;
        }

        // Helper Function for GetMaxDepth
        void getMaxDepth(unordered_map<int, bool> & nodesMarked, size_t & currentMaxDepth) const
        {
            auto it = find_if(nodesMarked.begin(), nodesMarked.end(), [](auto const& map_type) { return !map_type.second; });
            if (it != nodesMarked.end())
            {
                auto depth = getNode(it->first)->getDepth(nodesMarked);
                if (depth > currentMaxDepth)
                    currentMaxDepth = depth;
                getMaxDepth(nodesMarked, currentMaxDepth);
            }
        }

        // Print Helper
        void printGraph(unordered_map<int, bool> & nodesToBePrinted, int rootId) const // shared_ptr <Node<T>> root) const
        {
            queue<int> allNodes;
            allNodes.push(rootId);

            size_t currentCount = 0;
            size_t expectedCount = allNodes.size();
            while(!allNodes.empty())
            {
                // Print Current Node
                auto id = allNodes.front();
                // Only if it has not been printed
                if (!nodesToBePrinted.at(id))
                {
                    cout<< id << " ";
                    nodesToBePrinted[id] = true;
                }
                allNodes.pop();
                ++currentCount;

                // Copy all Children
                function<bool(int)> filterFunction = [&](int id) { return nodesToBePrinted.at(id) == false; };
                auto children = getNode(id)->getChildrensIds(filterFunction);
                for (const auto& child : children)
                {
                    allNodes.push(child);
                }

                // Reset Count
                if(currentCount == expectedCount)
                {
                    expectedCount = allNodes.size();
                    currentCount = 0;
                    cout<<endl;
                }
            }
            
            cout<<endl;
            cout<<"---- Isolated  Nodes -----"<<endl;
            // Find Node that has not been printed
            auto it = find_if(nodesToBePrinted.begin(), nodesToBePrinted.end(), [](auto const& map_type) { return !map_type.second; });
            if (it != nodesToBePrinted.end())
            {
                printGraph(nodesToBePrinted, it->first);
            }
            cout<<endl;
        }

        // Helper function to remove edges
        void removeEdges(vector<weak_ptr<Edge<T>>> const& edges, int nodeId, bool toOrFrom)
        {
            for (auto const& edge_to_wptr : edges)
            {
                auto edge_to_sptr = edge_to_wptr.lock();
                if (edge_to_sptr)
                {
                    weak_ptr<Node<T>> node_wptr;
                    if (toOrFrom)
                        node_wptr = edge_to_sptr->getTo();
                    else
                        node_wptr = edge_to_sptr->getFrom();

                    auto node_sptr = node_wptr.lock();
                    if (node_sptr)
                    {
                        string id;
                        if (toOrFrom)
                            id= createEdgeId(nodeId, node_sptr->getId());
                        else
                            id = createEdgeId(node_sptr->getId(), nodeId);
                        m_edges.erase(id);
                    }
                    else
                        throw; // This should not happen
                }
                else
                    throw;// This should not happen

            }
        }

        // Helper function reo remove edges after a node is removed
        bool removeDetachedEdges(int nodeId)
        {
            // SOLUTION 1: LOOK INTO ALL EDGES AND FIND ALL DETACHED EDGES
            // Find if there is any edge detached, so it can be reused
            //auto it = find_if(m_edges.begin(), m_edges.end(), [](auto &map_type) { return map_type.second->isDetached(); });
            //if (it != m_edges.end())
            //{
            //    m_edges.erase(it);
            //    removeDetachedEdges();
            //}

            // SOLUTION 2: SINCE EVERY NODE KNOWS ITS FROM AND TO EDGES, FIND THE SPECIFIC EDGES IN THE MAP AND REMOVE THEM
            auto node = getNode(nodeId);
            if (node)
            {
                removeEdges(node->m_children, nodeId, true);
                removeEdges(node->m_parents, nodeId, false);
                return true;
            }
            else
            {
                return false;
            }
        }
                
    private:
        unordered_map<int, shared_ptr<Node<T>>> m_nodes;
        unordered_map<string, shared_ptr<Edge<T>>> m_edges;
        bool isDirectedGraph = true;
        template<typename U> // Use different Template class
        friend set<shared_ptr<Edge<U>>> prims(Graph<U> & graph);
    };

    template <class T>
    struct LessThanByEdge
    {
        bool operator()(const shared_ptr<Edge<T>> & lhs, const shared_ptr<Edge<T>> & rhs) const
        {
            return lhs->getWeigth() < rhs->getWeigth();
        }
    };

    template <class T>
    void addToPriorityQueue(priority_queue< shared_ptr<Edge<T>>, vector<shared_ptr<Edge<T>>>, LessThanByEdge<T> > & priorityQueue,  unordered_map<int, bool> & nodesMarked, vector<shared_ptr<Edge<T>>> edges)
    {
        for ( auto const& edge : edges)
        {
            auto weakPtr = edge->getTo();
            auto smartPtr = weakPtr.lock();
            if (!nodesMarked[smartPtr->getId()]) {
                priorityQueue.push(edge);
            }
        }
    }


    template <class T>
    void prims(shared_ptr<Node<T>> node, set<shared_ptr<Edge<T>>> & minimumSpanningTree,  unordered_map<int, bool> & nodesMarked, priority_queue< shared_ptr<Edge<T>>, vector<shared_ptr<Edge<T>>>, LessThanByEdge<T> > & priorityQueue )
    {
        if (!nodesMarked[node->getId()]) {
            nodesMarked[node->getId()] = true;
            addToPriorityQueue(priorityQueue, nodesMarked, node->getChildren());
        }

        auto it = find_if(nodesMarked.begin(), nodesMarked.end(), [](auto const& map_type) { return !map_type.second; });
        if (it == nodesMarked.end())
            return;

        if (!priorityQueue.empty()) {
            auto edge = priorityQueue.top();
            priorityQueue.pop();
            minimumSpanningTree.insert(edge);
            prims(edge->getTo().lock(), minimumSpanningTree, nodesMarked, priorityQueue);
        }
    }


    template <class T>
    set<shared_ptr<Edge<T>>> prims(Graph<T> & graph)
    {
        set<shared_ptr<Edge<T>>> minimumSpanningTree;
        if(graph.getEdgesCount() > 0)
        {
            auto nodesMarked = getNodesMarked(graph.m_nodes, false);
            priority_queue< shared_ptr<Edge<T>>, vector<shared_ptr<Edge<T>>>, LessThanByEdge<T> > priorityQueue;
            prims(graph.m_nodes.begin()->second, minimumSpanningTree, nodesMarked, priorityQueue);
        }
        return minimumSpanningTree;
    }

    template <class T>
    void printMinimumSpanningTree(set<shared_ptr<Edge<T>>> const& minimumSpanningTree)
    {
        for (auto const& edge : minimumSpanningTree)
        {
            cout<<edge->getId()<< " ";
        }
        cout<<endl;
    }
}
#endif