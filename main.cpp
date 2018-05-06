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
#include <dirent.h>

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
            filelist.push_back(dirp->name);
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

    for(int i=0; i<filelist.size(); i++){
//      open file for writing results
        ofstream resfile;
        string resultfile = "result/" +file_pre.at(i) +"_result.txt";
        resfile.open(resultfile);
        assert(resfile) ;

//        open log for writing stdout
        ofstream logfile;
        string recordfile = "log/" +file_pre.at(i) +"_log.txt";
        logfile.open(recordfile);
        assert(logfile) ;

//      read html file
        ifstream fin;
        fin.open(filelist.at(i));
        assert(fin) ;
        const char * doc;
//    txt -> string
//    doc is const value === htmlfile
        stringstream buffer;
        buffer << fin.rdbuf();
        string contents(buffer.str());              // raw html file never be modified ----string type
        doc = contents.data();						// raw html file never be modified ----char * type

        noise_remove(contents, resfile, logfile);

//    donnot forget close files
        fin.close();
        resfile.close();
        logfile.close();
    }
    return EXIT_SUCCESS;

}

