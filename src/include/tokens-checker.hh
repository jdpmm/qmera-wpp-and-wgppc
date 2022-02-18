/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_TOKENS_CHECKER_HH
#define WGPP_PROGRAMMING_LANGUAGE_TOKENS_CHECKER_HH

#include "token-types.hh"
#include "err.hh"

char SC_exit_funtion  (std::vector<TOKEN> list);
char SC_wout_function (std::vector<TOKEN> list);
char SC_int_defintion (std::vector<TOKEN> list);
char SC_chr_defintion (std::vector<TOKEN> list);

#endif
