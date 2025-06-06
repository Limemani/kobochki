#include <stdio.h>
//#include "csv.h"
#include "extractor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // uncomment below line if you need printout extraction
    //_debug(extract(file, argv[1]));

    fclose(file);

    return 0;
}
