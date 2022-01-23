/** This file has been created to make templates of functions, conditionals, loops
 * and more things that i do not remember now
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___TEMPLATE_H
#define WG___TEMPLATE_H

#include <iostream>
#include <vector>

enum TemplateType {
    DEF
};
typedef struct Temp {
    std::string temp;
    std::string code;
    TemplateType type;

    /* For function templates:
     * def_name : The name of function...
     * bytes4   : Bytes reserved into the stack to save variables
     * np       : How many parameters take the function */
    std::string def_name;
    unsigned int bytes4;
} temp;
std::vector<temp> templates;

#endif