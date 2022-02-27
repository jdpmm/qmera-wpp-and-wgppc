#ifndef WGPP_PROGRAMMING_LANGUAGE_ERR_HH
#define WGPP_PROGRAMMING_LANGUAGE_ERR_HH
#include <iostream>

void ERR_argument_expected      ();
void ERR_file_doesnt_exist      ();
void ERR_semicolon_expected     (unsigned int intline);
void ERR_scape_code_expected    (unsigned int intline);

void ERR_function_doesnt_exist  (const std::string &fn);
void ERR_overwrite_fucntion     (const std::string &fn);

void ERR_delimiter_expected           (unsigned int intline);
void ERR_line_doesnt_make_sense       ();
void ERR_tokens_expected              (std::string instructionType);
void ERR_ilegal_character_definition (unsigned int intline);

void ERR_overwrite_variable    (const std::string &varname, const std::string &funcname);
void ERR_variable_doesnt_exist (const std::string &varname, const std::string &funcname);
void ERR_type_requierd         (const std::string &typerqd);

#endif
