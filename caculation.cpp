//
// Created by Grace on 2018/4/28.
//

#include "caculation.h"

int CaculateDensity(int *xres, int *yres, int approxStart, int approxEnd,
                    vector<int> is_tag, vector<int> contentStart, vector<int> contentEnd, int contentStartLength,
                    int contentEndLength, int length, ofstream &logfile){
	assert(!is_tag.empty());
	assert(!contentStart.empty());
	assert(!contentEnd.empty());
    int x, y;
    int M = (approxStart+approxEnd)/2;
    int density;

    int xstart= 0;
    int xend = 0;
    if(*contentStart.begin()>0) xstart = *contentStart.begin();
    else xstart = 0;
    if(contentStart.at(contentStartLength-1)<M) xend = contentStart.at(contentStartLength-1);
    else xend = M;
    for(x=xstart;x<=xend;x++){
//    for(x=((*contentStart.begin())>0?(*contentStart.begin()):0);x<=(contentStart.at(contentStartLength-1)<M?M:contentStart.at(contentStartLength-1));x++){
//logfile << "for " << endl;
        int max = 0;
        density = CaculateVector(is_tag,0,x-1,logfile)+M-x+1-CaculateVector(is_tag,x,M,logfile);
        if(density > max){
            *xres = x;
        }
    }

	int ystart = 0;
	int yend = 0;
	if(*contentEnd.begin()>M) ystart = *contentEnd.begin(); 
	else ystart = M;
	if(contentEnd.at(contentEndLength-1)<length-1) yend=contentEnd.at(contentEndLength-1);
	else yend = length-1;
	for(y=ystart;y<=yend;y++){
//    for(y= ((*contentEnd.begin())>M?(*contentEnd.begin()):M);y<=(contentEnd.at(contentEndLength-1)<(length-1))?contentEnd.at(contentEndLength-1):(length-1);y++){
        int max = 0;
	    int c1 = CaculateVector(is_tag,M,y,logfile);
	    int c2 = CaculateVector(is_tag,y,length,logfile);
	    density = y-M+1-c1+c2;
//        density = y-M+1-CaculateVector(is_tag,M,y)+CaculateVector(is_tag,y,length);
//logfile << " caculate end " << endl;
        if(max < density){
            *yres = y;
        }
    }
    return 0;
}

int CaculateVector(vector<int> v, int start, int end, ofstream &logfile){
	assert(!v.empty());
    int res = 0;
	int i = 0;
    for(i=start; i<end; i++){
//logfile << v.at(i) << endl;
//logfile << i << endl;
        res += v.at(i);
    }
    return res;
}
