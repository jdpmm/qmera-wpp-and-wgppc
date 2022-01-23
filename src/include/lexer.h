/** This file has been created to clean and analyze every line in the wgpp code, also
 * search tokens and push them, but that process is job of another file
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___LEXER_H
#define WG___LEXER_H

#include "token-operations.h"
#include "util.h"
#include <iostream>

/* A comment could be in a several lines, so we need to know if one comment was opened in N line
 * and was closed in M line */
bool comment_declared = false;

void searching_tokens (const std::string &line, int line_code, size_t idxHeadToken) {
    size_t idx = 0;
    std::string token;

    while ( line[idx] != '\0' ) {
        token += line[idx];

        if ( token == ";" ) {
            push_token(idxHeadToken, SEMI_COLON, token, line_code);
            token = "";
        }
        if ( token == "exit" ) {
            push_token(idxHeadToken, EXIT_FUNC, token, line_code);
            token = "";
        }
        if ( std::isdigit(token[0]) ) {
            token = get_whole_number(line, idx);
            push_token(idxHeadToken, NUMBER, token, line_code);
            idx += token.size() - 1;
            token = "";
        }
        if ( token[0] == '"' ) {
            token = str_until_(line, idx, '"');
            token += '"';
            push_token(idxHeadToken, STRING, token, line_code);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "wout" ) {
            push_token(idxHeadToken, WOUT_FUNC, token, line_code);
            token = "";
        }

        idx++;
    }
}

bool skip_comment (const std::string &line, size_t *idx) {
    /* The goal is reach to '#' symbol when a comment has been declared
    * if the comment is not closed in this line the lexer must ask the next line
    * in which maybe is the symbol needed to close the comment */
    comment_declared = true;
    do {
        if ( *idx >= line.size() ) return true;
        *idx += 1;
    } while ( line[*idx] != '#' );

    comment_declared = false;
    return false;
}

void start_lexer (const std::string &line, int line_code) {
    /* The goal is remove every white space except in there is a string, also it must
     * check the comments and ignore it */
    std::string clean_line;
    size_t idx = 0;

    while ( line[idx] != '\0' ) {
        while ( std::isspace(line[idx]) )
            idx++;
        if ( comment_declared )
            if ( skip_comment(line, &idx) ) return;
        if ( line[idx] == '#' )
            if ( skip_comment(line, &idx) ) return;
        if ( line[idx] == '"' ) {
            std::string str = str_until_(line, idx, '"');
            clean_line += str;
            idx += str.size();
        }

        clean_line += line[idx];
        idx++;
    }

    if ( clean_line != "#" ) {
        size_t idx_head = make_head_token();
        searching_tokens(clean_line, line_code, idx_head);
    }
}

#endif