#include "include/err.hh"

void ERR_argument_expected () {
    printf("wgpp: The wg++ 's compiler as every compiler needs a file to compile it...\n");
    exit(1);
}

void ERR_file_doesnt_exist () {
    printf("wgpp: The file given as parameter does not exist\n");
    exit(1);
}

void ERR_semicolon_expected (unsigned int intline) {
    printf("wgpp: Semicolon token expected on %d line\n", intline);
    exit(1);
}

void ERR_scape_code_expected (unsigned int intline) {
    printf("wgpp: Scape code expected on %d line\n", intline);
    exit(0);
}

void ERR_function_doesnt_exist (const std::string &fn) {
    printf("wgpp: Trying to call to %s function but that function has not been declared\n", fn.c_str());
    exit(1);
}

void ERR_overwrite_fucntion (const std::string &fn) {
    printf("wgpp: Trying to overwrite %s function, that function already has been declared\n", fn.c_str());
    exit(1);
}

void ERR_delimiter_expected (unsigned int intline) {
    printf("wgpp: Delimiter expected on %d line\n", intline);
    exit(1);
}

void ERR_line_doesnt_make_sense () {
    printf("wgpp: This line does not make any sense, maybe there are tokens that are incompatible together\n");
    exit(1);
}

void ERR_tokens_expected (std::string instructionType) {
    printf("wgpp: Some tokens were lost or expected\n");
    printf("  * if you don't know how to use this instruction type:\n");
    printf("  * $ how-to-wgpp %s\n", instructionType.c_str());
    exit(1);
}

void ERR_ilegal_character_definition (unsigned int intline) {
    printf("wgpp: Ilegar character on %d line\n", intline);
    printf("  * $ how-to-wgpp characters\n");
    printf("  * To know how the character works on wg++\n");
    exit(0);
}

void ERR_overwrite_variable (const std::string &varname, const std::string funcname) {
    printf("wgpp: '%s' variable already has been declared on `%s` function\n", varname.c_str(), funcname.c_str());
    printf("  * If you wanna change the value of any variable use 'CHG'\n");
    exit(1);
}
