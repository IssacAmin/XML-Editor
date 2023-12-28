#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include <vector>
#include "utilities/utilities.h"

#include<string>
using namespace std;
typedef struct GraphNode{
    string name;
    string id;
    int inEdges;
    GraphNode * next;

} GraphNode;
extern vector<GraphNode*> adjList;
GraphNode* set_Node(string name , string id);
vector<GraphNode*> build_Graph(string file_data);
GraphNode* add_follower(string id);
string most_influencer();
string most_active();
vector<string> common_users(string user1 , string user2);
vector<string> suggest(string user);
#endif // GRAPH_H_INCLUDED
