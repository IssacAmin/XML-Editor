#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<string> oneElementPerLine(string& xml_content);
bool isData(char x);
string eraseSpaces(string& str);
bool isLeaf(string line, int start);


#endif
