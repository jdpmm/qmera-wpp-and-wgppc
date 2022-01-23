/** This file has been created to report any error while the compiling process
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___ERR_REPORT_H
#define WG___ERR_REPORT_H

#include <cstdio>
#include <cstdlib>

void file_expected () {
    printf("Filename expected as argument\n");
    exit(1);
}

void file_doesnt_exist (char* filename) {
    printf("%s does not exist", filename);
    exit(1);
}

#endif