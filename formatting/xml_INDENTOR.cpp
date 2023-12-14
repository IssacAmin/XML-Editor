#include "xml_INDENTOR.h"
void xmlindentor(fstream& myfile ){
		string edited_line;
		vector<string> lines;
		int indent = 0;
		vector<string> elements = oneElementPerLine(myfile);
		for(string element:elements){

			if (element.substr(0, 2) == "</") {
            	--indent;
    		}
    		edited_line= string(indent*4,' ') + element;
    		if (element.substr(0, 1) == "<" && element.substr(1, 1) != "/" ) {
    			string str ="/";
    			size_t found = element.find(str);
    			if(found!= string::npos){
                    indent = indent;
				}
				else{
					++indent;
				}
        }
        	lines.push_back(edited_line);
		}
        for(int i=0;i<(int) lines.size();i++){
				cout<<lines[i]<<endl;
			}
}




