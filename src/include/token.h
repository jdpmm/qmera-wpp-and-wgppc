/** This file has been created to save all token types and know how it works and
 * how can be used
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___TOKEN_H
#define WG___TOKEN_H

#include <iostream>
#include <vector>

enum TokenType {
    EXIT_FUNC,     // exit function, to exit sure: exit 0;
    NUMBER,        // any number
    SEMI_COLON,    // ";" symbol
};

typedef struct Token {
    std::string value_as_token;
    TokenType type;
    unsigned int line_definition;
} token;
std::vector<std::vector<token>> tokenHeads;

#endif