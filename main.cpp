/*
 * todo
 *
 * body中的标签
 * 范围预估
 * test linux push
 * test linux push
 */
 //git test
/*
 *  initialize ssh pub key :https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/#platform-linux
 *   Start the ssh-agent in the background : eval "$(ssh-agent -s)"
 *   ssh git passphrase: forgit
 *   git clone git@github.com:GraceYongqi/bishe_test.git
 *
*/

#include "extraction.h"
#include "parse.h"
#include "caculation.h"

/*
 * function declaration
 * */

int main(int argc, char const *argv[])
{
//    open file for writing results
    ofstream resfile;
    resfile.open("result.txt");
    assert(resfile) ;
//    read html file
    ifstream fin;
    fin.open("3_eng.txt");
    assert(fin) ;



    const char * doc;
//    txt -> string
//    doc is const value === htmlfile
    stringstream buffer;
    buffer << fin.rdbuf();
    string contents(buffer.str());              // raw html file never be modified ----string type
    doc = contents.data();						// raw html file never be modified ----char * type

/*
 * todo
 * 1. 打开文件添加失败跳转逻辑
 * 2. 重写StringSplit方法 换成string类型的参数
 * */


    /*
//    step 1 extract content between <head> & </head>
    char * headres;
    headres = StringCut(doc , "<head>" , "</head>");
    resfile << "title" << '\t' << StringCut((const char * )headres ,"<title>" , "</title>") << endl;
//
    char * keywordres= StringCut((const char * )headres,"<meta name=\"keywords\" content=\"" , "\" />");
    resfile << "keywords" << '\t' ;
//    PrintVector(StringSplit(keywordres , ",_") , resfile) ;
    resfile << endl ;
    resfile << "description" << '\t' << StringCut((const char * )headres , "<meta name=\"description\" content=\"" , "\" />") << endl;
    resfile << "author" << '\t' << StringCut((const char * )headres , "<meta name=\"author\" content=\"" , "\" />") << endl;

//    step 2 extract content between <body XXXXX> & </body>   --> target text
//    maybe you can try moving the file pointer after </head>   ------- to be optimized
    char * pattern = "<body.*>\n" ;
    char * doc_for_body = (char *)doc ;                              //    ------ to be optimized
    char * BodyTag = FindTagByReg(doc_for_body , pattern);
//    cout << "match tag " << BodyTag << endl;
    char * bodyres = StringCut(doc , BodyTag , "</body>") ;
//    resfile << "body" << '\t' << bodyres << endl;
*/

//    class Extractor
//    目前只有.NET支持不确定长度的逆序环视，所以 <?<=body.*>)不能使用
//    三种方法，1.用不确定长度的正则表达式做两次分割；
//    2.不确定长度的正则表达式做一次分割+一次匹配；
//    3.用不确定长度的起始正则表达式先匹配到确定的标签字符串，用确定的字符串+结束标签做逆序+顺序环视匹配中间内容。 in use
//
//    step 1 extract content between <head> and </head>

//    char * headres = FindSingleByPattern((char *)doc , "(?<=<head>).*?(?=</head>)");
    string HeadTag = FindSingleByPattern(contents,"<head.*?>");
    string headres = FindSingleByPattern(contents , "(?<="+HeadTag+").*?(?=</head>)");
    resfile << "title" << '\t' << FindSingleByPattern(headres ,"(?<=<title>).*?(?=</title>)") << endl;
//    char * keywordres= FindSingleByPattern(headres,"(?<=<meta name=\"keywords\" content=\").*?(?=\" />)");
    string keywordres = FindSingleByPattern(headres , "(?<=<meta name=\"keywords\" content=\").*?(?=\")");
    resfile << "keywords" << '\t' ;
    vector<string> keywordvec ;
    boost::split(keywordvec,keywordres,boost::is_any_of(",_"));
    PrintVector(keywordvec , resfile) ;
    resfile << endl ;
    resfile << "description" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"description\" content=\").*?(?=\")") << endl;
    resfile << "author" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"author\" content=\").*?(?=\")") << endl;

