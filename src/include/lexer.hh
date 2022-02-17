/** Crated by jdpmm on 11-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_LEXER_HH
#define WGPP_PROGRAMMING_LANGUAGE_LEXER_HH

#include "utils.hh"
#include "token-op.hh"

extern bool comment_declared;
void lexer         (const std::string &contents, unsigned int intline);
void skip_comment  (std::string line, std::size_t *idx);
void search_tokens (const std::string &line, unsigned int intline);

#endif
