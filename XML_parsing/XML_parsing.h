
#ifndef XML_PARSING_H_
#define XML_PARSING_H_
#include <vector>
#include <stack>
#include <fstream>

#include "../TreeStructure/xmlTree.h"
#include "../utilities/utilities.h"

typedef enum {
	OPENING_TAG, CLOSING_TAG, DATA
} textType;


void XML_parsing(xmlTree& tree, string& file); //Function to parse the XML file into a tree

textType detectType(string element); //Detect the type of element (Opening tag, Closing tag, Data)
void tagToNode(string& element, textType type, xmlTree& tree); //Convert each tag into a node in the tree
#endif /* XML_PARSING_H_ */
