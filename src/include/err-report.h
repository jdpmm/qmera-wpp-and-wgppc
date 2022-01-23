/** This file has been created to report any error while the compiling process
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___ERR_REPORT_H
#define WG___ERR_REPORT_H

#include <iostream>

void file_expected () {
    printf("Filename expected as argument\n");
    exit(1);
}

void file_doesnt_exist (char* filename) {
    printf("%s does not exist", filename);
    exit(1);
}

void no_make_sense () {
    printf("This line does not make sense\n");
    exit(1);
}

void token_expected (const std::string &token) {
    printf("Token expected: %s\n", token.c_str());
    exit(1);
}

void delimiter_expected () {
    printf("Delimiter expected\n");
    exit(1);
}

#endif