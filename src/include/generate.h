/** This file has been created to parser all tokens into assembly code (GNU Assembly)
 * - Created by jpdmm on 23-01-2022 **/
#ifndef WG___GENERATE_H
#define WG___GENERATE_H

#include "assembly-help.h"

void init_data_segment (FILE* dtS) {
    fprintf(dtS, ".text\n");
    fprintf(dtS, ".section .rodata\n");
    fprintf(dtS, "\t.globl main\n");
    fprintf(dtS, "\t.type main, @function\n");
    fprintf(dtS, "\t.printnum:\n");
    fprintf(dtS, "\t\t.string \"%%d\"\n");
    fprintf(dtS, "\t\t.text\n");
}

void asm_exit_by_number (std::vector<token> *list, temp* Temp) {
    Temp->code += "\tmovl $1, %eax\n"
                  "\tmovl $" + list->at(1).value_as_token + ", %ebx\n"
                  "\tint $0x80\n";
}

#endif