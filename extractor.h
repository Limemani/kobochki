#include <stdio.h>
#include <string>
#include <vector>

struct tabel {
    std::string test_name;
    int test_num;
    std::string exit_code;
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
    const char *se = "******************************************************************************************************",
    *test_value_s = "|____________________________________________________________________________________________________|\n|",
    *test_value_e = "|\n|_________________________|__________|________|__________|__________|__________|__________|__________|";
    const char test_value_spliter = '|';

    // here extraction logic

    fclose(test_subject);
    return extracted;
}