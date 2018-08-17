
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

        void addChildren(weak_ptr<Edge<T>> to)
        {
            //auto nextAvailable = findNextInvalidPointer(children);
            auto nextAvailable = find_if(children.begin(), children.end(), [](const weak_ptr<Edge<T>>& e) { return e.expired() ? true : e.lock()->isDetached(); });
            // If there is some expired pointer, replace it
            if (nextAvailable != children.end())
            {
                //*children.emplace(nextAvailable, to);
                *nextAvailable = to;
            }
            else
            {
                children.push_back(to);
            }
            auto ptrEdge = to.lock();
            auto ptrNode = ptrEdge->getTo().lock();
            cout << "Edge from Node " << data << " to " << ptrNode->getData() << " was added." << endl;
        }
        
        void getChildren()
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
    private:
        int id;
        T data;
        vector<weak_ptr<Edge<T>>> children;
        friend class Graph<T>;
    };

    template <class T>
    static bool removeFromUnorderedMap(unordered_map<int, T> & map, int id)
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


    template <class T>
    class Edge
    {
    private:
        explicit Edge(weak_ptr<Node<T>> _from, weak_ptr<Node<T>> _to, int _id, int _weight) : from(_from), to(_to), id(_id), weight(_weight) {}
    public:
        ~Edge()
        {
            cout << "Destroying Edge" << endl;
        }
        int getId() const { return id; }
        const weak_ptr<Node<T>>& getFrom() const { return from; }
        const weak_ptr<Node<T>>& getTo() const { return to; }
        bool isDetached() const
        {
            return from.expired() || to.expired();
        }
    private:
        weak_ptr<Node<T>> from;
        weak_ptr<Node<T>> to;
        int id;
        int weight = 0;        
        friend class Graph<T>;
    };

    template<class T>
    class Graph
    {
    public:
        ~Graph()
        {
            cout << "Destroying Graph" << endl;
        }

        int addNode(T data)
        {
            // We can not use make_shared, since it is not friend of Node class
            shared_ptr<Node<T>> node (new Node<T>(++nodeIds, data));
            nodes[node->getId()] = node;
            return node->id;// node->getId();
        }

        bool addEdge(int fromId, int toId, int weigth)
        {
            auto from = nodes.find(fromId);
            auto to = nodes.find(toId);
            if (from != nodes.end() && to != nodes.end())
            {                
                // Find if there is any edge detached, so it can be reused
                auto nextAvailable = find_if(edges.begin(), edges.end(), [](auto &map_type) { return map_type.second->isDetached(); });
                int edgeId;
                if (nextAvailable != edges.end())
                    edgeId = nextAvailable->second->getId();
                // Incresae a new edge id
                else
                    edgeId = ++edgeIds;

                // We can not use make_shared, since it is not friend of Edge class
                shared_ptr<Edge<T>> edge(new Edge<T>(from->second, to->second, edgeId, weigth));
                edges[edgeId] = edge;
                from->second->addChildren(edge);
                return true;
            }
            cout << "Edge was not added. Some of the nodes do not exist" << endl;
            return false;
        }

        bool containsNode(int id)
        {
            auto it = nodes.find(id);
            return it != nodes.end();
        }

        bool removeNode(int id)
        {
            return removeFromUnorderedMap(nodes, id);
        } 

        bool removeEdge(int id)
        {
            return removeFromUnorderedMap(edges, id);
        }

        void print(int id)
        {
            cout << "Nodes " << nodes.size() << endl;
            cout << "Edges " << edges.size() << " and valid "<< getValidEdges()<<endl;

            auto rootNode = nodes.find(id);
            if (rootNode != nodes.end())
            {
                // Track which nodes have been printed
                unordered_map<int, bool> areNodesPrinted;
                transform(nodes.begin(), nodes.end(), std::inserter(areNodesPrinted, areNodesPrinted.end()), [](auto const& map_type) { return std::make_pair(map_type.first, false); } );

                cout << " Root node " << rootNode->second->getData()<<endl;
                removeFromUnorderedMap(areNodesPrinted, id);

            }
        }

    private:
        int getValidEdges() const
        {
            return count_if(edges.begin(), edges.end(), [](auto const& map_type) { return !map_type.second->isDetached(); });
        }
                
    private:
        std::atomic<int> nodeIds = 0;
        std::atomic<int> edgeIds = 0;
        unordered_map<int, shared_ptr<Node<T>>> nodes;
        unordered_map<int, shared_ptr<Edge<T>>> edges;
    };
}

#endif