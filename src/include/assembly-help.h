/** This file has been created as a helper to another files which needs some things about
 * assembly code, as registers
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WG___ASSEMBLY_HELP_H
#define WG___ASSEMBLY_HELP_H

#include <iostream>

/** These register are used as arguments to functions, every one of them will be used when there is
 * a function either by GNU Assembly like printf function, or any function declared on wg++ **/
const std::string args_r32b[5] = {"%esi", "%edx", "%ecx", "%r8d", "%r9d"};

#endif