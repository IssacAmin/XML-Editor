#include"decompress.h"
using namespace std;
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
        return decompressed_output;

}

string file_decompress(){
    ofstream output_file("Decompressed.xml");
    int index = -1;
    string decompressed_output = "";
    while(index < (int)strBuffer.size()-2){
        decompressed_output += decode(root , index , strBuffer);
    }
    for(unsigned int i = 0 ; i < decompressed_output.size(); i++){
         output_file << decompressed_output[i];
    }
     output_file.close();
    return decompressed_output;
}
