// Dalton Wemer
// CSC 325 Algorithms and Advanced Data Structures
// Homework 8: Disjoint Set Operations on Graphs
// April 28 2021

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <set>

using namespace std;
 
// This program implemnts disjoint set operations to be able to determine the number of connected components 
// in a graph that is given by an adjacency matrix. The program also shows all node that are present in each of the
// connected components. connect() and root() are the two Disjoint set operations, utilizing UnionFind
// we are able to detemine if a node in a graph is in fact a parent node

// Due to this program utlizing sets in C++, you must compile it using --std=c++11 
// For example, to compile this program I used: 
// g++ --std=c++11  hw8.cpp

// Array used to store the parents of all of the verticies
int parent[1000000];
int ccCount;
 
// Recursive solution to find the root node of a given element A
int root(int a)
{
    // Check to see if the current node is a parent (BASE CASE)
    if (a == parent[a]) {
        return a;
    }
 
    // If it is not a parent than we should continue moving up the graph
    return parent[a] = root(parent[a]);
}

 
// Connect vertex A with vertex B, where A is the node we are currently on
// and B is the destination
void connect(int a, int b)
{
    // Connect edges
    a = root(a);
    b = root(b);
 
    if (a != b) {
        parent[b] = a;
    }
}
 
// Function to find unique top most parents
int connectedComponents(int n)
{
    set<int> s;
 
    // Traverse all nodes and insert the highest order parent
    // from all of the connected components
    for (int i = 0; i < n; i++) {
 
        // insert the parent nodes into the set, we use set here
        // to avoid duplicate entries
        s.insert(parent[i]);
    }
    cout << endl;
    return s.size();
}

// Function to print the count of all of the top order elements
int connectedComponentCount(int n, vector<vector<int> > edges)
{

    for (int i = 0; i <= n; i++) 
    {
        parent[i] = i;
    }

    for (int i = 0; i < edges.size(); i++) 
    {
        connect(edges[i][0], edges[i][1]);
    }
 
    // Return integer of the number of seperate connected components
    return connectedComponents(n);
}

// Boolean function to return whether two nodes have the same parent
bool findParent(int A, int B)
{
    // If A and B have same root, that means that A and B are connected.
    if(A == root(B))       
    {
        return true;
    }else{
        return false;
    }
}

// Function to find unique top most parents
void connectedComponentsChildren(int n, int V)
{
   int parents[n];
   int componentCount[100];
   vector<vector<int> > components;

   for(int i=0; i < n; i++)
   {
       parents[i] = parent[i];
   }

   cout << "Connected Components: " << endl;
   for(int i = 0; i < n; i++)
   {
       vector<int> temp;
       for(int j=0; j < V; j++)
       {
           if(findParent(parent[i], parent[j]))
           {
               temp.push_back(j);
               cout << j << " ";
           }
       }
       if(temp.size() > 0)
       {
        cout << endl;
        ccCount++;
       }
   }
}

int main() {
    string fileName;
    fstream inputFile;
    int V;
    float array[100][100];
    

    vector<float>data;
    
    // Prompts user to enter the name of a data file
    cout << endl;
    cout << "Please place all data files in the same directory as this C++ source file!!" << "\n";
    cout << "Please enter the name of text file storing your adjacency matrix. You do not to put an extenstion." << "\n";
    cin >> fileName;
    cout << endl;
    // Adds the file extenstion to the file name
    fileName = fileName + ".txt";
    
    
    cout << "Attempting to open " << fileName << "...";
    
    // Open file for reading 
    inputFile.open(fileName,ios::in); 

    if (inputFile.is_open())
    { 
        cout << "SUCCESS!" << endl;
        cout << endl;

        inputFile >> V;

        // Read the text file and store the data into a 2D array
        // with the size m x m.
        int pos = 0;

        for(int i = 0; i < V; i++)
        {
          for (int j = 0; j < V; j++)
          {
            inputFile >> array[i][j];
            pos++;
          }
        }

        // Print out the adjacency matrix in a clean and clear way
        cout << "Adjacency Matrix " << endl;
        cout << endl;
        cout << endl;

        cout << "    ";
        for(int i = 0; i < V; i++)
        {
            cout << "v" << i << "  ";
        }
        cout << endl;
        for(int i = 0; i < V * 6; i++)
        {
            cout << "-";
        }

        cout << endl;
        for(int i = 0; i < V; i++)
        {
            cout << "v" << i << ":" << "  ";
          for (int j = 0; j < V; j++)
          {
              cout << array[i][j] << "   ";
          }
          cout << endl;
        }

        cout << endl;

        // Convert the read in adjancency matrix to 2D vector
        // representing the edges of the graph
        vector<vector<int> > E; 
        
        for(int i = 0; i < V; i++)
        {
          for (int j = 0; j < V; j++)
          {
           if(array[i][j] != 0)
           {
             for(int column = j; column < V; column++)
             {
                 vector<int> tempVect;
                 if(array[i][column] != 0)
                 {
                     tempVect.push_back(i);
                     tempVect.push_back(j);
                     E.push_back(tempVect);
                     break;
                 }
                    tempVect.push_back(i);
                    tempVect.push_back(i);
                    E.push_back(tempVect);
             }
           }
          }
        }

        int numOfConnectedComponents = connectedComponentCount(V, E);

        connectedComponentsChildren(numOfConnectedComponents, V);
        cout << endl;
        cout << "The number of connected components in the graph is: " << ccCount << endl;
        
        
        cout << '\n';
        
        
      // Close the file
      inputFile.close();
    } else {
      cout << "Failed to open specified data file, please check your file name and try again!" << endl;
    }
}