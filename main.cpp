#include <stdio.h>
#include <cstdlib>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <dirent.h>
#endif
#include <cstring>

#include <string>
#include <vector>

#include "analys.h"
#include "extractor.h"

int main(int argc, char* argv[]) {
    const char *header = "Пластина,Годных,Конт. обр.,Конт. КЗ,IILC,IIHC,IILH,IILL,IREF,IOZH,IOZL,IIA 5.5В,IIA 0.0В,ICC VCCa,ICC VCCd,ICC сумм.,UOL,UOH,El 5.5В,Eld 5.5В,E0 5.5В,Eg 5.5В,MC_n 5.5В,MC_rl 5.5В,CB_n 5.5В,mCB_n 5.5В,El 4.5В,Eld 4.5В,E0 4.5В,Eg 4.5В,MC_n 4.5В,MC_rl 4.5В,CB_n 4.5В,mCB_n 4.5В";

    if(argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n    or %s <file_path> -f\n", argv[0], argv[0]);
        return 1;
    }

    
    if(argc <= 2 || strcmp(argv[2], "-f") != 0) {
        FILE *csv = fopen("PyPlast-tests.csv", "w+");
        if (!csv){
            perror("Cannot use the file \"PyPlast-tests.csv\"");
            exit(1);
        }

        fprintf(csv, "%s\n", header);
#ifdef _WIN32
        std::string search_path = std::string(argv[1]) + "\\*";
        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);

        if(hFind == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Unable to open directory: %s\n", argv[1]);
            return 1;
        }

        do {
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            std::string filename = fd.cFileName;

            if(filename.find("V434-0021-") != std::string::npos) {
                std::string filepath = std::string(argv[1]) + "\\" + filename;
                FILE *file = fopen(filepath.c_str(), "r");
                if (!file){
                    perror("Cannot open file");
                    exit(1);
                }

                _test test = extract(file, fd.cFileName);

                if(argc > 2) {
                    printf("%s\n", fd.cFileName);
                    if(strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "-df") == 0) {
                        _debug(test, (strcmp(argv[2], "-df") == 0));
                    }
                }

                fprintf(csv, "%s\n", proccesData(test).c_str());
                fclose(file);
            }
        } while(FindNextFileA(hFind, &fd));
        FindClose(hFind);
#else

        DIR *dir = opendir(argv[1]);

        if (dir == NULL) {
            perror("Unable to open directory");
            return 1;
        }

        struct dirent *entry;
        while((entry = readdir(dir)) != NULL) {
            if(entry->d_name[0] == '.') {
                continue;
            }

            std::string filepath = entry->d_name;

            if(filepath.find("V434-0021-") != std::string::npos) {
                filepath = std::string(argv[1]) + "/" + filepath;

                FILE *file = fopen(filepath.c_str(), "r");
                if (!file){
                    perror("Cannot use the file \"file\"");
                    exit(1);
                }

                _test test = extract(file, entry->d_name);

                if(argc > 2) {
                    printf("%s\n", entry->d_name);
                    if(strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "-df") == 0) {
                        _debug(test, (strcmp(argv[2], "-df") == 0));
                    }
                }

                fprintf(csv, "%s\n", proccesData(test).c_str());

                fclose(file);
            }
        }

        closedir(dir);
#endif
        fclose(csv);
    }
    else if (argc > 2 && (strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "-fdf") == 0)) {
        FILE *file = fopen(argv[1], "r");
        if (!file){
            perror("Cannot use the file \"file\"");
            exit(1);
        }
        _debug(extract(file, argv[1]), strcmp(argv[2], "-fdf") == 0);
    }
    return 0;
}