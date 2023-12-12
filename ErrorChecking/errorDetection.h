#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
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


bool isOnStack(stack<tag>& st, tag current_tag);
vector<tag> ErrorDetection(string readFilePath, vector<string>& fileContent);
tag openTag(string& line, int lineIndex,int start);
tag closingTag(string& line, int lineIndex,int start );
