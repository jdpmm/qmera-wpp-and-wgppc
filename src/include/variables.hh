/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_VARIABLES_HH
#define WGPP_PROGRAMMING_LANGUAGE_VARIABLES_HH

#include "err.hh"
#include <vector>
enum class TVar {
    INTEGER,
    CHARACTER,
    POINTER
};

struct VARIABLE {
    // To any variable type
    std::string varname;
    TVar type;
    std::string func_belongs;
    unsigned int poStack;
    std::string varname_address;

    // To pointer variables
    unsigned int poStack_varpointing;
    TVar type_varpointing;
    unsigned int lvlptr;
};
extern std::vector<VARIABLE> variables;

void VAR_make_variable         (const std::string &vn, const std::string &fb, unsigned int pS, TVar t);
void VAR_make_pointer (const std::string &np, const std::string &fb, unsigned int pSp, unsigned int pSv, TVar typeV, int lvlp);
VARIABLE VAR_get_variable      (const std::string &varname, const std::string &func);
VARIABLE* VAR_get_variable_ptr (const std::string &varname, const std::string &func);
std::size_t VAR_getIdxvar      (const std::string &varname, const std::string &func);

#endif
