#ifndef ERROR_DETECTION_CORRECTION_H_
#define ERROR_DETECTION_CORRECTION_H_

#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

typedef enum {
	OPENING, CLOSING
} tagType;
typedef struct{
	string tag_name;
	int line;
	int pos;
	tagType type;
} tag;


string errorCorrection(vector<tag> errors,vector<string>& fileContent);
bool isOnStack(stack<tag>& st, tag current_tag);
vector<tag> ErrorDetection(string fileText, vector<string>& fileContent);
tag openTag(string& line, int lineIndex,int start);
tag closingTag(string& line, int lineIndex,int start );

#endif
