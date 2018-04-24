//
// Created by Grace on 2018/4/24.
//

#include "extraction.h"

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

vector<char *>FindMultiTagByReg(char * raw ,  char * pattern ){
    vector<char *>MultiTag ;

    string str(raw);
    boost::regex e1(pattern);

    std::string::const_iterator start, end;
    start = str.begin();
    end = str.end();
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    while(regex_search(start, end, what, e1, flags))
    {
        string temp = string(what[0].first,what[0].second) ;
        char *tmp = temp.data();
        MultiTag.push_back(tmp) ;
        cout << "match: " << string(what[0].first,what[0].second) << endl;
        start = what[0].second;
    }

    return MultiTag ;
}



char * DeleteByReg(char * raw , char * pattern){
    std::string phone = pattern;
    boost::regex r(phone);
    std::string fmt("");
    std::string number(raw);
//    std::cout << regex_replace(number, r, fmt) << std::endl;
    string temp =  regex_replace(number, r, fmt) << std::endl;
    raw = temp.data();
    return raw ;
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






