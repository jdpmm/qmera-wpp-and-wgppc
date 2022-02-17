#include "include/variables.hh"
std::vector<VARIABLE> variables = {};

void VAR_make_variable (const std::string &vn, const std::string &fb, unsigned int pS, TVar t) {
    if ( (int) VAR_getIdxvar(vn, fb) != -1 ) ERR_overwrite_variable(vn, fb);

    VARIABLE newV;
    newV.varname = vn;
    newV.type = t;
    newV.func_belongs = fb;
    newV.poStack = pS;
    variables.push_back(newV);
}

std::size_t VAR_getIdxvar  (const std::string &varname, const std::string &func) {
    for (std::size_t i = 0; i < variables.size(); ++i)
        if ( variables.at(i).varname == varname && variables.at(i).func_belongs == func )
            return i;
    return -1;
}
