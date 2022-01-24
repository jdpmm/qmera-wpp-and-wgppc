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

void tokens_lost () {
    printf("Some tokens were lost\n");
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

void nonsense () {
    printf("This line doesn't make sense\n");
    exit(1);
}

void invalid_name (const std::string &name) {
    printf("Invalid character: %s\n", name.c_str());
    printf("The names only could have:\n");
    printf("  - [A-Z]\n");
    printf("  - [a-z]\n");
    printf("  - [0-9]\n");
    printf("  -   _\n");

    exit(1);
}

void var_doesnt_exits (const std::string &name, const std::string &defname) {
    printf("%s does not exist in %s function\n", name.c_str(), defname.c_str());
    exit(1);
}

void no_right_type_variable (const std::string &needed) {
    printf("%s type of variable needed\n", needed.c_str());
    exit(1);
}

#endif