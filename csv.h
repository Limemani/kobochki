#include <stdio.h>
#include <fstream>

void generating_csv_file() {
    const char *header = "Пластина,Годных,Конт. обр.,Конт. КЗ,IILC,IIHC,IILH,IILL,IREF,IOZH,IOZL,IIA 5.5В,IIA 0.0В,ICC VCCa,ICC VCCd,ICC сумм.,UOL,UOH,El 5.5В,Eld 5.5В,E0 5.5В,Eg 5.5В,MC_n 5.5В,MC_rl 5.5В,CB_n 5.5В,mCB_n 5.5В,El 4.5В,Eld 4.5В,E0 4.5В,Eg 4.5В,MC_n 4.5В,MC_rl 4.5В,CB_n 4.5В,mCB_n 4.5В\n";

    FILE *csv = fopen("", "w+");
    if (!csv){
        perror("Cannot use the file");
        return 1;
    }

    // implement here massive convertion

    fprintf(csv, "%s", header);


    fclose(csv);
}