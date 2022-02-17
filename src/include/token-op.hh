/** Crated by jdpmm on 11-02-2022 **/
#ifndef WGGP_PROGRAMMING_LANGUAGE_TOKEN_OP_HH
#define WGGP_PROGRAMMING_LANGUAGE_TOKEN_OP_HH

#include "token-types.hh"
#include "functions.hh"
#include "temp.hh"
#include "tokens-checker.hh"
#include "generate.hh"

std::size_t TOKEN_make_iniToken ();
void TOKEN_push_token           (std::size_t idx, TType type, std::string vast, int ld);
void TOKEN_print_tokens_found   (std::vector<TOKEN> lineT, std::string nameFUNC);
void TOKEN_parser               ();

#endif
