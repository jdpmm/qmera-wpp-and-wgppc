/** This file has been created as a helper to another files which needs some things about
 * assembly code, as registers
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WGPP_ASSEMBLY_HELP_H
#define WGPP_ASSEMBLY_HELP_H

#include <iostream>

/** These register are used as arguments to functions, every one of them will be used when there is
 * a function either by GNU Assembly like printf function, or any function declared on wg++.
 * args_rNB:
 * N = number of
 * B = Bites **/
static std::string args_r32b[5] = {"%esi", "%edx", "%ecx", "%r8d", "%r9d"};
static std::string args_r8b[5] = {"%sil", "%dl", "%cl", "%r8b", "%r9b"};

#endif