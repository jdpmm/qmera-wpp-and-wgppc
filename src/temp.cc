#include "include/temp.hh"

std::vector<TEMP> templates = {};
std::string ar_64b [5] = { "%rsi", "%rdx", "%rcx", "%r8" , "%r9"  };
std::string ar_32b [5] = { "%esi", "%edx", "%ecx", "%r8d", "%r9d" };
std::string ar_16b [5] = { "%si" , "%dx" , "%cx" , "%r8w", "%r9w" };
std::string ar_8b  [5] = { "%sil", "%dl" , "%cl" , "%r8b", "%r9b" };

std::size_t TEMP_make_function_temp (std::string fn, int np) {
    TEMP newFT;
    newFT.code               = "";
    newFT.type               = TyTemp::FUNCTION;
    newFT.namefunc           = fn;
    newFT.rbytes             = 0;
    newFT.int_created        = 0;
    newFT.n_parameters       = np;
    newFT.char_created       = 0;
    newFT.rbytes_aux         = 1;
    newFT.last_type          = TVar::INTEGER;

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
    if ( type == TVar::CHARACTER ){
        temp->rbytes += 1;
    }
    else {
        if ( temp->last_type == TVar::CHARACTER ) {
            temp->rbytes = temp->rbytes_aux * 8;
            if ( (int) temp->rbytes <= temp->char_created ) {
                temp->rbytes += 8;
                temp->rbytes_aux += 1;
            }
            temp->rbytes_aux += 1;
        }
        else {
            temp->rbytes += 4;
        }
    }
}
