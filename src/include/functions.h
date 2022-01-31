/** This file has been created to know everything about each function created on
 * wg++ code
 * - Created by jdpmm on 30-01-2022 **/
#ifndef WGPP_FUNCTIONS_H
#define WGPP_FUNCTIONS_H

#include "err-report.h"
#include "variables.h"
#include <iostream>
#include <vector>

typedef struct FUNC {
    std::string name;
    unsigned int n_parameters;
    std::vector<varType> Ptypes;

} func;
std::vector<func> functions;

void new_function (const std::string &name, unsigned int n_parameters, const std::vector<varType> &p_types={}) {
    for ( func & f : functions )
        if ( f.name == name )
            trying_to_overwrite_function();

    func newfunction;
    newfunction.name = name;
    newfunction.n_parameters = n_parameters;
    newfunction.Ptypes = p_types;

    functions.push_back(newfunction);
}

func* find_a_function (const std::string &name) {
    func *findfunc = nullptr;
    for ( func & f : functions ) {
        if ( f.name == name ) {
            findfunc = &f;
            break;
        }
    }

    if ( !findfunc ) def_doesnt_exits(name);
    return findfunc;
}

#endif