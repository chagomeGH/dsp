//  dfs.cpp
//  Created by Mariana Chagoyan
//  Dates 01/06/2017

#include <iostream>
#include <fstream>
#include "graphm.h"
#include "graphl.h"

using namespace std;

int main() {
    
    
    ifstream infile2("data32.txt");
    if (!infile2) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    
    //for each graph, find the depth-first search ordering
    for (;;) {
        GraphL G;
        G.buildGraph(infile2);
        if (infile2.eof())
            break;
        G.displayGraph();
        G.depthFirstSearch(); // find and display depth-first ordering to cout
    }
    cout << endl;
    return 0;
}
