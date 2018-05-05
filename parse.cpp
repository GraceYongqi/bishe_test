//
// Created by Grace on 2018/4/28.
//

#include "parse.h"
#include <numeric>

vector<int> JudgeTag(int *contentStartLength, int *contentEndLength, vector<int> &is_tag, int length, string target, vector<int> &contentStart, vector<int> &contentEnd) {
    int i = 0;
    int c = 0;
//    vector<int> is_tag ;
cout << "length:" << length << endl;
    int labelStart = 0, labelEnd = 0;
    int find_tag = 0;
    while (i < length) {
        find_tag = i;
        while (target[find_tag] != '<' && find_tag < length - 1) {
            find_tag++;

        }
        labelStart = find_tag;
        if (i < labelStart) {
            if (labelStart != length - 1) {
                contentStart.at(c) = i;
//cout <<"contentStart:" << contentStart.at(c) << endl;

                contentEnd.at(c) = labelStart - 1;
//cout << "contentEnd:" << contentEnd.at(c) << endl;
                c++;
                for (int j = i; j < labelStart; j++) {
                    is_tag.at(j) = 0;
                }
            }
        } else {
            labelStart = i;
        }
//cout << "c: " << c << endl;
//cout << "contentStart:" << contentStart.at(c) << "," << contentStart.at(c) <<endl;
//cout << "contentEnd:" << contentEnd.at(c) << "," << contentEnd.at(c) << endl;
 
        find_tag = labelStart;
        while (target[find_tag] != '>' && find_tag <= length - 1) {
            find_tag++;
        }
        labelEnd = find_tag;
        if (labelStart != length - 1) {
            for (int j = labelStart; j <= labelEnd; j++) {
                is_tag.at(j) = 1;
            }
        }
        i = labelEnd + 1;

    }
//cout << contentStart[0] << ", " << contentStart[100] << endl;
	*contentStartLength = c;
	*contentEndLength = c;
    return is_tag;
}

vector<int> GetCandidates(vector<int> &candidate, vector<int> &is_tag, int length, int D, float a) {
//    vector<int> candidate;
    int k = 0;
    while (k * D < length) {
        int start, end;
        start = k * D;
        if ((k + 1) * D > length) end = length - 1;
        else end = (k + 1) * D - 1;
        int Num = end - start + 1;
        int tagNum = 0;
        for (int acc = start; acc <= end; acc++) {
            tagNum += is_tag.at(acc);
        }
        int charNum = Num - tagNum;
        if (charNum > a * D) candidate.at(k) = 1;
        else candidate.at(k) = 0;
        k++;
    }
    return candidate;
}

int GetProbableBoarder(int *start, int *end, int length, vector<int> candidate, int D) {
    int k = 0, maxLength = 0, currentLength = 0, approxStart = 0, approxEnd = 0;
    while (k * D < length) {
        if (candidate.at(k) == 1) {
            currentLength++;
            k++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
                approxEnd = k * D + 1;
                approxStart = (k - maxLength) * D;
            }
            currentLength = 0;
            k++;
        }
    }
    if (currentLength > maxLength) {
        maxLength = currentLength;
        approxEnd = length - 1;
        approxStart = (k - maxLength) * D;
    }
    *start = approxStart;
    *end = approxEnd;
    return EXIT_SUCCESS;
}

