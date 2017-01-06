# dsp
Dijkstra Shortest Path Algorithm in c++

Implementation Descriptions for Dijkstra's Shortest Path Algorithm

Programming Dijkstra's shortest path algorithm includes recovering the paths by finding the lowest cost path and displaying the cost and path from every node to every other node as well as the output of one path in detail.

The data to run this program is on data31.txt file and the first line tells the number of nodes, say n. Following is a text description of each of the 1 through n nodes, one description per line (50 chars max length). After that, each line consists of 3 ints representing an edge. If there is an edge from node 1 to node 2 with a label of 10, the data is: 1 2 10.  A zero for the first integer signifies the end of the data for that one graph. There are several graphs, each having at most 100 nodes. For example:

Sample Input picture (not part of data)
5
Aurora and 85th
Green Lake Starbucks
Woodland Park Zoo
Troll under bridge
PCC
1 2 50
1 3 20
1 5 30
2 4 10
3 2 20
3 4 40
5 2 20
5 4 25
0 0 0

Sample Output to display all (use this exact format, but blanks need not be exact):
Description From node To node Dijkstra's Path
Aurora and 85th
1 2 40 1 3 2
1 3 20 1 3
1 4 50 1 3 2 4
1 5 30 1 5
Green Lake Starbucks
2 1 ----
2 3 ----
2 4 10 2 4
2 5 ----
Woodland Park Zoo
3 1 ----
3 2 20 3 2
3 4 30 3 2 4
3 5 ----
Troll under bridge
4 1 ----
4 2 ----
4 3 ----
4 5 ----
PCC
5 1 ----
5 2 20 5 2
5 3 ----
5 4 25 5 4

Sample Output to display one path, for: G.display(1,4);
1 4 50 1 3 2 4
Aurora and 85th
Woodland Park Zoo
Green Lake Starbucks
Troll under Aurora bridge
1 2
3 4
5
40
20
30
20
20
10
50
25

Assumptions:
The input data file has correctly formatted data meaning that there will be 3 ints on one line of data for an edge (not 4 ints or chars, etc.). 
Data error checking is done in a way that an int you get is a valid value for the problem.
Graph Class includes the adjacency matrix, number of nodes, TableType array, and an array of NodeData. The only methods implemented for this class are the constructor, buildGraph (put in edge costs), insertEdge, removeEdge, findShortestPath, displayAll (uses couts to demonstrate that the algorithm works properly as shown), and display (to display one shortest distance with path). (Some utility functions are needed.)

class GraphM {
public:
...
private:
NodeData data[MAXNODES]; // data for graph nodes information
int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
int size; // number of nodes in the graph
TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
};
‐‐  The T in Dijkstra's algorithm (has dist, visited, and path), is a 2‐ dimensional array of structs. T is used to keep the current shortest distance (and associated path info) known at any point in the algorithm. This is row one in the 2D array. To adjust in use, add [source] as the row. 
For example, T[w].dist becomes T[source][w].dist .
struct TableType {
bool visited; // whether node has been visited
int dist; // shortest distance from source known so far
int path; // previous node in path of min dist
};

 The data member T is initialized in the constructor, sets all dist for the source node (source row) to infinity, sets all visited to false, and sets all path  to 0. The pseudo code given is for only one source node (node one was used). Another loop, controlling the source, allows for the shortest distance from all nodes to all other nodes. (Subscript zero is ignored. The nodes start at element one in the array. The zero elements is not used, or used otherwise.)



