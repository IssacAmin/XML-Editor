/*
 * compress.h
 *
 *  Created on: 19 Dec 2023
 *      Author: Joseph Sherif
 */
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<queue>
#include<bitset>
using namespace std;
#ifndef COMPRESS_H_INCLUDED
#define COMPRESS_H_INCLUDED

typedef struct Tree_Node{
	int frequency;
	char data;
	Tree_Node* left;
	Tree_Node* right;
}Tree;

struct compare{ // using custom structure to build minimum priority queue

	bool operator()(Tree_Node* left, Tree_Node* right){
		// the lowest frequency must have the highest priority in order to come out first
		return left->frequency > right->frequency;
	}
};
Tree* set_Node();
Tree* set_Node(char data, int frequency);
Tree* set_Node(char data , int frequency , Tree_Node* left, Tree_Node* right);
void form_huffmancode(string Filedata, Tree root, unordered_map<char,string> &code);
string compress(string File_data , string file_path);
void form_priorityQueue();
extern string strBuffer; // this string contains the encoded data zeroes and ones
extern vector<char> data;
extern Tree* root;
#endif // COMPRESS_H_INCLUDED

