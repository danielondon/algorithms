#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <memory>
#include <map>
#include <queue>
#include <climits>

using namespace std;

template<typename EnumType>
using UnderlyingType = typename std::underlying_type<EnumType>::type;

template<typename EnumType>
constexpr auto convertEnumToUnderlyingType(EnumType enumValue) -> UnderlyingType<EnumType>
{
    return static_cast<UnderlyingType<EnumType>>(enumValue);
}

template <typename TCollection>
void printCollection(TCollection const& collection)
{
    for (auto const& value : collection)
        cout<< value <<" ";
    cout<<endl;
}

template <class T>
void printVector(const vector<T> & numbers)
{
    std::for_each(numbers.cbegin(), numbers.cend(), [] (const T c) {std::cout << c << " ";} );
    cout<<endl;
}

template <class T>
void printMatrix(const vector<vector<T>> & matrix)
{
    std::for_each(matrix.cbegin(), matrix.cend(), [] (const auto& v) { printVector(v); } );
    cout<<endl;
}

enum class Color
{
    Red,
    Blue,
    Green,
    Invalid
};

std::ostream& operator<< (std::ostream& stream, const Color& color)
{
    stream<<convertEnumToUnderlyingType(color);
}


struct Node
{
    //int value;
    
    void addChild(shared_ptr<Node> child)
    {
        children.push_back(child);
    }
    
    ~Node()
    {
        cout<<"Destroying Node"<<endl;
    }
private:
    vector<shared_ptr<Node>> children;  
};

struct Vertex
{
    Vertex(int _id, int _data) : id(_id), data(_data), visited(false) 
    {
        cout<<"Creating Vertex "<<id<<endl;
    }
    
    ~Vertex()
    {
        cout<<"Destroying Vertex "<<id<<endl;
        //adjacents.clear();
    }

    void addEdge(shared_ptr<Vertex> to, int weigth)
    {
        //edges.push_back(Edge(to, weigth));
    }
    
    void addAdjacent(weak_ptr<Vertex> to)
    {
        adjacents.push_back(to);
        auto ptr = to.lock();
        cout<<"Edge from Vertex "<<id<<" to "<<ptr->id<<" was added."<<endl;
    }

    int id;
    bool visited;
    int data;
    //vector<Edge> edges;
    vector<weak_ptr<Vertex>> adjacents;
};


struct Edge
{
    Edge(shared_ptr<Vertex> _from,  shared_ptr<Vertex> _to, int _weight) : from(_from), to(_to), weight(_weight) {}
    shared_ptr<Vertex> from;
    shared_ptr<Vertex> to;
    int weight;
    
    ~Edge()
    {
        cout<<"Destroying Edge"<<endl;
    }
};

struct Graph
{
    ~Graph()
    {
        cout<<"Destroying Graph"<<endl;
    }
    
    shared_ptr<Vertex> getVertex(int id)
    {
        auto it = find_if(nodes.begin(), nodes.end(), [&] (const shared_ptr<Vertex>& v) { return v->id == id; } );
        if (it != nodes.end())
        {
            cout<<"Node found "<< (*it)->id <<endl;
            return *it;
        }
        
        return nullptr;
    }
    
    shared_ptr<Vertex> addVertex(int id, int data)
    {
        auto vertex = make_shared<Vertex>(id, data);
        nodes.push_back(vertex);
        cout<<"Vertex was added"<<endl;
        return vertex;
    }
    
    bool containsVertex(shared_ptr<Vertex> vertex)
    {
        auto it = find(nodes.begin(), nodes.end(), vertex);
        return it != nodes.end();
    }
    
    void removeVertex(shared_ptr<Vertex> vertex)
    {
        cout<<"Removing vertex"<<endl;
        auto it = find(nodes.begin(), nodes.end(), vertex);
        if (it != nodes.end())
        {
            nodes.erase(it, it + 1);
            cout<<"Vertex removed"<<endl;
        }
    }
    
    void addEdge(shared_ptr<Vertex> from, shared_ptr<Vertex> to, int weigth)
    {
        cout<<"Adding edge"<<endl;
        auto itFrom = find(nodes.begin(), nodes.end(), from);
        if (itFrom != nodes.end())
        {
            auto itTo = find(nodes.begin(), nodes.end(), to);
            if (itTo != nodes.end())
            {
                (*itFrom)->addAdjacent(*itTo);
            }
            else
                cout<<"To Vertex not found"<<endl;
        }
        else
        {
            cout<<"From Vertex not found"<<endl;
        }
    }

    const vector<shared_ptr<Vertex>>& getNodes() const
    {
        return nodes;
    }

private:
    vector<shared_ptr<Vertex>> nodes;

};
