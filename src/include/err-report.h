/** This file has been created to report any error while the compiling process
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WGPP_ERR_REPORT_H
#define WGPP_ERR_REPORT_H

#include <iostream>

void file_expected () {
    /** This error will be thrown when there isn't a second argument in the execution
     * of the program (C++ executable) **/
    printf("Filename expected as argument\n");
    exit(1);
}

void file_doesnt_exist (char* filename) {
    /** This error will be thrown then the file given as second parameter in the C++ execution file
     * does not exist **/
    printf("%s does not exist", filename);
    exit(1);
}

void tokens_lost () {
    /** This error will be thrown when a token is not in the list, and that token
     * is so useful to the operation, something like:
     * (C++) cout << ;
     * Token lost: string **/
    printf("Some tokens were lost\n");
    exit(1);
}

void token_expected (const std::string &token) {
    printf("Token expected: %s\n", token.c_str());
    exit(1);
}

void delimiter_expected () {
    /** This error will be thrown when there is a number or string and the lexer gotta
     * save all data, but this data never end, so the delimiter expected is the end of itself,
     * this function is used on "util.h" **/
    printf("Delimiter expected\n");
    exit(1);
}

void nonsense () {
    /** This error will be thrown when there is a line when were found some tokens
     * but these tokens don't make sense together **/
    printf("This line doesn't make sense\n");
    exit(1);
}

void invalid_name (const std::string &name) {
    /** This error will thrown when the lexer found a name of one variable or function
     * and the name contains characters not valid into an ID **/
    printf("Invalid character: %s\n", name.c_str());
    printf("The names only could have:\n");
    printf("  - [A-Z]\n");
    printf("  - [a-z]\n");
    printf("  - [0-9]\n");
    printf("  -   _\n");

    exit(1);
}

void var_doesnt_exits (const std::string &name, const std::string &defname) {
    /** This error will be thrown when, well the function name is so descriptive :D  **/
    printf("%s does not exist in %s function\n", name.c_str(), defname.c_str());
    exit(1);
}

void no_right_type_variable (const std::string &needed, const std::string &name_used) {
    /** This error will be thrown when a variable is been used in a specific operation
     * but the type variable expected for that operation is not the correct **/
    printf("%s type of variable needed\n", needed.c_str());
    printf("Reference to: %s\n", name_used.c_str());
    exit(1);
}

void trying_to_overwrite_variable () {
    printf("You are trying to change the value of this variable (wgdi) syntax\n");
    printf("If you want to change the value of one variable use CHG function instead\n");
    exit(1);
}

void printf_err () {
    printf("Printf only can take 5 arguments\n");
    exit(1);
}

void def_doesnt_exits (const std::string &name) {
    printf("%s does not exist as function\n", name.c_str());
    exit(1);
}

void trying_to_overwrite_function () {
    printf("You are trying to overwrite that function\n");
    printf("That function already exists\n");
    exit(1);
}

#endif