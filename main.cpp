#include "filelister.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <memory.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <strings.h> // Per strcasecmp


bool verbose = false;

int main(int argc, char *argv[])
{
    string a="",pth="./",qfp="",u="";
    int i=0;
    char s[256],t[80];
    FILE *f=nullptr,*ef=nullptr;
    struct QuickFile qf;
    struct File_Header fh;
    uint32_t p;
    uint16_t q;
    long secondi;

    if (argc>1){
        a = argv[1];
        if (a == "?" || a == "-h" || a == "--help"){
            Usage();
            return(0);
        }
        for (i=1; i<argc; i++){
            a = argv[i];
            if (startsWith(a,"-p")) {
                if (i+1 < argc){
                    pth = argv[i+1];
                }
            }
            if (startsWith(a,"-l")) {
                verbose = true;
            }
        }
    }

    if (pth[pth.length()-1] != '/') pth+='/';

    u = pth + trovaFileCaseInsensitive(pth, "file.dat");

    if ((f=fopen(u.data(),"r"))){
        memset(&qf,0,sizeof(struct QuickFile));
        while(fread(&qf,sizeof(struct QuickFile),1,f)){
            secondi = ntohl(qf.date) + 252460800;
            q = ntohs(qf.number);
            qf.number = q;
            if (verbose){
                u=pth + trovaFileCaseInsensitive(pth,to_string(qf.number)+".fd");
                ef = fopen(u.data(), "r");
                if (!ef){
                    u=pth + to_string(qf.number)+".fd";
                    ef = fopen(u.data(), "r");
                }
                if (ef){
                    memset(&fh,0,sizeof(struct File_Header));
                    fread(&fh,sizeof(struct File_Header),1,ef);
                    fclose(ef);
                }
            }
            p = ntohl(qf.size);
            qf.size = p;
            a = qf.desc;
            replaceAll(a, "\n","");
            replaceAll(a, "\r","");
            tm* tempo_locale = std::localtime(&secondi);
            strftime(t, sizeof(t), "%d-%m-%Y %H:%M", tempo_locale);
            sprintf(s,"%5u %-36s %8u %s %-60s",qf.number,qf.filename,qf.size,t,a.data());
            u = fh.From;
            q = ntohs(fh.Times_Downloaded);
            fh.Times_Downloaded = q;
            if (verbose) sprintf(s,"%5u %-36s %8u %s %-16s %8u %-60s",qf.number,qf.filename,qf.size,t,u.substr(0,16).data(),fh.Times_Downloaded,a.data());
            cout << s << endl;
        }
        fclose(f);
    }
    else {
        cout << "Cannot open '" << pth << "' file!" << endl;
        return(1);
    }

    return 0;
}


void Usage(void){
    cout << prgname + " v" + version << endl;
    cout << copyright << endl;
    cout << email << endl;
    cout << endl;
    cout << "Usage: " << prgname << " [options]" << endl;
    cout << "where options are:" << endl;
    cout << "-p <path>" << endl;
    cout << "-l for verbose list" << endl;
    cout << endl;
}

bool startsWith(const string& str, const string& prefix) {
    // compare(pos, count, str) checks if the substring starting at pos
    // with length count matches the provided string
    return str.compare(0, prefix.length(), prefix) == 0;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string trovaFileCaseInsensitive(const string& directory, const string& nomeCercato) {
    DIR* dir = opendir(directory.c_str());
    if (dir == nullptr) {
        return ""; // Directory non trovata
    }

    struct dirent* ent;
    string nomeTrovato = "";

    // Scansiona tutti i file nella directory
    while ((ent = readdir(dir)) != nullptr) {
        // Ignora maiuscole/minuscole
        if (strcasecmp(ent->d_name, nomeCercato.c_str()) == 0) {
            nomeTrovato = ent->d_name;
            break;
        }
    }

    closedir(dir);
    return nomeTrovato;
}

