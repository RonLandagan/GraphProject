// Ron Landagan
// CS310
// 11/20/2019

#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class MyGraph
{
private:
    class MyNode
    {
        private:
            string _name;
            multimap<string, int> _directedNeighbors;
        public:
            MyNode(string);
            ~MyNode();
            string getName();
            void addEdge(string, int);
            void removeEdges(string);
            bool contains(string);
            bool isSelfEdged();
            pair<string, int> findHeaviestEdge();
            int getSize();
    };
    vector<MyNode> _nodes;
    int _findIndexOfNode(string);

public:
    MyGraph();
    ~MyGraph();

    bool addEdge(string source, string dest, int cost);
    bool removeEdges(string source, string dest);
    void addVertex(string name);
    bool removeVertex(string name);
    bool contains(string name);
    bool contains(string source, string dest);

    int getSize();
    vector<string> findZeroInboundEdges();
    vector<string> findSelfEdgedVertices();
    vector<string> findZeroOutboundEdges();
    vector<string> findheaviestEdge();
};

