//
// Created by Grace on 2018/5/6.
//

#include "noise_remove.h"


string noise_remove(string contents, ofstream &resfile, ofstream &logfile){
    const char * doc = contents.data();

//    step 1 extract content between <head> & </head>
//    char * headres;
    string headres;
    string HeadTag = FindSingleByPattern(contents,"<head.*?>", logfile);
//    headres = StringCut(doc , "<head>" , "</head>");
//    headres = StringCut(doc , HeadTag.data() , "</head>");
    headres = CutByFind(contents, HeadTag, "</head>", logfile);
//    resfile << "title" << '\t' << StringCut((const char * )headres ,"<title>" , "</title>") << endl;
    resfile << "title" << '\t' << CutByFind(headres, "<title>", "</title>", logfile) << endl;

//    char * keywordres1= StringCut((const char * )headres,"<meta name=\"keywords\" content=\"" , "\" />");
    string keywordres = CutByFind(headres, "<meta name=\"keywords\" content=\"" , "\"", logfile);
    resfile << "keywords" << '\t' ;
//    string keywordres(keywordres1);
    vector<string> keywordvec ;
    boost::split(keywordvec,keywordres,boost::is_any_of(",_"));
    PrintVector(keywordvec , resfile, logfile) ;
    resfile << endl ;
//    resfile << "description" << '\t' << StringCut((const char * )headres , "<meta name=\"description\" content=\"" , "\" />") << endl;
    resfile << "description" << '\t' << CutByFind(headres , "<meta name=\"description\" content=\"" , "\"", logfile) << endl;

//    resfile << "author" << '\t' << StringCut((const char * )headres , "<meta name=\"author\" content=\"" , "\" />") << endl;
    resfile << "author" << '\t' << CutByFind(headres , "<meta name=\"author\" content=\"" , "\"", logfile) << endl;

//    step 2 extract content between <body XXXXX> & </body>   --> target text
//    maybe you can try moving the file pointer after </head>   ------- to be optimized
//    char * pattern = "<body.*>\n" ;
//    char * doc_for_body = (char *)doc ;                              //    ------ to be optimized
//    char * BodyTag = FindTagByReg(doc_for_body , pattern);
    string BodyTag = FindSingleByPattern(contents , "<body.*?>", logfile);
//    logfile << "match tag " << BodyTag << endl;
//    char * bodyres = StringCut(doc , BodyTag , "</body>") ;
//    char * bodyres = StringCut(doc , BodyTag.data() , "</body>") ;
    string bodycontent = CutByFind(contents, BodyTag, "</body>", logfile);
    assert(bodycontent!=NULL);
    //backup
//    string bodycontent(bodyres);



//    resfile << "body" << '\t' << bodyres << endl;

    /*

//    class Extractor
//    目前只有.NET支持不确定长度的逆序环视，所以 <?<=body.*>)不能使用
//    三种方法，1.用不确定长度的正则表达式做两次分割；
//    2.不确定长度的正则表达式做一次分割+一次匹配；
//    3.用不确定长度的起始正则表达式先匹配到确定的标签字符串，用确定的字符串+结束标签做逆序+顺序环视匹配中间内容。 in use
//
//    step 1 extract content between <head> and </head>

//    char * headres = FindSingleByPattern((char *)doc , "(?<=<head>).*?(?=</head>)");
    string HeadTag = FindSingleByPattern(contents,"<head.*?>", logfile);
    string headres = FindSingleByPattern(contents , "(?<="+HeadTag+").*?(?=</head>)", logfile);
    resfile << "title" << '\t' << FindSingleByPattern(headres ,"(?<=<title>).*?(?=</title>)", logfile) << endl;
//    char * keywordres= FindSingleByPattern(headres,"(?<=<meta name=\"keywords\" content=\").*?(?=\" />)");
    string keywordres = FindSingleByPattern(headres , "(?<=<meta name=\"keywords\" content=\").*?(?=\")", logfile);
    resfile << "keywords" << '\t' ;
    vector<string> keywordvec ;
    boost::split(keywordvec,keywordres,boost::is_any_of(",_"));
    PrintVector(keywordvec , resfile, logfile) ;
    resfile << endl ;
    resfile << "description" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"description\" content=\").*?(?=\")", logfile) << endl;
    resfile << "author" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"author\" content=\").*?(?=\")", logfile) << endl;


//    step 2 extract content between <body.*?> and </body>
//    maybe you can try moving the file pointer after </head>   ------- to be optimized

//    char * BodyTag = FindSingleByPattern((char *)doc , "<body.*?>") ;

    string bodyres = substr(contents, strstr(contents, "<body"));
    logfile << "body" << '\t' << bodyres << endl;
    string BodyTag = FindSingleByPattern(contents , "<body.*?>", logfile);
//    logfile << "match tag " << BodyTag << endl;
//    char * bodyres = FindSingleByPattern((char *)doc,"(?<="BodyTag").*?(?=</body>)");
    string bodyres = FindSingleByPattern(contents , "(?<="+BodyTag+").*?(?=</body>)", logfile);
*/





//    step 3 delete unneccessary tags and get target text
//    maybe you should save all unneccessary tags into a vector , delete them by traversing the vector ---- to be optimized
//    three kinds of tags : comments tag ; special character ; html content tag
//    char * commentres = DeleteByReg(bodyres,"<!--.*?-->|\/\*.*?\*\/");
//    string commentres = DeleteByReg(bodyres , "<!.*?-->|/\\*.*?\\*/", logfile);
    string commentres1 = DeleteByFind(bodycontent, "/*","*/", logfile);
    string commentres = DeleteByFind(commentres1, "<!", "-->", logfile);


//    char * contentres = DeleteByReg(commentres , "<script.*?</script>|<div.*?</div>");
//    string contentres = DeleteByReg(commentres , "<script.*?>.*?</script>|<style.*?>.*?</style>", logfile);
    string contentres1 = DeleteByFind(commentres, "<script", "</script>", logfile);
    string contentres = DeleteByFind(contentres1, "<style", "</style>", logfile);
    resfile << "body after dele <!&/**/&<script>&<style> " << endl ;
//    resfile << contentres << endl;
//    string areares = DeleteByReg(contentres , "<div.*?>|<font.*?>|<p.*?>", logfile);
//    顺序待调整
    string areares1 = DeleteByFind(contentres, "<div", ">", logfile);
    string areares2 = DeleteByFind(areares1, "<font", ">", logfile);
    string areares = DeleteByFind(areares2, "<p", ">", logfile);
    resfile << "body after dele <div&<font&<p" << endl;
//    resfile << areares << endl;
//    char * characterres ;
//    string characterres = DeleteByReg(areares , "&nbsp|&amp", logfile);
    string characterres1 = DeleteSingle(areares, "&nbsp", logfile);
    string characterres2 = DeleteSingle(characterres1, "&amp", logfile);

    resfile << "body after dele special character" << endl;
//    resfile << characterres << endl;

//    class Parser
//    step 4 distinguish tag and text character  symbol is is_tag =0/1

//    step 5 get the candidate content by comparing with the threshold
    string target = characterres ;
//    target = ReplaceSpace(target, logfile);
    string target1 = DeleteExtraSymbols(target, ' ', logfile);
    target = DeleteExtraSymbols(target1, '\n', logfile);

    int length = target.size() ;
    int exact_x=0, exact_y=0;
    int arealength =100, factor =0.7;                    //arealength--D usually 100 or 200; factor -- a usually 0.7 or 0.8

    vector<int> contentStart(length);
    vector<int> contentEnd(length);
    vector<int> TagFlag(length) ;
    vector<int> CandidateFlag(length) ;
/*
    contentStart.reserve(length);
    contentEnd.reserve(length);
    TagFlag.reserve(length);
    CandidateFlag.reserve(length);
*/
    int contentStartLength = 0;
    int contentEndLength = 0;
    TagFlag= JudgeTag(&contentStartLength, &contentEndLength, TagFlag, length, target, contentStart, contentEnd, logfile);
    CandidateFlag= GetCandidates(CandidateFlag, TagFlag, length, arealength, factor, logfile);
    assert(!TagFlag.empty());
    assert(!CandidateFlag.empty());
    assert(!contentStart.empty());
    assert(!contentEnd.empty());
//    step 6 get the probable boarder by searching the max successive candidates
    int probablestart=0, probableend=0;
    GetProbableBoarder(&probablestart, &probableend, length, CandidateFlag, arealength, logfile);

    logfile << probablestart << ":" << probableend << endl;
//    class Caculator
//    step 7 caculate density and get the accurate border
    CaculateDensity(&exact_x, &exact_y, probablestart, probableend, TagFlag, contentStart, contentEnd, contentStartLength, contentEndLength, length, logfile);
    logfile << "x:" << exact_x << " y:" << exact_y << endl;
    string coretarget = target.substr(exact_x, exact_y-exact_x+1);

    /*
       resfile << "target text:" << endl;
       for(int count = exact_x; count <= exact_y; count++){
           resfile << target[count] ;
       }
       resfile << endl;
   */
//    step 8 delete unneccessary tags
//    顺序待调整
//    string core1 = DeleteByReg(coretarget, "<strong.*?>|<img.*?>|<a.*?>", logfile);
    string core11 = DeleteByFind(coretarget, "<a", ">", logfile);
    string core12 = DeleteByFind(core11, "<img", ">", logfile);
    string core1  = DeleteByFind(core12, "<strong", ">", logfile);

//    string core2 = Replace(core1, "</p.*?>","\n", logfile);
    string core2 = ReplaceByFind(core1, "</p>", "\n", logfile);

//    string core3 = Replace(core2, "\t+", "\t",logfile);
    string core3 = DeleteExtraSymbols(core2, '\t', logfile);
//    string core4 = Replace(core3, "\n+", "\n", logfile);
    string core4 = DeleteExtraSymbols(core3, '\n', logfile);
//    string core = DeleteByReg(core4, "<br>", logfile);
    string core = DeleteByFind(core4, "<br", ">", logfile);
//    resfile << "final result :" << endl;
//    resfile << core << endl;

//  Release vector's memory
    vector<int>().swap(contentStart);
    vector<int>().swap(contentEnd);
    vector<int>().swap(TagFlag);
    vector<int>().swap(CandidateFlag);

    return core;
}