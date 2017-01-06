//  graphm.cpp
//  Created by Mariana Chagoyan
//  Dates 10/20/14 to 10/23/14

#include "graphm.h"

//------------------------------------------------------------------------------
/*  constructor
    creates GraphM class objectas and sets their variables values appropiately
    size to zero
    C[i][j] array values to -1 and zero depending of their location
    T[i][j] struct array to the following:
    vistited to false, distance to infinity and path to the row matrix i
*/
GraphM::GraphM(){
    size = 0;
    
    for(int i = 0; i < MAXNODES; i++){
        for(int j = 0; j < MAXNODES; j++){
            
            C[i][j] = -1;
            if(i == j){
                
                C[i][j] = 0;
            }
            T[i][j].visited = false;
            T[i][j].dist = infinity;
            T[i][j].path = i;
        }
    }
}
//------------------------------------------------------------------------------
/*  buildGraph
    buils a graph adjacency matrix by extracting data from input of a text file
    and using getLine function to pass data into C[i][j] and T[i][j] arrays.
    First line passes an integer representing size of NodeData data array.
    Second set of lines passes the strings to be store in NodeData array the 
    amount of lines are based on the size number previously passed.
    Third set of lines, each line passes 3 integer that represents graph 
    coordinates as fromNode and toNode and the distance as the edgeCost.
    @param infile, texfile passing the data that needs to be extracted to build
    C and T matrix arrays
 */
void GraphM::buildGraph(ifstream& infile){
    
    infile >> size;
    if(infile.eof())return;
    
    string s;
    getline(infile, s);
    for(int i=0; i < size; i++){
        data[i].setData(infile);
    }
    int fromNode = 0, toNode =0 , edgeCost = 0;
    for(;;){
        infile >> fromNode >> toNode >> edgeCost;
        
        if(fromNode >= 0 && toNode >= 0 && edgeCost >= 0){
            if(fromNode != 0 && toNode != 0 && edgeCost != 0){
                if(fromNode == toNode){
                    C[fromNode][toNode] = 0;
                    T[fromNode][toNode].visited = true;
                    T[fromNode][toNode].dist = 0;
                    T[fromNode][toNode].path = toNode;
                }
                else{
                    C[fromNode][toNode] = edgeCost;
                    T[fromNode][toNode].visited = false;
                    T[fromNode][toNode].dist = infinity;
                    T[fromNode][toNode].path = toNode;
                }
            }
            else{
                break;
            }
        }
        else{
            continue;
        }
    }
}
//------------------------------------------------------------------------------
/*  insertEdge
    inserts an edge into graph between to given nodes
    @fromNode, integer holding row location on C[row][column] array
    @toNode, integer holding column location C[row][column] array
    @edgeCost, integer holding distance or edgeCost from row to column
    returns true, if edge values were successfully inserted or false it not
 */
