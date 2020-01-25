// Ron Landagan
// CS310
// 11/20/2019

#include "stdafx.h"
#include "MyGraph.h"
#include <string>
#include <map>
using namespace std;

MyGraph::MyNode::MyNode(string val)
{
    _name = val;
}

MyGraph::MyNode::~MyNode()
{
}

string MyGraph::MyNode::getName()
{
    return _name;
}

/**
* Adds an edge to a MyNode
*
* @param string name of the destination MyNode
* @param int cost of the edge
*/
void MyGraph::MyNode::addEdge(string dest, int cost)
{
    _directedNeighbors.insert(pair<string, int>(dest, cost));
}

/**
* Removes an edge of a MyNode
*
* @param string name of the destination MyNode
*/
void MyGraph::MyNode::removeEdges(string dest)
{
    while (MyGraph::MyNode::contains(dest))
    {
        map<string, int>::iterator neighbor = _directedNeighbors.find(dest);
        _directedNeighbors.erase(neighbor);
    }
}

/**
* Checks to see if MyNode contains an edge to a specific MyNode
*
* @param string name of the destination MyNode
* @return bool of whether or not there exists an edge
*/
bool MyGraph::MyNode::contains(string dest)
{
    for (multimap<string, int>::iterator neighbor = _directedNeighbors.begin();
        neighbor != _directedNeighbors.end(); ++neighbor)
    {
        if (dest == (*neighbor).first)
            return true;
    }
    return false;
}

/**
* Checks to see if MyNode contains an edge to itself
*
* @return bool of whether or not there exists a self-edge
*/
bool MyGraph::MyNode::isSelfEdged()
{
    for (multimap<string, int>::iterator neighbor = _directedNeighbors.begin();
        neighbor != _directedNeighbors.end(); ++neighbor)
    {
        if ((*neighbor).first == _name)
        {
            return true;
        }
    }
    return false;
}

/**
* Finds and returns the heaviest edge and its MyNode destination.
*
* @return pair<string, int> of the heaviest edge cost and its MyNode name.
*/
pair<string, int> MyGraph::MyNode::findHeaviestEdge()
{
    pair<string, int> heaviestEdge;
    int currentHeaviest = INT_MIN;

    for (multimap<string, int>::iterator neighbor = _directedNeighbors.begin();
        neighbor != _directedNeighbors.end(); ++neighbor)
    {
        if ((*neighbor).second > currentHeaviest)
        {
            heaviestEdge.first = (*neighbor).first;
            heaviestEdge.second = (*neighbor).second;
            currentHeaviest = (*neighbor).second;
        }
    }

    return heaviestEdge;
}

/**
* Returns the number of outbound edges of the MyNode
*
* @return int of number of outbound edges
*/
int MyGraph::MyNode::getSize()
{
    return _directedNeighbors.size();
}

MyGraph::MyGraph()
{
}

MyGraph::~MyGraph()
{
}

/**
* Searches through the MyGraph for the passed-in MyNode name and returns its 
*   index position if it exists and -1 otherwise.
*
* @param string name of the MyNode
* @return int of the index position of the MyNode
*/
int MyGraph::_findIndexOfNode(string nodeName)
{
    for (int i = 0; i < _nodes.size(); i++)
    {
        if (_nodes[i].getName() == nodeName)
            return i;
    }
    return -1;
}

/**
* Creates a one-way connection from the source vertex to the destination vertex
*   with the parameter cost. Returns false and does not change the graph if 
*   either vertex specified does not yet exist in the graph.
*
* @param string name of the source MyNode
* @param string name of the destination MyNode
* @param int cost of the edge to be added
* @return bool of whether adding the edge was successful.
*/
bool MyGraph::addEdge(string source, string dest, int cost)
{
    if (!MyGraph::contains(source) || !MyGraph::contains(dest))
        return false;
    else
    {
        int nodeIndexPosition = _findIndexOfNode(source);
        _nodes[nodeIndexPosition].addEdge(dest, cost);
        return true;
    }
}

/**
* Deletes all edges from the source node to the destination node regardless of 
*   cost. Returns false if either vertex name is invalid.
*
* @param string name of the source MyNode
* @param string name of the destination MyNode
* @return bool of whether removing the edge was successful
*/
bool MyGraph::removeEdges(string source, string dest)
{
    if (!MyGraph::contains(source) || !MyGraph::contains(dest))
        return false;
    else
    {
        int nodeIndexPosition = _findIndexOfNode(source);
        _nodes[nodeIndexPosition].removeEdges(dest);
        return true;
    }
}

