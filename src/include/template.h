/** This file has been created to make templates of functions, conditionals, loops
 * and more things that i do not remember now
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WGPP_TEMPLATE_H
#define WGPP_TEMPLATE_H

#include "assembly-help.h"
#include "variables.h"

enum TemplateType {
    DEF
};

typedef struct Temp {
    std::string temp;
    std::string code;
    TemplateType type;

    /* For function templates:
     * def_name : The name of function...
     * bytesR   : Bytes reserved into the stack to save variables
     * np       : How many parameters take the function */
    std::string def_name;
    unsigned int bytesR;
    int np;
} temp;
std::vector<temp> templates;

size_t make_function_template (std::string defname, int nparam) {
    temp newt;
    newt.type = DEF;
    newt.bytesR = 4;
    newt.def_name = std::move(defname);
    newt.np = nparam;

    newt.temp = newt.def_name + ":\n"
                                "\tpushq %rbp\n"
                                "\tmovq %rsp, %rbp\n"
                                "%s"
                                "\tleave\n"
                                "\tret\n";
    templates.push_back(newt);
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

#endif
