/** Crated by jdpmm on 11-02-2022 **/
#ifndef WGGP_PROGRAMMING_LANGUAGE_TOKEN_TYPES_HH
#define WGGP_PROGRAMMING_LANGUAGE_TOKEN_TYPES_HH

#include <iostream>
#include <vector>
enum class TType : unsigned int {
    EXIT_FUNC,
    SEMICOLON,
    WOUT_FUNC,
    INT_RW,
    CHR_RW,
    STRING_V,
    CHARCTER_V,
    NUMBER_V,
    ID,
    EQUALS_S,
    PRINTF_FUNC
};

struct TOKEN {
    TType type;
    unsigned int line_definition;
    std::string value_as_token;
};
extern std::vector<std::vector<TOKEN>> tokens;

#endif
