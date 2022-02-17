/** Crated by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_FUCNTIONS_HH
#define WGPP_PROGRAMMING_LANGUAGE_FUCNTIONS_HH

#include "variables.hh"
#include "err.hh"
#include <map>

struct FUNCTION {
    std::string                 namefunction;
    int                         n_paramters;
    std::map<std::string, TVar> types;
};
extern std::vector<FUNCTION> functions;

void     FUNC_make_0Pfunction  (const std::string &fn);
void     FUNC_make_NPfunction  (const std::string &fn, int np, std::map<std::string, TVar> t);
FUNCTION FUNC_get_function     (const std::string &fn);
std::size_t   FUNC_get_idx_function (const std::string &fn);

#endif
