//
// Created by Grace on 2018/4/28.
//

#ifndef TEST_PARSE_H
#define TEST_PARSE_H

#include "extraction.h"

vector<int> JudgeTag(int *contentStartLength, int *contentEndLength, vector<int> &is_tag, int length,
                     string target, vector<int> &contentStart, vector<int> &contentEnd, ofstream &logfile);
//vector<int> JudgeTag(vector<int> is_tag, int length , string target,    vector<int> contentStart, vector<int> contentEnd );
vector<int> GetCandidates(vector<int> &candidate, vector<int> &is_tag, int length, int D, float a, ofstream &logfile);
int GetProbableBoarder(int *start, int *end, int length, vector<int> candidate, int D,ofstream &logfile);

#endif //TEST_PARSE_H
