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
    string contents(buffer.str());
    doc = contents.data();						// raw html file never be modified

//    step 1 extract content between <head> & </head>
    char * headres;
    headres = StringCut(doc , "<head>" , "</head>");
    resfile << "title" << '\t' << StringCut((const char * )headres ,"<title>" , "</title>") << endl;
//    resfile << "keywords" << '\t' << StringCut((const char * )headres,"<meta name=\"keywords\" content=\"" , "\" />") << endl;
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
    resfile << "body" << '\t' << bodyres << endl;

//    you need all strings surrounded by script tags  return array of char *
//    vector<char *> ScriptTags = FindMultiTagByReg(bodyres , "<scipt*</script>");
    char * scriptres = DeleteByReg(bodyres , "<script.*?</script>");
    resfile << "body after dele <script> " << '\t' << scriptres << endl;

//    step 3 delete unneccessary tags in target text
//    maybe you should save all unneccessary tags into a vector , delete them by traversing the vector ---- to be optimized


//    donnot forget close files
    fin.close();
    resfile.close();
    return EXIT_SUCCESS;
}

