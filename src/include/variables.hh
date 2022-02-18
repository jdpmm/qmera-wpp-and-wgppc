/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_VARIABLES_HH
#define WGPP_PROGRAMMING_LANGUAGE_VARIABLES_HH

#include "err.hh"
#include <vector>
enum class TVar {
    INTEGER,
    CHARACTER
};

struct VARIABLE {
    std::string varname;
    TVar type;
    std::string func_belongs;
    unsigned int poStack;
};
extern std::vector<VARIABLE> variables;

void VAR_make_variable    (const std::string &vn, const std::string &fb, unsigned int pS, TVar t);
VARIABLE VAR_get_variable (const std::string &varname, const std::string &func);
std::size_t VAR_getIdxvar (const std::string &varname, const std::string &func);

#endif
