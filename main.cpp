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

#include "noise_remove.h"

int main(int argc, char const *argv[])
{
//    traverse direction
    vector<string> filelist;
    vector<string> file_pre;

    struct dirent *dirp;
    DIR* dir = opendir("./htmlfiles");
    while ((dirp = readdir(dir)) != NULL) {
        if (dirp->d_type == DT_REG) {
            // 文件
            cout << dirp->d_name << endl;
            filelist.push_back(dirp->d_name);
            vector<string> splitvec;
            boost::split(splitvec,dirp->d_name,boost::is_any_of("."));
            file_pre.push_back(splitvec[0]);
        } else if (dirp->d_type == DT_DIR) {
            // 文件夹
//            do nothing
        }
    }
//    donnot forget close the direction
    closedir(dir);
    clock_t sumStart = clock();
    clock_t sumEnd;
    for(int i=0; i<filelist.size(); i++){
//      open file for writing results
        ofstream resfile;
//        cout << "main.cpp 47" <<endl;
        string resultfile;
        try {
            resultfile = "result/" + file_pre.at(i) + "_result.txt";
        }catch(exception &e){
            cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << e.what() << endl;
        }

        resfile.open( resultfile.data());
        assert(resfile) ;

//        open log for writing stdout
        ofstream logfile;
//        cout << "main.cpp 54" <<endl;
        string recordfile;
        try {
            recordfile = "log/" + file_pre.at(i) + "_log.txt";
        }catch(exception &e){
            cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << e.what() << endl;
        }
        logfile.open(recordfile.data());
        assert(logfile) ;

//      read html file
        ifstream fin;
//        cout << "main.cpp 59" <<endl;
        string readfile;
        try {
            readfile = "htmlfiles/" + filelist.at(i);
        }catch(exception &e){
            cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << e.what() << endl;
        }
        fin.open(readfile.data());
        assert(fin) ;
        const char * doc;
//    txt -> string
//    doc is const value === htmlfile
        stringstream buffer;
        buffer << fin.rdbuf();
        string contents(buffer.str());              // raw html file never be modified ----string type
        doc = contents.data();						// raw html file never be modified ----char * type

//        Timing start
        clock_t start;
        clock_t end;
        start = clock();
        string rescontents = noise_remove(contents, resfile, logfile);
//        Timing end
        end = clock();
        logfile << "noise_remove Runtime " << endl;
        logfile << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

        resfile << "final result :" << endl;
        resfile << rescontents << endl;

//    donnot forget close files
        fin.close();
        resfile.close();
        logfile.close();
    }
    sumEnd = clock();
    cout << "sum runtime: " << (double)(sumStart - sumEnd) / CLOCKS_PER_SEC << "S" << endl;
    return EXIT_SUCCESS;

}

