#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>

struct tabel {
    std::string test_name;
    std::string resualt;
};

struct _test {
    std::vector <tabel> extracted_tables;
    int wafer_num;
};

_test extract(FILE *test_subject, char *filenmae) {
    _test extracted;
    extracted.wafer_num = -1;
#ifdef _WIN32
    const std::string test_value_s = "|____________________________________________________________________________________________________|\n";
#else
    const std::string test_value_s = "|____________________________________________________________________________________________________|\r\n";
#endif
    const char test_value_spliter = '|';
    char buffer[256];
    bool is_end = false, is_value = false;
    unsigned int count = 0;
    
    std::string wafle = "";
    int pos = 10;
    while (isdigit(filenmae[pos])) {
        wafle += filenmae[pos];
        pos++;
    }
    bool is_1 = true;
    for (auto p: wafle){
        if(p != '0' || p != '1'){
            is_1 = false;
            break;
        }
    }
    if(is_1){
        wafle += '1';
    }
    if(!wafle.empty()) {
        extracted.wafer_num = std::stoi(wafle);
    }

    while(fgets(buffer, sizeof(buffer), test_subject)) {
        std::string l = std::string(buffer);
        if(is_value) {
            int coloumn = 0;
            std::string buf2[8] = {};
            for (int i = 1; i < 256; i++) {
                if(coloumn == 8){
                    break;
                }
                if(buffer[i] == test_value_spliter) {
                    coloumn++;
                }
                else if(buffer[i] == ' ' && buffer[i+1] != ' ' && buffer[i-1] != ' ' ) {
                    buf2[coloumn] += buffer[i];
                }
                else if(buffer[i] != ' ') {
                    buf2[coloumn] += buffer[i];
                }
            }
            tabel to_push;
            to_push.test_name = buf2[0];
            to_push.resualt = buf2[7];
            extracted.extracted_tables.push_back(to_push);
        }
        is_value = false;
        if (std::string(buffer) == test_value_s){
            is_value = true;
        }
    }

    return extracted;
}


void _debug(const _test& subj, bool full) {
    printf("Пластина %d\n", subj.wafer_num);
    if(full) {
        for (int i = 0; i < subj.extracted_tables.size(); i++){
            const tabel& t = subj.extracted_tables[i];
            if(t.resualt == "Брак") {
                printf("%s _ %s\n", 
                    t.test_name.c_str(), 
                    t.resualt.c_str()
                );
            }
            else {
                printf("Годен\n");
            }
        }
    }
}