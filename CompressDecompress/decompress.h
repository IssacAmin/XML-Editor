/*
 * decompress.h
 *
 *  Created on: 19 Dec 2023
 *      Author: Joseph Sherif
 */
#include "compress.h"
#ifndef DECOMPRESS_H_
#define DECOMPRESS_H_

string decode(Tree* root , int& index ,string file_data);
void file_decompress();

#endif /* DECOMPRESS_H_ */
