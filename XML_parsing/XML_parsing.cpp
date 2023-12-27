
#include "XML_parsing.h"

<<<<<<< HEAD
void XML_parsing(xmlTree& tree, string& file){
=======
void XML_parsing(xmlTree& tree, string& file) {
>>>>>>> f99338b8163698451fcba93aabde489ec93f2344
	string line;
	vector<string> elements = oneElementPerLine(file);
	for (string element : elements) {
		textType type = detectType(element);  //Check the type of element in line
		tagToNode(element, type, tree);		// Convert the tag in line to a node in the tree
	}
}

textType detectType(string element){
	if(element[0] == '<' && element[1] == '/')
		return CLOSING_TAG;
	else if(element[0] == '<' && element[1] != '/')
		return OPENING_TAG;
	else{
		return DATA;
	}
}
void tagToNode(string& element, textType type, xmlTree& tree){
	if(type == OPENING_TAG)
	{
		string tagName = element.substr(1,element.find(">") - 1);
		if(tree.empty()){							//If tree is empty
			Node* root = new Node(0,tree.currentLevel,tagName);
			tree.setRoot(root);
			tree.currentNode = tree.getRoot();
		}
		else{
			Node* tmp = new Node(0,tree.currentLevel, tagName);
			tree.currentNode->add(tmp);
			tree.currentNode = tmp;
		}
		tree.currentLevel++;

	}
	else if(type == DATA){
		bool digit = true;
		for(unsigned int i = 0; i < element.length(); i++){
			if(!isdigit(element[i])){
				digit = false;
				break;
			}

		}
		if(digit){
			tree.currentNode->setDataInt(stoi(element));
		}
		else{
			tree.currentNode->setDataString(element);
		}
	}
	else{  //If it is a closing tag
		if(tree.currentNode->getParent() != NULL)
		{
			tree.currentNode = tree.currentNode->getParent();
			tree.currentLevel --;
		}

	}

}



