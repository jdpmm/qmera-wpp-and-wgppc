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

#endif
