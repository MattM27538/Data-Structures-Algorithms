// Graph.cpp
// Author: Matthew Martinez
// Description: File contains constructor for a graph and common 
// functions to interact with the graph.

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

using std::cout;
using std::endl;
using std::vector;

/*Description: Default constructor for Graph class
  Parameters: N/A
  Returns: N/A
*/
Graph::Graph(){
  nodes = {};
}

/*Description: Function printAdjList prints all neighbors for each node in graph.
  Parameters: N/A
  Returns: void
*/
void Graph::printAdjList(){
  for(int i = 0; i < nodes.size(); i++) {
    cout << nodes[i]->id << ": ";

    for(int j = 0; j < nodes[i]->neighbors.size(); j++) {
      cout << nodes[i]->neighbors[j]->id << " ";
    } 

    cout << endl;
  }
}

/*Description: Function isNeighbor takes two int parameters for 
  node IDs. Returns true if the nodes are adjacent, else 
  returns false.
  Parameters: int u, int v
  Returns: bool
*/
bool Graph::isNeighbor(int u, int v){
  for (unsigned int i = 0; i < nodes[u]->neighbors.size(); i++) {
    if (nodes[u]->neighbors[i]->id == nodes[v]->id) {
      return true;
    } 
  }
  return false;
}

/*Description: Function DFS performs depth first search on graph.
  Parameters: N/A
  Returns: void
*/
void Graph::DFS(){
  // reset member variables for all nodes
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
    nodes[i]->discovered = -1;
    nodes[i]->finished = -1;
  }

  // visit all unvisited nodes
  int time = 0;
  for (int i = 0; i < nodes.size(); i++) {
    if (nodes[i]->visited == false) {
      time = DFSVisit(i,time);
    }
  } 
}

/*Description: Function DFSVisit sets node discovery times during DFS,
  iterates through all neighbors for each node, and sets/returns time when nodes
  are finished.
  Parameters: int s, int time
  Returns: int
*/
int Graph::DFSVisit(int s, int time){
  time = time + 1;
  nodes[s]->discovered = time;
  nodes[s]->visited = true;

  // visit all unvisited neighbors for each node and set member variables.
  for( int j = 0; j < nodes[s]->neighbors.size(); j++) {
    if(nodes[s]->neighbors[j]->visited == false) {
      nodes[s]->neighbors[j]->predecessor = nodes[s];
      time = DFSVisit(nodes[s]->neighbors[j]->id,time);
    }
  }
  
  time = time + 1;
  nodes[s]->finished = time;
  return time;
}

/*Description: Function BFS performs breadth first search
  on graph. Function takes parameter int s as source node.
  Parameters: int s
  Returns: void
*/
void Graph::BFS(int s){
  // reset member variables for all nodes
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->dist = INT_MAX;
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }
  
  nodes[s]->dist = 0;
  nodes[s]->visited = true;

  std::vector<std::shared_ptr<Node>> visited;
  visited.insert(visited.begin(),nodes[s]);

  while (visited.size() > 0) {
    s = visited.back()->id;
    visited.pop_back();

    // visit all unvisited neighbors for each node and set member variables
    for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
      if (nodes[s]->neighbors[i]->visited == false) {
        nodes[s]->neighbors[i]->dist = nodes[s]->dist + 1;
        nodes[s]->neighbors[i]->visited = true;
        nodes[s]->neighbors[i]->predecessor = nodes[s];
        visited.insert(visited.begin(),nodes[s]->neighbors[i]);
      }
    }
  }
}

/*Description: Function distancesFrom returns vector with distances
  from source node (int s).
  Parameters: int s
  Returns: std::vector<int>
*/
std::vector<int> Graph::distancesFrom(int s){
  std::vector<int> nodeDistances;
  BFS(s);

  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodeDistances.push_back(nodes[i]->dist);
  }

  return nodeDistances;
}

/*Description: Function determines if graph is bipartite. Returns
  true if true, else returns false.
  Parameters: N/A
  Returns: bool
*/
bool Graph::isTwoColorable(){
  if (nodes.size() == 0) {
    return false;
  }
  // reset dist member variable for all nodes in graph
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->dist = 0;
  }

  nodes[0]->dist = 1;

  std::vector<std::shared_ptr<Node>> visited;
  visited.insert(visited.begin(),nodes[0]);

  while (visited.size() > 0) {
    int s = visited.back()->id;
    visited.pop_back();

    // visit all unvisited neighbors for each node. If neighbor is
    // unvisited mark as visited. If neighbor is visited, if neighbor dist
    // is same as node dist return false.
    for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
      switch (nodes[s]->dist) {
        case 1:{
          switch (nodes[s]->neighbors[i]->dist) {
            case 0: {
              nodes[s]->neighbors[i]->dist = 2;
              visited.insert(visited.begin(),nodes[s]->neighbors[i]);
            }
            break;
            case 1: return false;
            break;
            default:{}
          }
        }
        break;     
        case 2: {
          switch (nodes[s]->neighbors[i]->dist) {
            case 0: {
              nodes[s]->neighbors[i]->dist = 1;
              visited.insert(visited.begin(),nodes[s]->neighbors[i]);
            }
            break;
            case 2: return false;
            break;
            default:{}
          }
        }
      }
    }
  }

  return true;
}

/*Description: Function determines if there is a path between
  all nodes in graph. Returns true if true, else returns false.
  Parameters: N/A
  Returns: bool
*/
bool Graph::isConnected(){
  if (nodes.size() > 0){
    BFS(nodes[0]->id);
  }
  
  for (unsigned int i = 0; i < nodes.size(); i++) {
    if (nodes[i]->visited == false) {
      return false;
    }
  }
  return true;
}

/*Description: Function determines if there is at least one
  instance where there are two unqiue paths from at least one node 
  back to itself in graph. Returns true if true, else returns false.
  Parameters: N/A
  Returns: bool
*/
bool Graph::hasCycle(){
  // reset member variables for all nodes in graph
  for (unsigned int i = 0; i < nodes.size(); i++) {
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }
  
  nodes[0]->visited = true;

  std::vector<std::shared_ptr<Node>> visited, allVisitedList;
  int s;
  visited.insert(visited.begin(),nodes[0]);

  while (visited.size() > 0) {
    s = visited.back()->id;
    allVisitedList.push_back(visited.back());

    // visit all unvisited neighbors for each node, set member variables,
    // and return true if there is a backedge.
    for (unsigned int i = 0; i < nodes[s]->neighbors.size(); i++) {
      if (nodes[s]->neighbors[i]->visited == false) {
        nodes[s]->neighbors[i]->visited = true;
        nodes[s]->neighbors[i]->predecessor = nodes[s];
        visited.insert(visited.begin(),nodes[s]->neighbors[i]);
      } else {
          if (nodes[s]->neighbors[i] != nodes[s]->predecessor) {
            return true;
          }
        }
    }

    visited.pop_back();
    }
  return false;
}

/*Description: Function determines if nodes u and v have a 
  path through the graph linking the two.
  Parameters: int u, int v
  Returns: bool
*/
bool Graph::isReachable(int u, int v){
  if (nodes.size() > 0){
    BFS(nodes[u]->id);
  }

  if (nodes[v]->visited == true) {
    return true;
  }

  return false;
}