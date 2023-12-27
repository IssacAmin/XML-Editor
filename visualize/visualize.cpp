#include "visualize.h"


void createGraphVisualization(vector <GraphNode*> v)
{
	remove("Graph.dot");
	string temp(1, 34);

	string dotFile_Str = "digraph test {\nnode [shape=";
	dotFile_Str += temp + "record" + temp + "  color=" + temp + "red" \
		+ temp + "] \n\n";

	for (GraphNode* v : adjList )
	{
		dotFile_Str += v->id + "[ label = " + temp + "{Name: " + v->name + " | ID: " \
			+ v->id + "} " + temp + "]\n" + v->id + " -> {";

		GraphNode* tempNode = v->next;
		while(tempNode !=NULL)
		{
			dotFile_Str += tempNode->id;
			if (tempNode->next != NULL)
			{
				dotFile_Str += ",";
			}
			tempNode = tempNode->next;
		}
		dotFile_Str += "}\n";
	}
	dotFile_Str += "}";

	ofstream image("Graph.dot");
	image << dotFile_Str;
	image.close();

//#ifdef _WIN32
//	system("dot -Tpng -O Graph.dot");
//
//#elif _linux_
//	system("dot -Tpng -O Graph.dot");
//
//#endif
}