/**
* Inserts a vertex in the graph. If the vertex already exists in the graph, 
*   this method does nothing.
*
* @param string name of the MyNode vertex to be added
*/
void MyGraph::addVertex(string name)
{
    if (!MyGraph::contains(name))
    {
        _nodes.push_back(MyNode(name));
    }
}

/**
* Deletes the vertex, and all references to it, from the graph. It returns 
*   false if the vertex name does not appear in the graph.
*
* @param string name of the MyNode to be removed
* @return bool of whether removing the vertex was successful
*/
bool MyGraph::removeVertex(string name)
{
    if (!MyGraph::contains(name))
        return false;

    int nodeIndexPosition = _findIndexOfNode(name);
    _nodes.erase(_nodes.begin() + nodeIndexPosition);
    return true;
}

/**
* Returns true if the specified vertex appears in the graph.
*
* @param string name of the MyNode to be found
* @return bool of whether the vertex was found in the graph
*/
bool MyGraph::contains(string name)
{
    if (MyGraph::_findIndexOfNode(name) < 0)
        return false;
    else
        return true;
}

/**
* Returns true if the specified edge between the two vertex names exists in the
*   graph.
*
* @param string name of the source MyNode to be found
* @param string name of the destination MyNode to be found
* @return bool of whether the edge was found in the graph
*/
bool MyGraph::contains(string source, string dest)
{   
    if (!MyGraph::contains(source))
        return false;
    int sourceNodeIndex = MyGraph::_findIndexOfNode(source);
    if (_nodes[sourceNodeIndex].contains(dest))
        return true;
    else
        return false;
}

/**
* Returns the number of vertices in the MyGraph.
*
* @return int of number of vertices in MyGraph
*/
int MyGraph::getSize()
{
    return _nodes.size();
}

/**
* Returns a vector of strings containing the names of vertices with zero
*   inbound edges.
*
* @return vector<string> of vertices with zero inbound edges
*/
vector<string> MyGraph::findZeroInboundEdges()
{
    vector<string> zeroInboundEdges;
    bool currentlyZeroInboundEdges = true;

    for (int i = 0; i < _nodes.size(); i++)
    {
        currentlyZeroInboundEdges = true;
        for (int j = 0; j < _nodes.size(); j++)
        {
            if (_nodes[j].contains(_nodes[i].getName()))
                currentlyZeroInboundEdges = false;
        }
        if (currentlyZeroInboundEdges)
            zeroInboundEdges.push_back(_nodes[i].getName());
    }
    return zeroInboundEdges;
}

/**
* Returns a vector of strings containing the names of vertices with self edges.
*
* @return vector<string> of vertices with self edges
*/
vector<string> MyGraph::findSelfEdgedVertices()
{
    vector<string> selfEdgedVertices;

    for (int i = 0; i < _nodes.size(); i++)
    {
        if (_nodes[i].isSelfEdged())
            selfEdgedVertices.push_back(_nodes[i].getName());
    }
    return selfEdgedVertices;
}

/**
* Returns a vector of strings containing the names of vertices with zero
*   outbound edges.
*
* @return vector<string> of vertices with zero outbound edges
*/
vector<string> MyGraph::findZeroOutboundEdges()
{
    vector<string> zeroOutboundEdges;

    for (int i = 0; i < _nodes.size(); i++)
    {
        if (_nodes[i].getSize() == 0)
            zeroOutboundEdges.push_back(_nodes[i].getName());
    }
    return zeroOutboundEdges;
}

/**
* Returns a vector of strings containing the names of vertices with heaviest
*   edge and its cost.
*
* @return vector<string> of vertices with its heaviest cost
*/
vector<string> MyGraph::findheaviestEdge()
{
    vector<string> heaviestEdge;
    string heaviestSource, heaviestDest;
    int currentHeaviestEdge = INT_MIN;
    
    for (int i = 0; i < _nodes.size(); i++)
    {
        if (_nodes[i].findHeaviestEdge().second > currentHeaviestEdge)
        {
            heaviestSource = _nodes[i].getName();
            heaviestDest = _nodes[i].findHeaviestEdge().first;
            currentHeaviestEdge = _nodes[i].findHeaviestEdge().second;
        }
    }
    
    heaviestEdge.push_back(heaviestSource);
    heaviestEdge.push_back(heaviestDest);
    if(currentHeaviestEdge != INT_MIN)
        heaviestEdge.push_back(to_string(currentHeaviestEdge));
    return heaviestEdge;
}