//    step 2 extract content between <body.*?> and </body>
//    maybe you can try moving the file pointer after </head>   ------- to be optimized

//    char * BodyTag = FindSingleByPattern((char *)doc , "<body.*?>") ;
    string BodyTag = FindSingleByPattern(contents , "<body.*?>");
//    cout << "match tag " << BodyTag << endl;
//    char * bodyres = FindSingleByPattern((char *)doc,"(?<="BodyTag").*?(?=</body>)");
    string bodyres = FindSingleByPattern(contents , "(?<="+BodyTag+").*?(?=</body>)" );
//    resfile << "body" << '\t' << bodyres << endl;


//    step 3 delete unneccessary tags and get target text
//    maybe you should save all unneccessary tags into a vector , delete them by traversing the vector ---- to be optimized
//    three kinds of tags : comments tag ; special character ; html content tag
//    char * commentres = DeleteByReg(bodyres,"<!--.*?-->|\/\*.*?\*\/");
    string commentres = DeleteByReg(bodyres , "<!.*?-->|/\\*.*?\\*/" );

//    char * contentres = DeleteByReg(commentres , "<script.*?</script>|<div.*?</div>");
    string contentres = DeleteByReg(commentres , "<script.*?>.*?</script>|<style.*?>.*?</style>");
    resfile << "body after dele <!&/**/&<script>&<style> " << endl ;
//    resfile << contentres << endl;
    string areares = DeleteByReg(contentres , "<div.*?>|<font.*?>|<p.*?>");
    resfile << "body after dele <div&<font&<p" << endl;
//    resfile << areares << endl;
//    char * characterres ;
    string characterres = DeleteByReg(areares , "&nbsp|&amp");
    resfile << "body after dele special character" << endl;
    resfile << characterres << endl;

//    class Parser
//    step 4 distinguish tag and text character  symbol is is_tag =0/1

//    step 5 get the candidate content by comparing with the threshold
    string target = characterres ;
    target = ReplaceSpace(target);

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
    TagFlag= JudgeTag(&contentStartLength, &contentEndLength, TagFlag, length, target, contentStart, contentEnd);
cout << "tagflag "<< *--TagFlag.end() << "," << TagFlag[0] << endl;
cout << "length : " << contentStartLength-1 << endl;
cout << "in main:contentStart:" << *contentStart.begin() <<","<< contentStart[contentStartLength-1] << endl;
    CandidateFlag= GetCandidates(CandidateFlag, TagFlag, length, arealength, factor);
    assert(!TagFlag.empty());
    assert(!CandidateFlag.empty());
    assert(!contentStart.empty());
    assert(!contentEnd.empty());
//    step 6 get the probable boarder by searching the max successive candidates
    int probablestart=0, probableend=0;
    GetProbableBoarder(&probablestart, &probableend, length, CandidateFlag, arealength);

    cout << probablestart << ":" << probableend << endl;
//    class Caculator
//    step 7 caculate density and get the accurate border
    CaculateDensity(&exact_x, &exact_y, probablestart, probableend, TagFlag, contentStart, contentEnd, contentStartLength, contentEndLength, length);
cout << " caculatedensity " << endl;
    cout << "x:" << exact_x << " y:" << exact_y << endl;
    cout << "target text:" << endl;
    for(int count = exact_x; count <= exact_y; count++){
        cout << target[count] ;
    }
    cout << endl;

//    step 8 delete unneccessary tags

//  Release vector's memory
    vector<int>().swap(contentStart);
    vector<int>().swap(contentEnd);
    vector<int>().swap(TagFlag);
    vector<int>().swap(CandidateFlag);

//    donnot forget close files
    fin.close();
    resfile.close();
    return EXIT_SUCCESS;
}

