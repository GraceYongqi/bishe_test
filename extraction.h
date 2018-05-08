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
#include <dirent.h>
#include <time.h>
#include <exception>



//#define  EXIT_SUCCESS 0 ;

using namespace std;

char * FindTagByPattern(char *raw, char *pattern,ofstream &logfile);
char * StringCut(const char * raw , char * start, char * end, ofstream &logfile);
//vector<char *> FindMultiByPattern(char * raw , char * pattern);
//char * FindSingleByPattern(char * raw , char * pattern);
//char * DeleteByReg(char * raw , char * pattern);
//char * DeleteByReg(char * raw , char * pattern);

vector<char *> StringSplit(char * raw , char * delim, ofstream &logfile);
//int PrintVector(vector<char *> v , ofstream &resfile);

vector<string>FindMultiByPattern(string raw ,  string pattern, ofstream &logfile );
string FindSingleByPattern(string raw , string pattern,ofstream &logfile);
string DeleteByReg(string raw , string pattern, ofstream &logfile);
int PrintVector(vector<string> v , ofstream &resfile, ofstream &logfile);
string ReplaceSpace(string raw, ofstream &logfile);
string Replace(string raw, string from, string to, ofstream &logfile);

string CutByFind(string raw, string start, string end, ofstream &logfile);
string DeleteByFind(string raw, string start, string end, ofstream &logfile);
string DeleteExtraSymbols(string raw, char symbol, ofstream &logfile);
string DeleteSingle(string raw, string single, ofstream &logfile);
string ReplaceByFind(string raw, string from, string to, ofstream &logfile);




#endif //BISHE_TEST_EXTRACTION_H

