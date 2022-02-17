#include "include/temp.hh"

std::vector<TEMP> templates = {};

std::size_t TEMP_make_function_temp (std::string fn, int np) {
    TEMP newFT;
    newFT.code               = "";
    newFT.type               = TyTemp::FUNCTION;
    newFT.namefunc           = fn;
    newFT.rbytes             = 0;
    newFT.variables_created  = 0;
    newFT.n_parameters       = np;

    newFT.temp = fn + ":\n"
                 "\tpushq %rbp\n"
                 "\tmovq %rsp, %rbp\n"
                 "%s"
                 "\tleave\n"
                 "\tret\n";
    if ( np == 0 ) {
        FUNC_make_0Pfunction(fn);
    }
    templates.push_back(newFT);
    return templates.size() - 1;
}

TEMP* TEMP_get_template (std::size_t idx) {
    return &templates.at(idx);
}

void TEMP_setpoStack (TEMP* temp, TVar type) {
    if ( !(temp->rbytes % 2) ) {
        if ( type == TVar::INTEGER ) temp->rbytes += 4;
        if ( type == TVar::CHARACTER ) temp->rbytes += 1;
    }
    else {
        if ( type == TVar::INTEGER ) temp->rbytes = temp->variables_created * 4 + 4;
        if ( type == TVar::CHARACTER ) temp->rbytes += 1;
    }
}
