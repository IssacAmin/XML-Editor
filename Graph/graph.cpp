#include "Graph.h"
#include "fstream"
vector<GraphNode*> adjList; // vector of pointers to the followers of the users
int followers[1000] = {0} ; // array for each user to count his followers list
GraphNode* set_Node(string name , string id){
    //function to add new node to the graph
	GraphNode* newNode = new GraphNode();
	newNode->name = name;
	newNode->id = id;
	newNode->next = NULL;
	newNode->outEdges = 0;
	return newNode;
}
GraphNode* add_following(string id){
// function to add follower and connect between 2 users
	GraphNode* newNode = new GraphNode();
	newNode->id = id;
	newNode->next = NULL;
	newNode->outEdges = 0;
	return newNode;
}
string most_influencer(){
    // function to get the most influencer user (who has the most followers)
	int maximum = 0;
	int index = 0;
	string ID ;
	int length = (sizeof(followers)) / sizeof(followers[0]);
	for(int i = 0 ; i < length ; i++){
// here we use the following array which contain the number of following list for each user and we loop on them to get the maximum one
		if(followers[i] > maximum){
			maximum = followers[i];
			index = i;
		}
	}
	ID = to_string(index);
	for(unsigned int i = 0 ; i < adjList.size() ; i ++){
		if(ID == adjList[i]->id) {
			index = i;
			break;
		}
	}
	return adjList[index]->name;
}
string most_active(){
// function to get the most active user who follows the most
    int maximum = 0;
	int index = 0;
	for(unsigned int i = 0 ; i < adjList.size(); i ++){
/*
there is a data member called outEdges which is the number of his following list and here we loop on them to get
the maximum number of followers
    */
		if(adjList[i]->outEdges > maximum){
			maximum = adjList[i]->outEdges;
			index = i;
		}
	}
	return adjList[index]->name;
}
vector<string> ID_to_Name(vector<string> ID){
	vector<string> names;
	int id;
	for(unsigned int i = 0 ; i < ID.size() ; i++){
		id = stoi(ID[i]) - 1;
		names.push_back(adjList[id]->name);
	}
	return names;
}
vector<GraphNode*> build_Graph(string file_data){
    // building the graph using adjacency list way
	vector<string> xmldata = oneElementPerLine(file_data);
	int i = 0;
	int num_of_users = 0;
	int num_followers = 0;
	string line;
	string id, name;
	GraphNode* temp;
	/*	Loop until we save all the users and their followers */
	while (xmldata[i] != "</users>")
	{
		i++;
		while (xmldata[i] != "</id>") {
			if (xmldata[i] == "<id>") {
				i++;
				id = xmldata[i];
			}
			i++;
		}
		while (xmldata[i] != "<followers>") {
			if (xmldata[i] == "<name>") {
				i++;
				name = xmldata[i];
			}
			i++;
		}
		adjList.push_back(set_Node(name,id));
		temp = adjList[num_of_users];
		//num_of_users++;
		//GraphNode newGraphNode(id, name);
		while (xmldata[i] != "</user>") {
			if (xmldata[i] == "<id>") {
				i++;
				id = xmldata[i];
                temp->next = add_following(id);
                temp = temp->next;
                num_followers++;
				adjList[num_of_users]->outEdges++;
				int ID = stoi(id);
				followers[ID]++;
				//newGraphNode.addFollower(id);
			}
			i++;
		}
		//vecOfGraphNodes.push_back(newGraphNode);
		num_of_users++;
		i++;
	}
	return adjList;
}

vector<string> common_users(string user1 , string user2){
	vector<string> followers1;
	vector<string> followers2;
	vector<string> common;
	int index1 , index2;
	for(unsigned int i = 0 ; i < adjList.size() ; i++){
        // here we get the index of each user in the adjacency lst
		if(adjList[i]->name == user1) index1 = i;
		if(adjList[i]->name == user2) index2 = i;
	}
/*
then we will create a temporary pointer to each user and then loop on the followers and push them inside vector for the followers of user 1 and same for
user 2
*/
	GraphNode* temp = adjList[index1];
	int i = 0;
	while(temp!= NULL){
		if(i == 0){
			temp = temp->next;
			i++;
		}
		else{
			followers1.push_back(temp->id);
			temp = temp->next;
		}
	}
	temp = adjList[index2];
	i = 0;
	while(temp!= NULL){
		if(i == 0){
			temp = temp->next;
			i++;
		}
		else{
			followers2.push_back(temp->id);
			temp = temp->next;
		}
	}
	// here we will compare the followers of user 1 and user 2 and push the common inside common vector and then we will return this vector
	for(unsigned int i = 0 ; i < followers1.size() ; i++){
		for(unsigned int j = 0 ; j < followers2.size() ; j++){
			if(followers1[i]  == followers2[j]) common.push_back(followers1[i]);
		}
	}
	vector<string> users_names = ID_to_Name(common);
	return users_names;
}

bool is_follower(int id1 , int id2){
    // function to check if the 2 users follow each other or not
    bool flag = false;
    GraphNode* temp;
    temp = adjList[id1-1]->next;
    while(temp != NULL){
          if(id2 == stoi(temp->id)){
            flag = true;
            break;
        }
        else temp = temp->next;
    }
    if(flag == true) return true;
    else return false;
}

vector<string> suggest(string username){
    vector<string> followers1;
	vector<string> suggested;
	int index1;
	for(unsigned int i = 0 ; i < adjList.size() ; i++){
		if(adjList[i]->name == username) {
		    index1 = i;
             break;
		}

	}
	GraphNode* temp = adjList[index1];
	int i = 0;
	while(temp!= NULL){
		if(i == 0){
			temp = temp->next;
			i++;
		}
		else{
			followers1.push_back(temp->id);
			temp = temp->next;
		}

	}
	int ID;
	vector<string> followers_of_followers;
	for(unsigned int j = 0 ; j < followers1.size() ; j++){
		ID = stoi(followers1[j]);
		temp = adjList[ID-1];
		i = 0;
		while(temp!= NULL){
			if(i == 0){
				temp = temp->next;
				i++;
			}
			else{
				followers_of_followers.push_back(temp->id);
				temp = temp->next;
			}
		}

	}
	bool found;
	int index2;
	for(unsigned int j = 0 ; j < followers_of_followers.size() ; j++){
		found = false;
		for(unsigned int k = 0 ; k < followers1.size() ; k++){
			if(followers1[k] == followers_of_followers[j]){
				found = true;
				break;
			}
			else index2 = j;

		}
		if(found == false )
			suggested.push_back(followers_of_followers[index2]);
		}
    vector<string> suggested_modified ;
	for(unsigned int k = 0; k < suggested.size() ;k++){
        if(suggested[k] != adjList[index1]->id)
            suggested_modified.push_back(suggested[k]);
	}
	vector<string> users_names = ID_to_Name(suggested_modified);
	return users_names;

}
