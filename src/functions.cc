#include "include/functions.hh"

std::vector<FUNCTION> functions = {};
void FUNC_make_0Pfunction (const std::string &fn) {
    FUNCTION newF;
    newF.namefunction = fn;
    newF.n_paramters = 0;

    functions.push_back(newF);
}

void FUNC_make_NPfunction (const std::string &fn, int np, std::map<std::string, TVar> t) {
    FUNCTION newF;
    newF.namefunction = fn;
    newF.n_paramters = np;
    newF.types = t;

    functions.push_back(newF);
}

FUNCTION FUNC_get_function (const std::string &fn) {
    std::size_t idxF = FUNC_get_idx_function(fn);
    if ( (int) idxF == -1 ) ERR_function_doesnt_exist(fn);
    return functions.at(idxF);
}

std::size_t FUNC_get_idx_function (const std::string &fn) {
    for (std::size_t i = 0; i < functions.size(); ++i)
        if ( functions.at(i).namefunction == fn )
            return i;
    return -1;
}
