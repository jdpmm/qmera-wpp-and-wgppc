#include "include/variables.hh"
std::vector<VARIABLE> variables = {};

void VAR_make_variable (const std::string &vn, const std::string &fb, unsigned int pS, TVar t) {
    if ( (int) VAR_getIdxvar(vn, fb) != -1 ) ERR_overwrite_variable(vn, fb);

    std::string nameAdress = vn;
    nameAdress[0] = '&';
    nameAdress[nameAdress.size() - 1] = '&';

    VARIABLE newV;
    newV.varname = vn;
    newV.type = t;
    newV.func_belongs = fb;
    newV.poStack = pS;
    newV.varname_address = nameAdress;
    variables.push_back(newV);
}

void VAR_make_pointer (const std::string &np, const std::string &fb, unsigned int pSp, unsigned int pSv, TVar typeV, int lvlp) {
    if ( (int) VAR_getIdxvar(np, fb) != -1 ) ERR_overwrite_variable(np, fb);
    std::string nameAdress = np;
    nameAdress[0] = '&';
    nameAdress[nameAdress.size() - 1] = '&';

    VARIABLE newP;
    newP.varname = np;
    newP.type = TVar::POINTER;
    newP.func_belongs = fb;
    newP.poStack = pSp;
    newP.varname_address = nameAdress;

    newP.poStack_varpointing = pSv;
    newP.type_varpointing = typeV;
    newP.lvlptr = lvlp;
    variables.push_back(newP);
}

std::size_t VAR_getIdxvar  (const std::string &varname, const std::string &func) {
    for (std::size_t i = 0; i < variables.size(); ++i) {
        if ( variables.at(i).varname == varname && variables.at(i).func_belongs == func )
            return i;
        if ( variables.at(i).varname_address == varname && variables.at(i).func_belongs == func )
            return i;
    }

    return -1;
}

VARIABLE VAR_get_variable (const std::string &varname, const std::string &func) {
    std::size_t idx = VAR_getIdxvar(varname, func);
    if ( (int) idx == -1 ) ERR_variable_doesnt_exist(varname, func);

    return variables.at(idx);
}

VARIABLE* VAR_get_variable_ptr (const std::string &varname, const std::string &func) {
    std::size_t idx = VAR_getIdxvar(varname, func);
    if ( (int) idx == -1 ) ERR_variable_doesnt_exist(varname, func);

    return &variables.at(idx);
}
