/*************************************************************************************
* File Name: xmltojson.cpp
*
* Description: Source file that contain that contain the functions definitions
*              of the functions to convert from XML to JSON format
*
* Author: Andrew Hany
**************************************************************************************/

#include "..\treeStructure\Node.h"
#include "..\treeStructure\xmlTree.h"
#include "..\XML_parsing\XML_parsing.h"
#include "xmltojson.h"
#include <stdlib.h>

string JSON_file = "" ;
//private global tree that can be used only by this file functions
static xmlTree g_tree  ;
//private stack to save the closing of each bracket to make sure that each open bracket is closed
static stack<char>closingBracketsStack ;
//variable that counts the number of tabs needed in ever new line
static int numberOfTabs = 0 ;
//private vector that holds in it the name tags of the arrays in the tree
static vector<string> arrayInTree ;
//private flag to detect if the type of the array is written or not
bool g_childFlag = false ;

/*************************************************************************************
 *                              Functions definitions                                *
 *************************************************************************************/

/*
 * Function that return true if the current node is array ot not
 */
bool is_Array(Node * current)
{
    if(!arrayInTree.empty())
    {
        for(auto &arr_name :arrayInTree)
        {
            if(arr_name == current->getTagName())
                return true ;
        }
        return false ;
    }
    return false ;
}

/*
 * Function that is responsible for the indentation in each new line
 */
void printTabs(int nOfTabs)
{
    for(int i = 0 ; i<nOfTabs ; i++)
    {
        JSON_file += "    " ;
    }
}

/*
 * A function that takes the file path from the user and then parse the data in the file to save
 * the data of the file in a tree
 */
void xmlToTree(std::string xmlFile)
{
    XML_parsing(g_tree ,xmlFile) ;
}

/*
 * A function that check if the current node is leaf or not
 */
bool is_leaf(Node * current)
{
    if(current->getChildren().empty())
        return true ;

    return false ;
}

/*
 * Function that convert the passed XML file path to JSON file
 */
string xmlToJson(string xmlFile)
{
    Node * current = NULL ;

    //save the xml file to a tree
    xmlToTree(xmlFile) ;

    current = g_tree.getRoot() ;

    arraysInTree(current) ;

    if(!g_tree.empty())
    {
        //open the JSON block
    	JSON_file += "{\n" ;

        //push the closing of this bracket in the stack
        closingBracketsStack.push('}') ;

        //increment the number of tabs for a good indentation of the file
        numberOfTabs++ ;

        current = g_tree.getRoot() ;
        printFile(current) ;

        /*
         * now check if there is remaining brackets  in the stack not popped
         */
        while( !closingBracketsStack.empty())
        {
            numberOfTabs-- ;
            JSON_file += "\n" ;
            printTabs(numberOfTabs) ;
            JSON_file += closingBracketsStack.top()  ;
            closingBracketsStack.pop() ;
        }
    }
    else
    {
    	JSON_file += "File is empty!" ;
    }
    return JSON_file ;
}

/*
 * A function that takes the root of a graph then re-turn a vector has the tag name of the
 * arrays included in this tree
 */
void arraysInTree(Node *root)
{
    bool flag = false ;

    /************ Base case of the function *************/
    if(is_leaf(root) )
    {
        return;
    }

    if(root->getChildren().size() > 1)
    {
        if(root->getChildren()[0]->getTagName() == root->getChildren()[1]->getTagName())
        {
            /*
             * in this case the current node is array.
             * First check for the name tag if saved in the array or not if not fount then add it to the array
             * if found discard it
             */
            for(auto &arr_name : arrayInTree)
            {
                if(root->getTagName() == arr_name)
                {
                    flag = true ;
                    break ;
                }
            }
            //the tag name is not found in the tree---->add it
            if(false == flag)
            {
                arrayInTree.push_back(root->getTagName()) ;
            }
        }
    }
    for(unsigned int i= 0 ; i < root->getChildren().size() ; i++)
    {
        /********** The recursive call **********/
        arraysInTree(root->getChildren()[i]) ;
    }
    return ;
}
/*
 * a function to print the tag name of the array nodes
 */
