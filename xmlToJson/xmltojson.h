/*************************************************************************************
* File Name: xmltojson.h
*
* Description: header file that contain that contain the functions prototypes
*              and macros needed in the source file xmltojson.c
*
* Author: Andrew Hany
**************************************************************************************/

#ifndef XMLTOJSON_XMLTOJSON_H
#define XMLTOJSON_XMLTOJSON_H

#include <string.h>
#include "../TreeStructure/Node.h"
#include <bits/stdc++.h>

/*************************************************************************************
 *                              Functions prototypes                                 *
 *************************************************************************************/
/*
 * Function that is responsible for the indentation in each new line
 */
void printTabs(int numberOfTabs) ;
/*
 * Function that convert the passed XML file path to JSON file
 */
string xmlToJson(std::string xmlFile) ;
/*
 * A function that takes the file path from the user and then parse the data in the file to save
 * the data of the file in a tree
 */
void xmlToTree(std::string xmlFile) ;
/*
 * Function that return true if the current node is array ot not
 */
bool is_Array(Node * current) ;
/*
 * The function that is responsible for the style of printing the data to same as the JSON format
 */
void printFile(Node *root) ;
/*
 * A function that check if the current node is leaf or not
 */
bool is_leaf(Node * current) ;
/*
 * A function that takes the root of a graph then re-turn a vector has the tag name of the
 * arrays included in this tree
 */
void arraysInTree(Node *root) ;
/*
 * a function to print the tag name of the array nodes
 */
void printArraysName(string xmlFilePath) ;


#endif //XMLTOJSON_XMLTOJSON_H
