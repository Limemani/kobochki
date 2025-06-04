#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>

struct tabel {
    std::string test_name;
    int test_num;
    std::string exit_pin;
    int test_value;
    int min;
    int max;
    std::string param;
    std::string resualt;
};

struct _test {
    std::vector <tabel> extracted_tables;
    int wafer_num;
};

_test extract(FILE *test_subject) {
    _test extracted;
    extracted.wafer_num = -1;
    const std::string se = "******************************************************************************************************\n",
    test_value_s = "|____________________________________________________________________________________________________|\n",
    test_value_e = "|_________________________|__________|________|__________|__________|__________|__________|__________|\n",
    wafer = "Пластина №  ";
    const char test_value_spliter = '|';
    char buffer[256];
    bool is_end = false, is_value = false;
    unsigned int count = 0;
    
    while(fgets(buffer, sizeof(buffer), test_subject)) {
        if(is_value) {
            int coloumn = 0;
            std::string buf2[8] = {};
            for (int i = 1; i < 256; i++) {
                if(coloumn == 8){
                    break;
                }
                if(buffer[i] == '|') {
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
            to_push.test_num = std::atoi(buf2[1].c_str());
            to_push.exit_pin = buf2[2];
            to_push.test_value = std::atoi(buf2[3].c_str());
            to_push.min = std::atoi(buf2[4].c_str());
            to_push.max = std::atoi(buf2[5].c_str());
            to_push.param = buf2[6];
            to_push.resualt = buf2[7];
            extracted.extracted_tables.push_back(to_push);
        }
        is_value = false;
        if(extracted.wafer_num == -1) {
            for (int i = 0; i < 256; i++){
                if(buffer[i] == wafer[0]) {
                    bool f = true;
                    for (int j = 0; j < wafer.size(); j++){
                        if(buffer[i] != wafer[j]) {
                            f = !f;
                            break;
                        }
                         i++;
                    }
                    if(f) {
                        for(int j = 0; j < 10; j++){
                            if (buffer[i+j] == ' ') {
                                break;
                            }
                            extracted.wafer_num += (buffer[i+j]-47)*pow(10, j);
                        }
                        break;
                    }
                }
            }
        }
        if(std::string(buffer) == se && !is_end) {
            is_end = true;
        }
        else if(is_end && std::string(buffer) == se) {
            count++;
        }
        else if (is_end && std::string(buffer) == test_value_s){
            is_value = true;
        }
    }

    fclose(test_subject);
    return extracted;
}

void _debug(const _test& subj) {
    printf("Пластина %d\n", subj.wafer_num);
    for (int i = 0; i < subj.extracted_tables.size(); i++){
        const tabel& t = subj.extracted_tables[i];
        if(t.resualt == "Брак") {
            printf("%s _ %d _ %s _ %d _ %d _ %d _ %s _ %s\n", 
                t.test_name.c_str(), 
                t.test_num, 
                t.exit_pin.c_str(), 
                t.test_value,
                t.min,
                t.max,
                t.param.c_str(),
                t.resualt.c_str()
            );
        }
        else {
            printf("Годен\n");
        }
    }
}