void printArraysName(string xmlFilePath)
{
    Node *current ;
    xmlToTree(xmlFilePath) ;
    current = g_tree.getRoot() ;

    arraysInTree(current) ;

    for(auto &arr_name : arrayInTree)
    {
        cout<<arr_name<<endl ;
    }
    cout<<arrayInTree.size() ;
}

/*
 * The function that is responsible for the style of printing the data to same as the JSON format
 */
void printFile(Node *root)
{
    bool extraPopFlag = false ;

    printTabs(numberOfTabs) ;

    /******* this conditions is responsible for writing the tag name ******/
    /*
     * the case the current node is the root of the tree then write its tag name normaly
     */
    if(root == g_tree.getRoot())
    {
    	JSON_file += '"' + root->getTagName() + "\": " ;
    }
    /*
     * if the current node is children to an array then prints then only write its tag name once in each
     */
    else if(is_Array(root->getParent()) )
    {
        if(!g_childFlag)
        {
        	JSON_file += '"' + root->getTagName() + "\": " ;

            if(root->getParent()->getChildrenNumber() >1)
            {
            	JSON_file += "[\n" ;
                closingBracketsStack.push(']') ;
                numberOfTabs++ ;
                printTabs(numberOfTabs) ;
            }

            g_childFlag = true ;
        }
    }
    else if(!is_Array(root->getParent()) && !is_Array(root))
    {
    	JSON_file += '"' + root->getTagName() + "\": " ;

    }
    else if(!is_Array(root->getParent()) && is_Array(root))
    {
    	JSON_file += '"' + root->getTagName() + "\": " ;

        if(root->getChildren().size() >1)
            extraPopFlag = true ;
    }

    /*
     * in this case the node is parent so it carry more than one data info so we must open parenthesis
     */
    if( !is_leaf(root) )
    {
    	JSON_file += "{\n" ;
        closingBracketsStack.push('}') ;
        numberOfTabs++ ;
    }

    /********* Base Case ************/
    if(is_leaf(root))
    {
        if(root->getDataInt() == 0)
        {
            //current node data is string
        	JSON_file = JSON_file + "\"" + root->getDataString() + "\"";
        }
        else
        {
        	//current node data is int
        	JSON_file = JSON_file + "\"" + std::to_string( root->getDataInt()) + "\"";
        }
        return ;
    }
    else
    {
        for(unsigned int i = 0 ; i < root->getChildren().size() ; i++)
        {
            /*
             * start of new sub-tree so set the flag to false to write the tag name of the children
             * at least once
             */
            if(i== 0)
            {
                g_childFlag = false ;
            }

            /********* the recursive call **********/
            printFile(root->getChildren()[i]) ;

            if(i == root->getChildren().size() -1)
            {
                /*
                 * when reaching here it is the end of the sub-tree so we will go back to the parent of this sub-tree
                 * then set the flag to true again
                 */
                g_childFlag = true ;

            	JSON_file += "\n" ;
            }
            else {
            	/*
				 * if the current node is not the last node to its parent then we need to write comma
				 * to differ between it and the next data
				 */
            	JSON_file += ",\n" ;
            }
        }
        /*
         * this is the case of pushing an extra parenthesis to the stack so we will need to pop it from the stack
         * the extra pop flag is true only when the current root is array of size > 1
         */
        if( extraPopFlag )
        {
            numberOfTabs -- ;
            printTabs(numberOfTabs) ;
            JSON_file = JSON_file + closingBracketsStack.top() + "\n" ;

            closingBracketsStack.pop() ;
            extraPopFlag = false ;
        }
        /*
         * when reaching out of the loop this mean the end of the current subtree so pop from the stack the last
         * pushed parenthesis to the stack (parenthesis which is pushed when getting into the subtree)
         */
        numberOfTabs -- ;
        printTabs(numberOfTabs) ;
        JSON_file += closingBracketsStack.top() ;
        closingBracketsStack.pop() ;
    }
}
