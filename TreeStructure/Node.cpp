/*
 * Node.cpp
 *
 *  
 *      Author: Poula
 */

#include "Node.h"

Node::Node() {
	dataInt = 0;
	dataString = "";
	level = 0;
	tagName = "";
	parent = NULL;
}
Node::Node(int data, int Level, string tag){
	dataString = "";
	dataInt = data;
	level = Level;
	tagName = tag;
	parent = NULL;


}

Node::Node(string data, int Level, string tag){
	dataInt = 0;
	dataString = data;
	level = Level;
	tagName = tag;
	parent = NULL;
}
Node::~Node() {
}

void Node::add(Node* n) {
	Node* current = this;
	n->setParent(current);
	children.push_back(n);}
Node* Node::getNode(int i) {return children[i];}
int Node::getChildrenNumber() {return children.size();}


vector<Node*>& Node::getChildren() {
	return children;
}

void  Node::setChildren( vector<Node*>& children) {
	this->children = children;
}

int  Node::getDataInt()  {
	return dataInt;
}

void  Node::setDataInt(int data) {
	dataInt = data;
}

 string&  Node::getDataString()  {
	return dataString;
}

void  Node::setDataString( string& data) {
	 dataString = data;
}

int  Node::getLevel()  {
	return level;
}

void Node::setLevel(int level) {
	this->level = level;
}

 Node*& Node::getParent() {
	return parent;
}

void Node::setParent( Node*& parent) {
	this->parent = parent;
}

string& Node::getTagName() {
	return tagName;
}

void Node::setTagName( string& tag) {
	tagName = tag;
}

void Node::printNode(){

		cout << "Tag name: " << tagName << ", ";
		cout << "Data: ";
		if(dataString.compare("") == 0 ){
			cout << dataInt << ", ";
		}
		else
			cout << dataString << ", ";
		cout << "Level: " << level << ", ";
		if(parent != NULL)
			cout << "Parent: " << parent->tagName << endl << endl;
	}

