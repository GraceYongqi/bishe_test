//
// Created by Grace on 2018/4/24.
//

#include "extraction.h"

/*
 * match tag which format is unsure or not fixed
 * return a accurate tag(string) as argument passed to StringCut
 * */
char *FindTagByReg(char *raw, char *pattern, ofstream &logfile) {

    char *outdata;
    regex_t reg;
    regmatch_t pm[1];
    int status = 0;
    /*编译正则表达式*/
    status = regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE | REG_ICASE);
//    status = regcomp(&reg, pattern, REG_EXTENDED|REG_ICASE);
    // ICASE ignore capital or not
    //EXTENED more completed pattern could be used
    //NEWLINE recognize line break symbol
    //without NEWLINE compiler would consider raw as one complete string

    if (status != 0) {
        return NULL;
    }
    status = regexec(&reg, raw, 1, pm, 0);
    if (status == REG_NOMATCH) {
        printf("no match!\n");
        status = -1;
    } else if (status != 0) {
        return NULL;
    } else if (status == 0) {
        int i, j;
        i = pm[0].rm_so;
        for (int pos = 0; pos < i; pos++) {
            raw++;
        }

        outdata = new char[pm[0].rm_eo - pm[0].rm_so + 1];
        strncpy(outdata, raw, pm[0].rm_eo - pm[0].rm_so);
        outdata[pm[0].rm_eo - pm[0].rm_so] = '\0';
    }
    regfree(&reg);
    return outdata;
}

//vector<char *>FindMultiByPattern(char * raw ,  char * pattern ){
vector<string> FindMultiByPattern(string raw, string pattern, ofstream &logfile) {
//    vector<char *>Multi ;
    vector<string> Multi;
//    string str(raw);
    boost::regex e1(pattern);

    std::string::const_iterator start, end;
//    start = str.begin();
//    end = str.end();
    start = raw.begin();
    end = raw.end();
    boost::match_results <std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    while (regex_search(start, end, what, e1, flags))        //type of search function return value : bool
    {
        string temp = string(what[0].first, what[0].second);
//        char *tmp = (char *)temp.data();
//        Multi.push_back(tmp) ;
        Multi.push_back(temp);
        //logfile << "match: " << string(what[0].first,what[0].second) << endl;
        start = what[0].second;
    }

    return Multi;
}

/*
 * extract string according to regex expression
 * you can extract content before B by using
 * (?<=A).*?(?=B)
 * only .NET support (?<=A.*?>)  unfixed length
 * */

//char * FindSingleByPattern(char * raw , char * pattern){
string FindSingleByPattern(string raw, string pattern, ofstream &logfile) {
    assert(raw.size() != 0);
    string Single;
//    string str(raw);
    boost::regex e1(pattern);
    std::string::const_iterator start, end;
//    start = str.begin();
//    end = str.end();
    start = raw.begin();
    end = raw.end();
    boost::match_results <std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    if (regex_search(start, end, what, e1, flags)) //type of search function return value : bool
    {
        string temp = string(what[0].first, what[0].second);
//        char *tmp = (char *)temp.data();
//        Single = tmp ;
        Single = temp;
//        logfile << "match: " << string(what[0].first,what[0].second) << endl;
//        start = what[0].second;
    }
    return Single;

}


//char * DeleteByReg(char * raw , char * pattern){
string DeleteByReg(string raw, string pattern, ofstream &logfile) {
//    std::string reg = pattern;
//    boost::regex r(reg);
    boost::regex r(pattern);
    std::string fmt("\0");
//    std::string res(raw);
//    std::logfile << regex_replace(res, r, fmt) << std::endl;
//    string temp =  regex_replace(res, r, fmt);
    raw = regex_replace(raw, r, fmt);
//    raw = (char *)temp.data();
    return raw;
}

string ReplaceSpace(string raw, ofstream &logfile) {
    boost::regex r1(" +");
    std::string fmt1(" ");
    raw = regex_replace(raw, r1, fmt1);
    boost::regex r2("\n+");
    std::string fmt2("\n");
    raw = regex_replace(raw, r2, fmt2);
    return raw;
}

string Replace(string raw, string from, string to, ofstream &logfile){
    boost::regex r(from);
//    std::string fmt(to);
    raw = regex_replace(raw, r, to);
    return raw;
}

/*
 * extract content between two strings/tags
 * format determined
 *
 * */


char *StringCut(const char *raw, char *start, char *end, ofstream &logfile) {
    char *nomatch = "not exist";
    if (!start || !end) {
        logfile << "start null" << endl;
        return nomatch;
    }
    char *strtmp1 = strstr((char *) raw, start);
    if (!strtmp1) {
        logfile << "start not exist" << endl;
        return nomatch;
    }
    char *strtmp2 = strstr(strtmp1, end);
    if (!strtmp1 || !strtmp2) {
        logfile << "end not exist" << endl;
        return nomatch;
    }

    int len1 = strlen((const char *) start);

    char *newstr = new char[strtmp2 - strtmp1 + 1];
    memset(newstr, 0, (strtmp2 - strtmp1 + 1) * sizeof(char));
    for (int i = 0; i < len1; i++) {
        strtmp1++;
    }
    return strncpy(newstr, strtmp1, strtmp2 - strtmp1);
}


/*
 * extract content between two tags/strings
 * format not sure
 * 'start' here is not a accurate word for matching
 * you need find the complete tag containing this word
 * */
/*
char * CompleteSpringCut(const char * raw , char * start , char * end){
    const char * pattern = "<"
}
*/





/*
 * extract words from one string by delimiter
 * return a vector of words
 *
 * */
vector<char *> StringSplit(char *raw, char *delim, ofstream &logfile) {
    char *temp;
    vector<char *> SplitRes;
    temp = strtok(raw, (const char *) delim);
    while (temp) {
        SplitRes.push_back(temp);
        temp = strtok(NULL, (const char *) delim);
    }
    return SplitRes;
}

/*
 * print elements of the vector
 * */

int PrintVector(vector<string> v, ofstream &resfile, ofstream &logfile) {     //basic class(basic_ios) does not allow to be copied ,
    //you must pass the quotation arguement
    for (vector<string>::const_iterator iter = v.begin(); iter != v.end(); iter++) {
        resfile << (*iter) << '\t';
    }
    return EXIT_SUCCESS;
}







