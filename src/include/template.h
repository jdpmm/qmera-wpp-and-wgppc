/** This file has been created to make templates of functions, conditionals, loops
 * and more things that i do not remember now
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WGPP_TEMPLATE_H
#define WGPP_TEMPLATE_H

#include "assembly-help.h"
#include "variables.h"
#include "functions.h"

enum TemplateType {
    DEF
};

typedef struct Temp {
    std::string temp;
    std::string code;
    TemplateType type;

    /* For function templates:
     * def_name   : The name of function...
     * bytesR     : Bytes reserved into the stack to save variables
     * nv_created : N variables created
     * np         : How many parameters take the function */
    std::string def_name;
    unsigned int bytesR;
    int nv_created;
    int np;
} temp;
std::vector<temp> templates;

size_t make_function_template (std::string defname, int nparam) {
    temp newt;
    newt.type = DEF;
    newt.bytesR = 0;
    newt.nv_created = 0;
    newt.def_name = std::move(defname);
    newt.np = nparam;

    newt.temp = newt.def_name + ":\n"
                                "\tpushq %rbp\n"
                                "\tmovq %rsp, %rbp\n"
                                "%s"
                                "\tleave\n"
                                "\tret\n";
    templates.push_back(newt);

    new_function(newt.def_name, newt.np);
    return templates.size() - 1;
}

void set_parameters_in_function (size_t idxTemp, const std::vector<variable> &types) {
    // TODO
    temp* thisT = &templates.at(idxTemp);
    for (size_t i = 0; i < types.size(); ++i) {}
}

inline temp* get_temp (size_t idx) {
    return &templates.at(idx);
}

void get_poStack_for_this_one (temp *Temp, const std::string &type) {
    if ( (Temp->bytesR % 4) == 0 ) {
        if ( type == "i" ) Temp->bytesR += 4;
        if ( type == "c" ) Temp->bytesR += 1;
    }
    else {
        if ( type == "c" ) Temp->bytesR += 1;
        if ( type == "i" ) Temp->bytesR = 4 * Temp->nv_created + 4;
    }

    Temp->nv_created++;
}

#endif