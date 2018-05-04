//
// Created by Grace on 2018/4/28.
//

#include "caculation.h"

int CaculateDensity(int *xres, int *yres, int approxStart, int approxEnd,
                    vector<int> is_tag, vector<int> contentStart, vector<int> contentEnd, int length){
    int x, y;
    int M = (approxStart+approxEnd)/2;
    int density;
    for(x=((*contentStart.begin())>0?(*contentStart.begin()):0);x<=((*contentStart.end())<M?M:(*contentStart.end()));x++){
        int max = 0;
        density = CaculateVector(is_tag,0,x-1)+M-x+1-CaculateVector(is_tag,x,M);
        if(density > max){
            *xres = x;
        }
    }
    for(y= ((*contentEnd.begin())>M?(*contentEnd.begin()):M);y<=((*contentEnd.end())<length)?(*contentEnd.end()):length;y++){
        int max = 0;
        density = y-M+1-CaculateVector(is_tag,M,y)+CaculateVector(is_tag,y+1,length);
        if(max < density){
            *yres = y;
        }
    }
    return 0;
}

int CaculateVector(vector<int> v, int start, int end){
    int res = 0;
    for(int i=start; i<=end; i++){
        res += v.at(i);
    }
    return res;
}
