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

/*
 * function declaration
 * */

int main(int argc, char const *argv[])
{
//    open file for writing results
    ofstream resfile;
    resfile.open("result.txt");
//    read html file
    ifstream fin;
    fin.open("test.txt");
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

//    目前只有.NET支持不确定长度的逆序环视，所以 <?<=body.*>)不能使用
//    三种方法，1.用不确定长度的正则表达式做两次分割；
//    2.不确定长度的正则表达式做一次分割+一次匹配；
//    3.用不确定长度的起始正则表达式先匹配到确定的标签字符串，用确定的字符串+结束标签做逆序+顺序环视匹配中间内容。 in use
//
//    step 1 extract content between <head> and </head>

//    char * headres = FindSingleByPattern((char *)doc , "(?<=<head>).*?(?=</head>)");
    string headres = FindSingleByPattern(contents , "(?<=<head>).*?(?=</head>)");
    resfile << "title" << '\t' << FindSingleByPattern(headres ,"(?<=<title>).*?(?=</title>)") << endl;
//    char * keywordres= FindSingleByPattern(headres,"(?<=<meta name=\"keywords\" content=\").*?(?=\" />)");
    string keywordres = FindSingleByPattern(headres , "(?<=<meta name=\"keywords\" content=\").*?(?=\" />)");
    resfile << "keywords" << '\t' ;
//    PrintVector(StringSplit(keywordres , ",_") , resfile) ;
    resfile << endl ;
    resfile << "description" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"description\" content=\").*?(?=\" />)") << endl;
    resfile << "author" << '\t' << FindSingleByPattern(headres , "(?<=<meta name=\"author\" content=\").*?(?=\" />)") << endl;

//    step 2 extract content between <body.*?> and </body>
//    maybe you can try moving the file pointer after </head>   ------- to be optimized

//    char * BodyTag = FindSingleByPattern((char *)doc , "<body.*?>") ;
    string BodyTag = FindSingleByPattern(contents , "<body.*?>");
//    cout << "match tag " << BodyTag << endl;
//    char * bodyres = FindSingleByPattern((char *)doc,"(?<="BodyTag").*?(?=</body>");
    string bodyres = FindSingleByPattern(contents , "(?<="+BodyTag+").*?(?=</body>" );
//    resfile << "body" << '\t' << bodyres << endl;


//    step 3 delete unneccessary tags and get target text
//    maybe you should save all unneccessary tags into a vector , delete them by traversing the vector ---- to be optimized
//    three kinds of tags : comments tag ; special character ; html content tag
//    char * commentres = DeleteByReg(bodyres,"<!--.*?-->|/\*.*?\*/");
    string commentres = DeleteByReg(bodyres , "<!--.*?-->|/\*.*?\*/" );
//    char * contentres = DeleteByReg(commentres , "<script.*?</script>|<div.*?</div>");
    string contentres = DeleteByReg(commentres , "<script.*?</script>|<div.*?</div>");
    resfile << "body after dele <script> " << '\t' << contentres << endl;
//    char * characterres ;
    string characterres ;
    resfile << "body after dele special character" << '\t' << characterres << endl;

//    step 4 get the core content by comparing with the threshold

//    step 5 ensure the exact boarder
//    donnot forget close files
    fin.close();
    resfile.close();
    return EXIT_SUCCESS;
}

