/** This file has been created to save all token types and know how it works and
 * how can be used
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WGPP_TOKEN_H
#define WGPP_TOKEN_H

#include <iostream>
#include <vector>

enum TokenType {
    EXIT_FUNC,     // exit function, to exit sure: exit 0;
    NUMBER,        // any number
    SEMI_COLON,    // ";" symbol
    STRING,        // string to be printed
    WOUT_FUNC,     // to print strings and values
    INT_RW,        // int reserved word, to make an integer variable
    VAR_NAME,      // ...
    EQUALS_S,      // equals symbol '='
    ARITH_CALL,    // calling to arithmetic function
    MATH_OP,       // mathematical operator
    L_PAR,         // left parenthesis
    R_PAR,         // right parenthesis
    CHG_CALL,      // Calling to change value function
    PRINTF_FUNC,   // printf function like printf of C
    INT_OP,        // integer operation: inc (++), dec (--) and neg (n * -1)
    CHR_RW,        // reserved word to create a character variable
    CHR_VAL,       // character value: 'c'
};

typedef struct Token {
    std::string value_as_token;
    TokenType type;
    unsigned int line_definition;
} token;
std::vector<std::vector<token>> tokenHeads;

#endif
