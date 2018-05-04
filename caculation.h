//
// Created by Grace on 2018/4/28.
//

#ifndef TEST_CACULATION_H
#define TEST_CACULATION_H

#include "extraction.h"

int CaculateDensity(int *xres, int *yres, int approxStart, int approxEnd,
                    vector<int> is_tag, vector<int> contentStart, vector<int> contentEnd, int contentStartLength, int contentEndLength, int length);
//int CaculateDensity(int *xres, int *yres, int approxStart, int approxEnd,
//                    vector<int> is_tag, vector<int> contentStart, vector<int> contentEnd, int length);
int CaculateVector(vector<int> v, int start, int end);

#endif //TEST_CACULATION_H
