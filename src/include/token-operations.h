/** This file has been created to save all tokens found it and save the parser
 * function, a very useful function
 * - Created to jdpmm on 22-01-2022 **/
#ifndef WG___TOKEN_OPERATIONS_H
#define WG___TOKEN_OPERATIONS_H

#include "token.h"
#include "template.h"

size_t make_head_token () {
    /* Set a new head, every new head means new line of code which will have
     * N tokens */
    tokenHeads.emplace_back(std::vector<token> ());
    return tokenHeads.size() - 1;
}

void push_token (size_t idx, TokenType type, const std::string &tkn_value_str, int line_definition ) {
    token NewToken;
    NewToken.line_definition = line_definition;
    NewToken.type = type;
    NewToken.value_as_token = tkn_value_str;

    tokenHeads.at(idx).push_back(NewToken);
}

void print_line (std::vector<token> *line_tkns) {
    /* Prints all tokens found it in every line, this is so useful
     * when there is an error because we show the struct of the line
     * and the line when the error happened */
    printf("%d :: TOKENS <", line_tkns->at(0).line_definition);
    for (auto & token : *line_tkns)
        printf(" %s", token.value_as_token.c_str());
    printf(" >\n");
}

void parser () {
    for (auto & tokenHead : tokenHeads) {
        std::vector<token> *currntLine = &tokenHead;
        print_line(currntLine);
    }
}

#endif