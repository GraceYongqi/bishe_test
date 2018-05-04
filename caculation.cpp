//
// Created by Grace on 2018/4/28.
//

#include "caculation.h"

int CaculateDensity(int *xres, int *yres, int approxStart, int approxEnd,
                    vector<int> is_tag, vector<int> contentStart, vector<int> contentEnd, int contentStartLength, int contentEndLength, int length){
	assert(!is_tag.empty());
	assert(!contentStart.empty());
	assert(!contentEnd.empty());
    int x, y;
    int M = (approxStart+approxEnd)/2;
    int density;
    for(x=((*contentStart.begin())>0?(*contentStart.begin()):0);x<=(contentStart.at(contentStartLength-1)<M?M:contentStart.at(contentStartLength-1));x++){
//cout << "for " << endl;
        int max = 0;
        density = CaculateVector(is_tag,0,x-1)+M-x+1-CaculateVector(is_tag,x,M);
        if(density > max){
            *xres = x;
        }
    }
cout << "for x " << endl;
//cout << *contentEnd.begin() << " : " << *contentEnd.end() << endl;
//cout << "M:" <<  is_tag[45300] << endl;
//cout << "ystart: " << is_tag[45299] << endl;
//cout << "ystart2: " << is_tag[45300] << endl;
//cout << "yend: " << is_tag[49935] << endl;
//cout << "yend1: " << is_tag[49936] << endl;
//cout << "length: " << is_tag[49947] << "," << is_tag[length-1] << endl;
cout << "M:"<<M<<endl;
cout <<"end.begin()"<<*contentEnd.begin() << endl;
cout << "contenEndLength " << contentEndLength << endl;
cout << "end.end()" << contentEnd.at(contentEndLength-2) << endl;
	int ystart = 0;
	int yend = 0;
	if(*contentEnd.begin()>M) ystart = *contentEnd.begin(); 
	else ystart = M;
	if(contentEnd.at(contentEndLength-1)<length-1) yend=contentEnd.at(contentEndLength-1);
	else yend = length-1;
	cout << "y : "<< ystart << "-> "<< yend << endl;
	for(y=ystart;y<=yend;y++){
//    for(y= ((*contentEnd.begin())>M?(*contentEnd.begin()):M);y<=(contentEnd.at(contentEndLength-1)<(length-1))?contentEnd.at(contentEndLength-1):(length-1);y++){
        int max = 0;
cout << "for y start" << endl;
cout << "y" << y << endl;
	int c1 = CaculateVector(is_tag,M,y);
	cout << "c1 end " << endl;
	int c2 = CaculateVector(is_tag,y,length);
	cout << "c2 end " << endl;
	density = y-M+1-c1+c2;
	cout << "density end " << endl;
//        density = y-M+1-CaculateVector(is_tag,M,y)+CaculateVector(is_tag,y,length);
//cout << " caculate end " << endl;
        if(max < density){
            *yres = y;
        }
    }
cout << "for y " << endl;
    return 0;
}

int CaculateVector(vector<int> v, int start, int end){
	assert(!v.empty());
    int res = 0;
	int i = 0;
    for(i=start; i<end; i++){
//cout << v.at(i) << endl;
//cout << i << endl;
        res += v.at(i);
    }
cout << "end i : " << i << endl;
    return res;
}
