/*
 * todo
 *
 * body中的标签
 * 范围预估
 *
 * */
 //git test
/*
 *  initialize ssh pub key :https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/#platform-linux
 *   Start the ssh-agent in the background : eval "$(ssh-agent -s)"
 *   ssh git passphrase: forgit
 *   git clone git@github.com:GraceYongqi/bishe_test.git
 *
*/




//#include <Parser.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <regex.h>
#include <assert.h>

#define  EXIT_SUCCESS 0 ;

using namespace std;

/*
 * function declaration
 * */
char * FindTagByReg(char *raw, char *pattern);
char * StringCut(const char * raw , char * start, char * end);
vector<char *> StringSplit(char * raw , char * delim );
int PrintVector(vector<char *> v , ofstream &resfile);

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
    char * MatchTag = FindTagByReg(doc_for_body , pattern);
    cout << "match tag " << MatchTag << endl;
    resfile << "body" << '\t' << StringCut(doc , MatchTag , "</body>") << endl;

//    step 3 delete unneccessary tags in target text
//    maybe you should save all unneccessary tags into a vector , delete them by traversing the vector ---- to be optimized


//    donnot forget close files
    fin.close();
    resfile.close();
    return EXIT_SUCCESS;
}

/*
 * match tag which format is unsure or not fixed
 * return a accurate tag(string) as argument passed to StringCut
 * */
char * FindTagByReg(char *raw, char *pattern){
    char * outdata;
    regex_t reg;
    regmatch_t pm[1];
    int  status = 0;
    /*编译正则表达式*/
     status = regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE|REG_ICASE);
//    status = regcomp(&reg, pattern, REG_EXTENDED|REG_ICASE);
    // ICASE ignore capital or not
    //EXTENED more completed pattern could be used
    //NEWLINE recognize line break symbol
    //without NEWLINE compiler would consider raw as one complete string

    if (status != 0){
        return NULL;
    }
    status = regexec(&reg, raw, 1, pm, 0);
    if (status == REG_NOMATCH){
        printf("no match!\n");
        status = -1;
    }
    else if (status != 0) {
        return NULL;
    }
    else if (status == 0) {
        int i, j;
        i = pm[0].rm_so;
        for(int pos =0;pos<i;pos++){
            raw++;
        }

        outdata = new char[pm[0].rm_eo-pm[0].rm_so+1];
        cout << "size : " << pm[0].rm_eo-pm[0].rm_so << endl;
        strncpy(outdata , raw , pm[0].rm_eo-pm[0].rm_so);
        outdata[pm[0].rm_eo-pm[0].rm_so] = '\0';
        cout << "out size " << strlen(outdata) << endl;
    }
    cout << "get outdata" << endl;
    regfree(&reg);
    return outdata;
}




/*
 * extract content between two strings/tags
 * format determined
 *
 * */
char * StringCut(const char * raw , char * start, char * end){
    char * nomatch  = "not exist" ;
    if(!start || !end){
        cout << "start null" << endl;
        return nomatch ;
    }
    char * strtmp1 = strstr((char * )raw, start);
    if(!strtmp1){
        cout << "start not exist" << endl;
        return nomatch ;
    }
    char * strtmp2 = strstr(strtmp1, end);
    if( !strtmp1 || !strtmp2 ){
        cout << "end not exist" << endl;
       return nomatch;
    }

    int len1 = strlen((const char * )start);
    cout << "strlen1 " << endl ;

    char * newstr = new char[strtmp2-strtmp1+1];
    memset(newstr , 0, (strtmp2-strtmp1+1)*sizeof(char));
    for(int i=0;i<len1;i++){
        strtmp1++;
    }
    return strncpy(newstr , strtmp1 , strtmp2-strtmp1);
}

/*
 * extract content between two tags/strings
 * format not sure
 * 'start' here is not a accurate word for matching
 * you need find the complete tag containing this word
 * */
/*
char * CompleteSprintCut(const char * raw , char * start , char * end){
    const char * pattern = "<"
}



char * FindSpringByPattern(const char * raw , char * tag){
    stringstream ss;
    ss << tag ;
    const char * pattern = "<"ss"*>";
    int ret = fnmatch(pattern, raw , FNM_PERIOD|FNM_CASEFOLD);  //CASEFOLD ignore capital or not
    if(ret == 0)          //符合pattern的结构
    {
        printf("%s\n", entry->d_name);
    }else if(ret == FNM_NOMATCH){
        continue ;
    }else
    {
        printf("error file=%s\n", entry->d_name);
    }
}

}
*/

/*
 * extract words from one string by delimiter
 * return a vector of words
 *
 * */
vector<char *> StringSplit(char * raw , char * delim ){
    char * temp ;
    vector<char *> SplitRes ;
    temp  = strtok(raw , (const char * )delim);
    while(temp){
        SplitRes.push_back(temp);
        temp = strtok(NULL , (const char * )delim);
    }
    return SplitRes ;
}

/*
 * print elements of the vector
 * */
/*
int PrintVector(vector<char *> v , ofstream  &resfile){     //basic class(basic_ios) does not allow to be copied ,
                                                            //you must pass the quotation arguement
    for(auto val : v){
        resfile << val << '\t' ;
    }
    return EXIT_SUCCESS;
}
*/