bool GraphM::insertEdge(int fromNode, int toNode, int edgeCost){
  
    bool inserted = false;
    
    if(fromNode >= 0 && toNode >= 0 && edgeCost >= 0){
        
        C[fromNode][toNode] = edgeCost;
        inserted = true;
    }
    else{
        
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
/*  removeEdge
    removes an edge between two given nodes
    @fromNode, integer holding row location on C[row][column] array
    @toNode, integer holding column location C[row][column] array
    returns true, if edge values were successfully removed or false it not
 */
bool GraphM::removeEdge(int fromNode, int toNode){
    
    bool removed = false;
    
    if(fromNode >= 0 && toNode >= 0){
     
        removed = true;
    }
    else{
        return false;
        
    }
    return true;
}
//------------------------------------------------------------------------------
/*  findShortestPath
    finds the shortes path by using Dijkstra's algorithm.
    Access C[i][j] array to acces edgeCost(distance) from one node to another 
    Compare distances between one node to different nodes if an edge exits and
    update and stores the minimum distance by accessing T[i][j] struct array as 
    well as the rest of their variables of visited and path.
*/
void GraphM::findShortestPath(){
    
    int costShortestPath;
    int minV;
    
    for(int source = 1; source <= size; source++){
        // sets the source path to itself to zero
        T[source][source].dist = 0;
        
        for(int v = 1; v <= size; v++){
            costShortestPath = infinity;
            minV = -1;
            
            for(int i = 1; i <= size; i++){
                if(T[source][i].dist < costShortestPath){
                    if(T[source][i].visited == false){
                        // starts out with the infinity value
                        costShortestPath = T[source][i].dist;
                        // finds the minV
                        minV = i;
                    }
                }
            }
            if(minV == -1){
                continue;
            }// mark as visited
            T[source][minV].visited = true;
            
            for(int w = 1; w <= size; w++){
                    
                if(T[source][w].visited || C[minV][w] == -1){
                    continue;
                }
                else{
                    // costPath from V to w + costPath from source W to W
                    if(C[minV][w]+T[source][minV].dist < T[source][w].dist){
                        // update distance
                        T[source][w].dist= C[minV][w]+T[source][minV].dist;
                        // assign the path to T array
                        T[source][w].path = minV;
                    }
                }
            }
        }
    }
}
//------------------------------------------------------------------------------
/*  displayAll
    uses couts to display all data stored on T[i][j] struct array and uses 
    findPath function to access all the different sequence paths obtained from 
    first node to end node as well as the corresponding disance.
 */
void GraphM::displayAll()const{
    
    cout << "Description                From node   To node   Dijkstra's";
    cout << "   Path" << endl;
   
    for(int i = 1; i < size+1; i++){
        cout << setw(45) << left << data[i-1] << endl;
        
        for(int j = 1; j < size +1; j++){
            if(T[i][j].dist > 0 && T[i][j].dist < infinity){
                
                cout << setw(30) << right << i << setw(10) << j << setw(12);
                cout << T[i][j].dist << setw(11);
                
                findPath(i, j);
                cout << endl;
            }
            else{
                
                if(i != j){
                    cout << setw(30) << right << i << setw(10) << j << setw(12);
                    cout << "----" << setw(10) << endl;
                }
                else{
                    
                    continue;
                }
            }
        }
    }
    cout << endl;
}
//------------------------------------------------------------------------------
/*  display
    uses couts to display the shortest distance with path information between 
    the fromNode to toNode. this data is stored on T[i][j] array and uses
    findPath function to access one sequence path obtained from first node
    to end node as well as the corresponding disance.
    @fromNode, integer holding row location on T[row][column] struct array
    @toNode, integer holding column location T[row][column] struct array
*/
void GraphM::display(const int fromNode, const int toNode)const{
    
    cout <<"Sample Output to display one path, for:      G.display(";
    cout << fromNode << "," << toNode << ");" << endl;
    
    if(T[fromNode][toNode].dist != infinity){
        
        cout << "     " << fromNode << "     " << toNode << "     ";
        cout << T[fromNode][toNode].dist << right << setw(20);
        findPath(fromNode, toNode);
        cout << endl;
    }
    else{
        cout << left << setw(12) << toNode << setw(12) << fromNode;
        cout << "----       THERE IS NO PATH ";
        
    }
    findPathData(fromNode, toNode);
    cout << endl;
}
//------------------------------------------------------------------------------
/*  findPath 
    finds path from initial to final node by accessing this particular data on 
    T[i][j] struct array and by keeping track of previous node.
    @fromNode, integer holding row location on T[row][column] struct array
    @toNode, integer holding column location T[row][column] struct array
 */
void GraphM::findPath(const int fromNode, const int toNode)const{
    
    if(fromNode != toNode)
        if(T[fromNode][toNode].path != 0)
            
            findPath(fromNode, T[fromNode][toNode].path);
    cout << toNode << " ";
}
//------------------------------------------------------------------------------
/*  findPathData
    find the data belonging to the path from initial node to the final node 
    by accessing this data on T[i][j] struct array and by keeping track of 
    previous node as well as the corresponding information on data array.
    @fromNode, integer holding row location on T[row][column] struct array
    @toNode, integer holding column location T[row][column] struct array
*/
void GraphM::findPathData(const int fromNode, const int toNode)const{
    
    if(fromNode != toNode)
        if(T[fromNode][toNode].path != 0)
            findPathData(fromNode, T[fromNode][toNode].path);
    
    cout << data[toNode-1] << endl;
}
//------------------------------------------------------------------------------



