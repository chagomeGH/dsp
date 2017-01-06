//
//  graphm.h
//  lab3
//  Created by Mariana Chagoyan
//  Dates 10/20/14 to 10/23/14

#ifndef graphm_h
#define graphm_h

#include "nodedata.h"
#include <climits>
#include <iomanip>

//------------------------------------------------------------------------------
/*  GraphM class does not include copy constructor and destructor and implements
    Number of nodes, GraphM, TableType and NodeData objects to represent a
    directed and weighted graph with an adjacency matrix array.
 
    1. Number of nodes, stores an integer value representing the size.
    2. NodeData data array store string values holding location nodes locations.
    3. Integer C[row][column] array stores three integer values representing
       these values in this particular order:
       fromNode(row), toNode(column(column), and edgCost (distance).
    4. Strut TableType T[row][column] array stores these follwoing variables.
       a) integer variable for distance, which is the edgeCost between 2 nodes
       b) boolean variable visited set to true if node is visited if not false
       c) integer variable path that holds the value of the previous node.
 
    All the above data is extracted from a text file to build and update data
    in their corresponding GraphM objects. In addition, this class also implem
    ments Dijkstra's algorithm which finds shortest path from initial to final
    
    Assumtions:
    1. Maximum capacity for the matrix array is the 100 nodes
    2. Firs line integer represetns the actual nodes on both array and matrix
    3. Lines with texts represent node locations with NodeData(string) values
    4. Lines with three integers represent: fromNode, toNode and edgeCost
    5. 3 zeros in one line represent the end of the data for one graph matrix
    6. Negative integers are ignored as well as other incorrect input data
*/
//------------------------------------------------------------------------------

const int MAXNODES = 100;
const int infinity = INT_MAX;

class GraphM{
    
public:
    
    GraphM();                       // construcotr
    void buildGraph(ifstream &);    // updates edgeCosts between nodes
    bool insertEdge(int, int, int); // inserts edgeCost from one node to another
    bool removeEdge(int, int);      // removes edgeCost from one to another
    
    // finds shortest path between every node to every other node in the graph
    // updates T table with the shortest path information
    void findShortestPath();
    
    // displays all nodes and paths in a graph
    void displayAll()const;
    
    // finds path from initial to final node and keeps track of previous node.
    void findPath(const int, const int)const;
    
    // finds path from initial to final node and keeps track of previous node.
    // as well as the corresponding information stored on data array.
    void findPathData(const int, const int)const;
    
    // display the shortest distance with path between fromNode to toNode
    void display(const int, const int)const;
    
private:
    
    struct TableType{
        
        bool visited;       // whether a node has been visited
        unsigned int dist;  // shortest distance from source known so far
        int path;           // previous node in path of min dist
    };
    
    NodeData data[MAXNODES];            // data for graph nodes
    int C[MAXNODES][MAXNODES];          // adjacency matrix array storing cost
    int size;                           // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];    // t array struct storing data for
                                        // variables visited, dist and path
};

#endif
