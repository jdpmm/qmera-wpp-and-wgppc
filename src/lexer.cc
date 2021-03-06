#include "include/lexer.hh"
bool comment_declared = false;

void lexer (const std::string &contents, unsigned int intline) {
    std::string cLine;
    std::size_t idx_s = 0;
    std::string stringHelp;

    while ( idx_s <= contents.size() ) {
        SKIP_WHITESPACES:
        while ( std::isspace(contents[idx_s]) ) idx_s++;

        if ( contents[idx_s] == '#' || comment_declared ) {
            skip_comment(contents, &idx_s);
            if ( comment_declared ) return;
            idx_s++;
            goto SKIP_WHITESPACES;
        }
        if ( contents[idx_s] == '"' ) {
            stringHelp = UTL_get_until_delimiter(contents, idx_s, intline, '"');
            cLine += stringHelp;
            idx_s += stringHelp.size();
        }

        if ( contents[idx_s] == ';' && contents[idx_s + 1] != '\0' ) {
            cLine += contents[idx_s];
            search_tokens(cLine, intline);
            cLine = "";
            idx_s++;
            goto SKIP_WHITESPACES;
        }

        cLine += contents[idx_s];
        idx_s++;
    }

    if ( cLine.size() != 1 ) {
        if ( cLine[cLine.size() - 2] != ';' ) ERR_semicolon_expected(intline);
        search_tokens(cLine, intline);
    }
}

void skip_comment (std::string line, std::size_t *idx) {
    comment_declared = true;
    do {
        *idx += 1;
        if ( *idx > line.size() ) return;
    } while ( line[*idx] != '#' );

    comment_declared = false;
}

void search_tokens (const std::string &line, unsigned int intline) {
    std::string token;
    std::size_t idx = 0;
    std::size_t idxVT = TOKEN_make_iniToken();

    while ( line[idx] != '\0'  ) {
        token += line[idx];
        if ( token == ";" ) {
            TOKEN_push_token(idxVT, TType::SEMICOLON, token, intline);
            token = "";
        }
        if ( token == "exit" ) {
            TOKEN_push_token(idxVT, TType::EXIT_FUNC, token, intline);
            token = "";
        }
        if ( std::isdigit(line[idx]) || ( token == "-" && std::isdigit(line[idx + 1]) ) ) {
            token = UTL_get_whole_number(line, idx, intline);
            TOKEN_push_token(idxVT, TType::CONSTANT, token, intline);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "wout" ) {
            TOKEN_push_token(idxVT, TType::WOUT_FUNC, token, intline);
            token = "";
        }
        if ( token == "\"" ) {
            token = UTL_get_until_delimiter(line, idx, intline, '"');
            TOKEN_push_token(idxVT, TType::STRING, token, intline);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "'" ) {
            token = UTL_check_character(line, idx, intline);
            TOKEN_push_token(idxVT, TType::CONSTANT, token, intline);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "$" ) {
            token = UTL_get_until_delimiter(line, idx, intline, '$');
            TOKEN_push_token(idxVT, TType::ID_VARIABLE, token, intline);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "int" ) {
            TOKEN_push_token(idxVT, TType::INT_RW, token, intline);
            token = "";
        }
        if ( token == "=" ) {
            TOKEN_push_token(idxVT, TType::EQUALS_S, token, intline);
            token = "";
        }
        if ( token == "chr" ) {
            TOKEN_push_token(idxVT, TType::CHR_RW, token, intline);
            token = "";
        }
        if ( token == "printf" ) {
            TOKEN_push_token(idxVT, TType::PRINTF_FUNC, token, intline);
            token = "";
        }
        if ( token == "CHG" ) {
            TOKEN_push_token(idxVT, TType::CHG_FUNC, token, intline);
            token = "";
        }
        if ( token == "INC" || token == "DEC" || token == "NEG" ) {
            TOKEN_push_token(idxVT, TType::INT_FUNC, token, intline);
            token = "";
        }
        if ( token == "ARITH" ) {
            TOKEN_push_token(idxVT, TType::ARITH_CALL, token, intline);
            token = "";
        }
        if ( token == "add" || token == "sub" || token == "mul" || token == "div" || token == "mod" || token == "pot" ) {
            TOKEN_push_token(idxVT, TType::ARITH_OPERATOR, token, intline);
            token = "";
        }
        if ( token == "(" ) {
            TOKEN_push_token(idxVT, TType::L_PARENTHESES, token, intline);
            token = "";
        }
        if ( token == ")" ) {
            TOKEN_push_token(idxVT, TType::R_PARENTHESES, token, intline);
            token = "";
        }
        if ( token == "ptr" ) {
            TOKEN_push_token(idxVT, TType::PTR_RW, token, intline);
            token = "";
        }
        if ( token == "*" ) {
            token = UTL_get_until_delimiter(line, idx, intline, '*');
            TOKEN_push_token(idxVT, TType::ID_PTR, token, intline);
            idx += token.size() - 1;
            token = "";
        }
        if ( token == "&" ) {
            token = UTL_get_until_delimiter(line, idx, intline, '&');
            TOKEN_push_token(idxVT, TType::ID_ADDRESS, token, intline);
            idx += token.size() - 1;
            token = "";
        }

        idx++;
    }
}
