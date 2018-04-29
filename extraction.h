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
#include <boost/algorithm/string.hpp>


//#define  EXIT_SUCCESS 0 ;

using namespace std;

char * FindTagByPattern(char *raw, char *pattern);
char * StringCut(const char * raw , char * start, char * end);
//vector<char *> FindMultiByPattern(char * raw , char * pattern);
//char * FindSingleByPattern(char * raw , char * pattern);
//char * DeleteByReg(char * raw , char * pattern);
//char * DeleteByReg(char * raw , char * pattern);

vector<char *> StringSplit(char * raw , char * delim);
//int PrintVector(vector<char *> v , ofstream &resfile);

vector<string>FindMultiByPattern(string raw ,  string pattern );
string FindSingleByPattern(string raw , string pattern);
string DeleteByReg(string raw , string pattern);
int PrintVector(vector<string> v , ofstream &resfile);
string ReplaceSpace(string raw);


#endif //BISHE_TEST_EXTRACTION_H

