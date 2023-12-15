#include "utilities.h"

bool isData(char x) {
	return ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9'));
}

string eraseSpaces(string& str) {
	// Find the first non-space character from the beginning
	size_t start = str.find_first_not_of(" \n\t");
	// If the string is all spaces, return an empty string
	if (start == string::npos) {
		return "";
	}
	// Find the last non-space character from the end
	size_t end = str.find_last_not_of(" \n\t");
	// Return the substring without leading and trailing spaces
	return str.substr(start, end - start + 1);
}


vector<string> oneElementPerLine(string& xml_content) {
    bool insideTag = false;     // Flag to track if currently inside a tag
    bool insideData = false;    // Flag to track if currently inside data
    bool outsideTag = false;    // Flag to track if currently outside a tag
    bool outsideData = false;   // Flag to track if currently outside data
    vector<string> xmlElements; // Vector to store XML elements
    string currentElement = ""; // String to store the current XML element being parsed
    string tempData = "";       // Temporary string to store data characters

    for (size_t i = 0; i < xml_content.length(); i++) {
        // Add Begin of Tag
        if (xml_content[i] == '<') {
            insideTag = true;      // Set insideTag flag to true
            outsideTag = false;    // Set outsideTag flag to false
            insideData = false;    // Set insideData flag to false
            outsideData = false;   // Set outsideData flag to false
            if (!currentElement.empty()) {
                xmlElements.push_back(eraseSpaces(currentElement)); // Add currentElement to xmlElements vector after removing spaces
                currentElement.clear();                              // Clear currentElement string
            }
        }

        // Add end of Tag
        else if (xml_content[i] == '>') {
            insideTag = false;     // Set insideTag flag to false
            outsideTag = true;     // Set outsideTag flag to true
            insideData = false;    // Set insideData flag to false
            outsideData = false;   // Set outsideData flag to false
            currentElement += xml_content[i];          // Add '>' to currentElement string
            xmlElements.push_back(currentElement);    // Add currentElement to xmlElements vector
            currentElement.clear();                    // Clear currentElement string
        }

        // Get Data characters and the middle spaces
        if (isData(xml_content[i]) && !insideTag) {
            outsideTag = false;    // Set outsideTag flag to false
            insideData = true;     // Set insideData flag to true
            outsideData = false;   // Set outsideData flag to false
            currentElement += tempData;  // Add tempData to currentElement string
            tempData.clear();            // Clear tempData string
        }

        // Add Spaces to Temporary string to check if they are mid spaces or last spaces
        if ((xml_content[i] == ' ' || xml_content[i] == '\n' || xml_content[i] == '\t') && insideData) {
            insideTag = false;     // Set insideTag flag to false
            insideData = false;    // Set insideData flag to false
            outsideData = true;    // Set outsideData flag to true
            tempData += xml_content[i]; // Add space character to tempData string
        }

        // Add Tag Names and Attributes
        if (insideTag) {
            currentElement += xml_content[i];  // Add current character to currentElement string
        }

        // Add Tag Value without begin (Spaces or \t or \n)
        if (insideData && !outsideTag) {
            currentElement += xml_content[i];  // Add current character to currentElement string
        }
    }

    return xmlElements;
}

bool isLeaf(string line, int start){
	int end = line.find(">", start + 1);
	for(int i = end; line[i] != '<'; i++){
		if(isspace(line[end + 1]) )
			continue;
		else{
			return 1;
		}


	}
	return 0;
}
