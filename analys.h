#include "extractor.h"

int detectField(const std::string& line) {
    if (line.find("Uccd") != std::string::npos) return 2;
    if (line.find("Ucca") != std::string::npos) return 3;
    if (line.find("IILC") != std::string::npos) return 4;
    if (line.find("IIHC") != std::string::npos) return 5;
    if (line.find("IILH") != std::string::npos) return 6;
    if (line.find("IILL") != std::string::npos) return 7;
    if (line.find("IREF") != std::string::npos) return 8;
    if (line.find("IOZH") != std::string::npos) return 9;
    if (line.find("IOZL") != std::string::npos) return 10;
    if (line.find("IIA") != std::string::npos) {
        if (line.find("5.500") != std::string::npos) return 11;
        if (line.find("0.0") != std::string::npos) return 12;
    }
    if (line.find("VCCa") != std::string::npos) return 13;
    if (line.find("VCCd") != std::string::npos) return 14;
    if (line.find("ICC") != std::string::npos) return 15;
    if (line.find("UOL") != std::string::npos) return 16;
    if (line.find("UOH") != std::string::npos) return 17;

    // 5.5В
    if (line.find("El") != std::string::npos && line.find("5.5") != std::string::npos) return 18;
    if (line.find("Eld") != std::string::npos && line.find("5.5") != std::string::npos) return 19;
    if (line.find("E0") != std::string::npos && line.find("5.5") != std::string::npos) return 20;
    if (line.find("Eg") != std::string::npos && line.find("5.5") != std::string::npos) return 21;
    if (line.find("MC_cnt") != std::string::npos) return 22;
    if (line.find("MC_rl") != std::string::npos) return 23;
    if (line.find("CB_cnt") != std::string::npos) return 24;
    if (line.find("mCB_cnt") != std::string::npos) return 25;

    // 4.5В
    if (line.find("El") != std::string::npos && line.find("4.5") != std::string::npos) return 26;
    if (line.find("Eld") != std::string::npos && line.find("4.5") != std::string::npos) return 27;
    if (line.find("E0") != std::string::npos && line.find("4.5") != std::string::npos) return 28;
    if (line.find("Eg") != std::string::npos && line.find("4.5") != std::string::npos) return 29;
    if (line.find("MC_cnt") != std::string::npos && line.find("4.5") != std::string::npos) return 30;
    if (line.find("MC_rl") != std::string::npos && line.find("4.5") != std::string::npos) return 31;
    if (line.find("CB_cnt") != std::string::npos && line.find("4.5") != std::string::npos) return 32;
    if (line.find("mCB_cnt") != std::string::npos && line.find("4.5") != std::string::npos) return 33;

    return 1;
}

std::string proccesData(_test data) {
    std::string res = std::to_string(data.wafer_num) + ',';
    unsigned int output_data[33] = {};
    for (int i = 0; i < 33; i++) {
        output_data[i] = 0;
    }
    for (auto p: data.extracted_tables){
        if(p.resualt != "Брак") {
            output_data[0]++;
        }
        else {
            output_data[detectField(p.test_name)]++;
        }
    }
    for (int i = 0; i < 33; i++) {
        res += std::to_string(output_data[i]);
        if(i != 32){
            res += ',';
        }
    }
    return res;
}
