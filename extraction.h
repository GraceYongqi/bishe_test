//
// Created by Grace on 2018/4/24.
//

#ifndef BISHE_TEST_EXTRACTION_H
#define BISHE_TEST_EXTRACTION_H

//#include <Parser.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <regex.h>
#include <assert.h>
#include <boost/regex.hpp>

//#define  EXIT_SUCCESS 0 ;

using namespace std;

char * FindTagByReg(char *raw, char *pattern);
vector<char *> FindMultiTagByReg(char * raw , char * pattern);
char * DeleteByReg(char * raw , char * pattern);

char * StringCut(const char * raw , char * start, char * end);
vector<char *> StringSplit(char * raw , char * delim);
int PrintVector(vector<char *> v , ofstream &resfile);

#endif //BISHE_TEST_EXTRACTION_H

