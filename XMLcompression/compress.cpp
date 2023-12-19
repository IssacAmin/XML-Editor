/**********************************************************************************************************************************************************
major steps of huffman compression technique:
 *First: we will create node for each character found in the file, then we will create a hash map
 *for frequencies of those characters to determine which character has the most frequency
 *and the character with the highest frequency will have the lowest priority  and then we will form
 *a minimum priority queue and the 2 nodes which have the highest priority we will pop them
 *and create a new node and its character will be Null (it does not matter) and we will assign
 *to the frequency field inside the node the sum of their frequencies and we will loop until the
 *queue contains one node which contains all the elements and here the tree will be formed and
 *the code of each character will be determined by its path from root and to form the code
 *each character on the left will be '0' and each character on the right will be '1' and the code
 *of the character will be determined by the path until we reach this character.
 **********************************************************************************************************************************************************/
#include"compress.h"
using namespace std;
priority_queue <Tree*,vector<Tree*>,compare> heap;
string strBuffer;
vector<char> data; // creating vector of characters to store all the characters inside the file
Tree* root; // root of huffman tree which contains the data and their frequencies
// unordered map for storing the codes of each character inside the map
unordered_map <char,string> huffman_code ;
Tree* set_Node(){
	Tree* root = new Tree();
	root->frequency = 0;
	root->data = 0;
	root->left = root->right = NULL;
	return root;
}
Tree* set_Node(char data, int frequency){
	Tree* root = new Tree();
	root->data = data;
	root->frequency = frequency;
	root->left = root->right = NULL;
	return root;
}
Tree* set_Node(char data , int frequency , Tree_Node* left, Tree_Node* right){
	Tree* root = new Tree();
	root->data = data;
	root->frequency = frequency;
	root->left = left;
	root->right = right;
	return root;
}

void form_huffmancode(string encoded_data, Tree* root, unordered_map<char,string> &code){
	if(root == NULL) return; // tree is empty

	if((root->left == NULL) && (root->right == NULL))

		code[root->data] = encoded_data;
	/* 2 recursive calls to give the left character 0 and right character 1 according to the
	 *algorithm and the code of the character is the sequence of zeroes and ones until we reach
	 *this character in the tree
	 */
	form_huffmancode(encoded_data + '0' , root->left , code);

	form_huffmancode(encoded_data + '1' , root->right , code);
}
void form_priorityQueue(){
	// creating an unordered hash map to store frequencies of characters inside the file.
	unordered_map<char,int> char_frequency;

	for(char c : data ) {
		// calculating the frequency of each character inside the file and storing it in the map
		char_frequency[c]++;
	}
	for(auto hashmap_data : char_frequency){
		/* we used auto because we want to take the data inside the unordered map and this map
		 *contains 2 data types,so the data type of the variable will be determined according
		 *to the data from the hash map
		 */
		//storing leaf node for each character inside the priority queue
		heap.push(set_Node(hashmap_data.first,hashmap_data.second)) ;

	}
}

void compress(string File_data , string fileName){

	string encoded_data = ""; // empty string to store the encoded data for each character

	form_priorityQueue(); // here we create the priority queue
	// we will loop until the queue contains one element which is the tree that contains
	//all the nodes
	while(heap.size() != 1){

		Tree* left = heap.top(); // get the first node which has the highest priority

		heap.pop(); // removing it from the queue

		Tree* right = heap.top(); // get the second node

		heap.pop(); //  removing it from the queue

		/*sum the frequencies of the 2 nodes which will be the frequency of the
		 *combination of the 2 nodes
		 */

		int freq_sum = left->frequency + right->frequency;

		/*here we form a node which contains 2 nodes with the highest priority
		 * and the summation of their frequencies
		 */
		heap.push(set_Node( '\0', freq_sum, left, right));

	}

	root = new Tree();

	root = heap.top(); // root pointer to the whole tree

	// calling function to form the code of each character
	form_huffmancode(encoded_data, root , huffman_code);
	// empty string to store the encoded data inside it and write inside the file
	string compressed_data = "";

	for(char c : data)
		// getting code of each character from the map and st
		compressed_data += huffman_code[c];

	ofstream file1;
	strBuffer = compressed_data ;
	file1.open("compression.bin", ios::binary);

	if (file1.is_open()) {

		int remainingBits = compressed_data.length() % 8;//get the remaining number of bits

		unsigned int i = 0;
		for (; i < compressed_data.length() - remainingBits; i += 8) {
			//we will loop on the complete number of bits and write it inside the file
			string byte = compressed_data.substr(i, 8);

			char byteValue = static_cast<char>(bitset<8>(byte).to_ulong());

			file1.write(&byteValue, 1);
		}

		// check if there are any remaining bits inside the compressed string
		if (remainingBits > 0) {
			// we will create a string called last byte which contain the remaining number of bits
			//and pad the remaining bits with zero
			string lastByte = compressed_data.substr(i, remainingBits);

			while (lastByte.length() < 8) {
				lastByte += '0'; // padding the remaining bits with zero
			}
			char lastByteValue = static_cast<char>(bitset<8>(lastByte).to_ulong());

			file1.write(&lastByteValue, 1); // writing the last byte in the file
		}
		file1.close();
	}

}
/*
string decode(Tree* root , int& index ,string file_data){
    string decompressed_output = "";

    if(root == NULL) return decompressed_output;

    if((root->left == NULL) && (root->right == NULL)){
    // when we reach the leaf this means that the data is ready and we will get character from this node
        decompressed_output = root->data;
        return decompressed_output;
    }
    index++;
    if(file_data[index] == '0'){
    // if encoded data contains 0 we will make recursive call to left of tree
        decompressed_output += decode(root->left, index, file_data);
    }
    else{
    // if encoded data contains 1 we will make recursive call to the right of the tree
        decompressed_output += decode(root->right, index, file_data);
    }
}

void file_decompress(){
    ofstream output_file("Decompressed.txt");
    int index = -1;
    string decompressed_output = "";
    while(index < (int)strBuffer.size()-2){
        decompressed_output += decode(root , index , strBuffer);
    }
    for(int i = 0 ; i < decompressed_output.size(); i++){
         output_file << decompressed_output[i];
    }
     output_file.close();
}
*/
