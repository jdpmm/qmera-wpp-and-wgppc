/** This file has been created to know everything about the variables created in the program
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WG___VARIABLES_H
#define WG___VARIABLES_H

#include <iostream>
#include <vector>

enum varType {
    INTEGER,
    CHARACTER
};

typedef struct {
    /** name      : ...
     * poStack    : Index in the assembly stack
     * type       : ...
     * belongs_to : The function to which this variable belongs **/
    std::string name;
    unsigned int poStack;
    varType type;
    std::string belongs_to;
} variable;
std::vector<variable> variables;

void push_variable (const std::string &name, varType type, unsigned int poStack, const std::string &funcname) {
    variable var;
    var.name = name;
    var.type = type;
    var.belongs_to = funcname;
    var.poStack = poStack;

    variables.push_back(var);
}

variable* get_variable (const std::string &name, varType type, const std::string &defname) {
    variable* findvar = nullptr;
    for (auto & variable : variables) {
        printf("-> %s\n", variable.name.c_str());
        if ( variable.name == name && variable.belongs_to == defname )
            findvar = &variable;
    }

    if ( findvar->type == type ) return findvar;
    else {
        // TODO: check another types
        if ( type == INTEGER ) no_right_type_variable("INTEGER");
    }

    var_doesnt_exits(name, defname);
    return nullptr;
}

#endif