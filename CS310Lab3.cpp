// Ron Landagan
// CS310
// 11/20/2019

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "MyGraph.h"

using namespace std;

vector<string> createVectorFromCSV(string);
MyGraph createMyGraphFromVector(vector<string>);
void analyzeGraph(MyGraph);
void listNumberOfVertices(MyGraph);
void listZeroInboundEdgesVertices(MyGraph);
void listSelfEdgedVertices(MyGraph);
void listZeroOutboundEdgesVertices(MyGraph);
void listHeaviestEdge(MyGraph);

int main(int argc, char *argv[])
{   
    vector<string> input = createVectorFromCSV(argv[1]);
    MyGraph graph = createMyGraphFromVector(input);
    analyzeGraph(graph);

    system("pause");
    return 0;
}

/**
* Opens a passed-in .csv filename and creates a vector of inputs from it
*
* @param string of .csv filename to turn into inputs
* @return vector<string> containing the inputs from the .csv file
*/
vector<string> createVectorFromCSV(string inputFilename)
{
    string line, temp;
    ifstream inputFile;
    vector<string> csvInput;

    inputFile.open(inputFilename);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line, '\n'))
        {
            stringstream ss(line);
            while (getline(ss, temp, ','))
            {
                csvInput.push_back(temp);
            }
        }
        inputFile.close();
    }
    else
        cout << "Unable to open file" << endl;

    return csvInput;
}

/**
* Takes in a vector of string inputs and creates a MyGraph from it
*
* @param vector<string> of inputs
* @return MyGraph created from inputs
*/
MyGraph createMyGraphFromVector(vector<string> input)
{
    MyGraph sampleGraph;
    for (int row = 0; row < input.size(); row+=3)
    {   
        string source = input[row];
        string dest = input[row + 1];
        int cost = stoi(input[row + 2]);

        sampleGraph.addVertex(source);
        sampleGraph.addVertex(dest);
        sampleGraph.addEdge(source, dest, cost);
    }
    return sampleGraph;
}

/**
* Takes in a MyGraph and analyzes it for: number of vertices, vertices with
*   zero inbound edges, vertices with self-edges, vertices with zero 
*   outbound edges, and the heaviest edge between two vertices. Then the
*   results are printed.
*
* @param MyGraph to be analyzed
*/
void analyzeGraph(MyGraph graph)
{
    listNumberOfVertices(graph);
    listZeroInboundEdgesVertices(graph);
    listSelfEdgedVertices(graph);
    listZeroOutboundEdgesVertices(graph);
    listHeaviestEdge(graph);
}


/**
* Takes in a MyGraph and prints the number of vertices.
*
* @param MyGraph to be analyzed
*/
void listNumberOfVertices(MyGraph graph)
{
    int numberOfVertices = graph.getSize();
    cout << "The number of vertices of this graph: " << 
        numberOfVertices << endl << endl;
}


/**
* Takes in a MyGraph and prints the vertices with zero inbound edges.
*
* @param MyGraph to be analyzed
*/
void listZeroInboundEdgesVertices(MyGraph graph)
{
    vector<string> verticesWithZeroInboundEdges = 
        graph.findZeroInboundEdges();
    cout << "The following vertices have zero inbound edges:" << endl;
    for (int i = 0; i < verticesWithZeroInboundEdges.size(); i++)
    {
        cout << verticesWithZeroInboundEdges[i] << endl;
    }
    cout << endl;
}


/**
* Takes in a MyGraph and prints the vertices with self-edges.
*
* @param MyGraph to be analyzed
*/
void listSelfEdgedVertices(MyGraph graph)
{
    vector<string> selfEdgedVertices = graph.findSelfEdgedVertices();
    cout << "The following vertices have self edges:" << endl;
    for (int i = 0; i < selfEdgedVertices.size(); i++)
    {
        cout << selfEdgedVertices[i] << endl;
    }
    cout << endl;
}


/**
* Takes in a MyGraph and prints the vertices with zero outbound edges.
*
* @param MyGraph to be analyzed
*/
void listZeroOutboundEdgesVertices(MyGraph graph)
{
    vector<string> verticesWithZeroOutboundEdges = 
        graph.findZeroOutboundEdges();
    cout << "The following vertices have zero outbound edges:" << endl;
    for (int i = 0; i < verticesWithZeroOutboundEdges.size(); i++)
    {
        cout << verticesWithZeroOutboundEdges[i] << endl;
    }
    cout << endl;
}


/**
* Takes in a MyGraph and prints the heaviest edge and its vertices.
*
* @param MyGraph to be analyzed
*/
void listHeaviestEdge(MyGraph graph)
{
    vector<string> heaviestEdge = graph.findheaviestEdge();
    cout << "The following vertices have the heaviest edge:" << endl;
    for (int i = 0; i < heaviestEdge.size(); i++)
    {
        cout << heaviestEdge[i] << endl;
    }
    cout << endl;
}