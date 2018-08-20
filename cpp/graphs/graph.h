
#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include <atomic>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>

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
        // Avoid that a node can be constructed
    private:                       
        explicit Node(int _id, int _data) : id(_id), data(_data)
        {
            cout << "Creating Node " << data << endl;
        }
    public:
        ~Node()
        {
            cout << "Destroying Node " << data << endl;
        }
    private:
        // It was not moved to a free function, becasue the method isDetached is private and then can not be accessed from the free function.
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
            addOrReplace(children, to);
        }

        void addParent(weak_ptr<Edge<T>> from)
        {
            addOrReplace(parents, from);
        }

    public:
        void getChildren() const
        {
            set<int> childrenIds;
            for (auto& childWeak : children)
            {
                auto child = child.lock();
                if (child)
                {
                    childrenIds.insert(child->getId());
                }
            }
        }

        int getId() const { return id; }
        T getData() const { return data; }
        size_t getChildrenCount() const { return children.size(); }
        size_t getParentsCount() const { return parents.size(); }
    private:
        int id;
        T data;
        vector<weak_ptr<Edge<T>>> children;
        vector<weak_ptr<Edge<T>>> parents;
        friend class Graph<T>;
    };

    template <class T, class U>
    static bool removeFromUnorderedMap(unordered_map<U, T> & map, U id)
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

    static string createEdgeId(int fromId, int toId)
    {
        return to_string(fromId) + string("-") + to_string(toId);
    }


    template <class T>
    class Edge
    {
    private:
        explicit Edge(weak_ptr<Node<T>> _from, weak_ptr<Node<T>> _to, string _id, int _weight) : from(_from), to(_to), id(_id), weight(_weight) {}
    public:
        ~Edge()
        {
            cout << "Destroying Edge" << endl;
        }
        string getId() const { return id; }

    private:
        const weak_ptr<Node<T>>& getFrom() const { return from; }
        const weak_ptr<Node<T>>& getTo() const { return to; }
        bool isDetached() const
        {
            return from.expired() || to.expired();
        }
    private:
        weak_ptr<Node<T>> from;
        weak_ptr<Node<T>> to;
        string id;
        int weight = 0;        
        friend class Graph<T>;
        friend class Node<T>;
    };

    template<class T>
    class Graph
    {
    public:
        ~Graph()
        {
            cout << "Destroying Graph" << endl;
        }

        bool addNode(int id)
        {
            if (containsNode(id))
                return false;

            // We can not use make_shared, since it is not friend of Node class
            shared_ptr<Node<T>> node (new Node<T>(id, id));
            m_nodes[node->getId()] = node;
            return true;
        }

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
                removeEdges(node->children, nodeId, true);
                removeEdges(node->parents, nodeId, false);
            }
            else
            {
                return false;
            }
        }

        bool addEdge(int fromId, int toId, int weigth)
        {
            auto from = m_nodes.find(fromId);
            auto to = m_nodes.find(toId);
            if (from != m_nodes.end() && to != m_nodes.end())
            {   
                // Check if the edge exist
                auto edgeId = createEdgeId(fromId, toId);
                if (m_edges.find(edgeId) != m_edges.end())
                {
                    cout << "edges already exist" << endl;
                    return false;
                }
                // We can not use make_shared, since it is not friend of Edge class
                shared_ptr<Edge<T>> edge(new Edge<T>(from->second, to->second, edgeId, weigth));
                m_edges[edgeId] = edge;
                from->second->addChild(edge);
                to->second->addParent(edge);
                return true;
            }
            cout << "Edge was not added. Some of the nodes do not exist" << endl;
            return false;
        }

        bool containsNode(int id) const
        {
            auto it = m_nodes.find(id);
            return it != m_nodes.end();
        }

        bool removeNode(int id)
        {
            bool res = removeDetachedEdges(id);
            res &= removeFromUnorderedMap(m_nodes, id);            
            return res;
        } 

        bool removeEdge(int fromId, int toId)
        {
            return removeFromUnorderedMap(m_edges, createEdgeId(fromId, toId));
        }

        void print(int id) const
        {
            cout << "Nodes " << getNodesCount() << endl;
            cout << "Edges " << getEdgesCount() << " and valid "<< getValidEdges()<<endl;

            auto rootNode = m_nodes.find(id);
            if (rootNode != m_nodes.end())
            {
                // Track which nodes have been printed
                unordered_map<int, bool> areNodesPrinted;
                transform(m_nodes.begin(), m_nodes.end(), std::inserter(areNodesPrinted, areNodesPrinted.end()), [](auto const& map_type) { return std::make_pair(map_type.first, false); } );

                cout << " Root node " << rootNode->second->getData()<<endl;
                removeFromUnorderedMap(areNodesPrinted, id);

            }
        }

        size_t getNodesCount() const { return m_nodes.size(); }
        size_t getEdgesCount() const { return m_edges.size(); }
        const shared_ptr <Node<T>> getNode(int nodeId) const
        {
            if (containsNode(nodeId))
                return m_nodes.at(nodeId);
            else
                return nullptr;
        }

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

    private:
        int getValidEdges() const
        {
            return count_if(m_edges.begin(), m_edges.end(), [](auto const& map_type) { return !map_type.second->isDetached(); });
        }
                
    private:
        unordered_map<int, shared_ptr<Node<T>>> m_nodes;
        unordered_map<string, shared_ptr<Edge<T>>> m_edges;
    };
}

#endif