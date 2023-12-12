#include "errorDetection.h"

vector<tag> ErrorDetection(string readFilePath,vector<string>& fileContent){
	stack<tag> tags;
	vector<tag> singleTags;
	string line;
	int lineIndex = 0;
	fstream file;
	file.open(readFilePath, ios::in);
	if(!file.is_open()){
		cout << "File doesn't exist";
		return singleTags;
	}
	while(getline(file,line)){
		fileContent.push_back(line);
		int tagIndex = 0;

		if(line.find("<") == string::npos){
			lineIndex++;
			continue;
		}
		//		vector<tag> tagsInLine;

		while(line.find("<",tagIndex) != string::npos)  //If more than one tag exists in one line
		{
			tagIndex = line.find("<",tagIndex);
			if(line[tagIndex + 1] != '/'){  			//If the tag is an opening tag
				tags.push(openTag(line,lineIndex,tagIndex));

			}
			else{
				tag closing = closingTag(line,lineIndex,tagIndex);
				if((!tags.empty()) && (tags.top().tag_name.compare(closing.tag_name) == 0)	){
					tags.pop();
				}
				else if(tags.empty()){					//if stack is empty then it is a single closing tag (ERROR!)
					singleTags.push_back(closing);

				}
				/*If the top of the stack is not the same tag as the one we are going to pop
				 *Then either the top of the stack misses a closing tag
				 *Or the closing tag has no opening tag
				 */
				else if(tags.top().tag_name.compare(closing.tag_name) != 0){
					if(isOnStack(tags,closing)){				//If the stack contains the pair of the current closing tag
						while(tags.top().tag_name.compare(closing.tag_name) != 0)
						{
							singleTags.push_back(tags.top());		//Then the top of the stack is the single one with no closing tag
							tags.pop();
						}
						if((!tags.empty()) && (tags.top().tag_name.compare(closing.tag_name) == 0)	){
							tags.pop();
						}

					}
					else{										//If the stack doesnt contain the pair of the closing tag
						singleTags.push_back(closing);
						//Then the current closing tag is the one with no opening tag

					}
				}
			}
			tagIndex += 1;
		}

		lineIndex++;
	}
	while(!tags.empty()){
		singleTags.push_back(tags.top());
		tags.pop();
	}
	file.close();
	return singleTags;
}



tag openTag(string& line, int lineIndex,int start){
	int end = line.find(">", start + 1);
	tag current_tag;
	current_tag.tag_name = line.substr(start + 1, end - (start + 1)); //TagName without opening and closing < >
	current_tag.line = lineIndex;
	current_tag.pos = start;
	current_tag.type = OPENING;
	return current_tag;
}
tag closingTag(string& line, int lineIndex,int start){
	int end = line.find(">", start + 1);
	tag current_tag;
	current_tag.tag_name = line.substr(start + 2, end - (start + 2)); //TagName without opening and closing < > and /
	current_tag.line = lineIndex;
	current_tag.pos = start;
	current_tag.type = CLOSING;
	return current_tag;

}

bool isOnStack(stack<tag> &st, tag current_tag){

	if(st.empty()){
		return false;
	}
	if(st.top().tag_name.compare(current_tag.tag_name) == 0){
		return true;
	}
	else
	{
		tag tmp = st.top();
		st.pop();
		bool exists = isOnStack(st, current_tag);
		st.push(tmp);
		return exists;
	}


}


