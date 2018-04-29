//
// Created by Grace on 2018/4/28.
//

#ifndef TEST_PARSE_H
#define TEST_PARSE_H

#include "extraction.h"

vector<int> JudgeTag(vector<int> is_tag, int length , string target,    vector<int> contentStart, vector<int> contentEnd );
vector<int> GetCandidates(vector<int> candidate, vector<int> is_tag, int length, int D, float a);
int GetProbableBoarder(int start, int end, int length, vector<int> candidate, int D);

#endif //TEST_PARSE_H
