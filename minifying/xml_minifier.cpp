#include "xml_minifier.h"
void xmlminifier(fstream& myfile){
		string line;
		string oneLineFile = "";
			vector<string> elements = oneElementPerLine(myfile);
			for(string element : elements){

			element.erase(remove(element.begin(), element.end(), '\t'),element.end());
			element.erase(remove(element.begin(), element.end(), '\f'),element.end());
			element.erase(remove(element.begin(), element.end(), '\n'),element.end());
			element.erase(remove(element.begin(), element.end(), '\v'),element.end());
			oneLineFile += element;
}
			cout<<oneLineFile<<endl;
}



