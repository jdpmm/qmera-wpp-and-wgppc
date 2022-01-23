/** This file has been created to parser all tokens into assembly code (GNU Assembly)
 * - Created by jpdmm on 23-01-2022 **/
#ifndef WG___GENERATE_H
#define WG___GENERATE_H

#include "assembly-help.h"

/** To print strings we need definite it in the data section, so to not repeat
 * strings we'll have a vector to save the name of every string declared before
 * to not repeat it and don't spend memory foolishly **/
unsigned int labelCount = 1;
std::vector<std::string> labels;
const std::string labelTemp = ".lbp";

void init_data_segment (FILE* dtS) {
    fprintf(dtS, ".text\n");
    fprintf(dtS, ".section .rodata\n");
    fprintf(dtS, "\t.globl main\n");
    fprintf(dtS, "\t.type main, @function\n");
    fprintf(dtS, "\t.printnum:\n");
    fprintf(dtS, "\t\t.string \"%%d\"\n");
    fprintf(dtS, "\t\t.text\n");
}

std::string set_string_in_data_segment (const std::string &src, FILE *dtS) {
    for (size_t i = 0; i < labels.size(); ++i)
        if ( labels.at(i) == src )
            return labelTemp + std::to_string(i + 1);

    fprintf(dtS, "\t.lbp%d:\n", labelCount);
    fprintf(dtS, "\t\t.string %s\n", src.c_str());
    fprintf(dtS, "\t\t.text\n");

    labels.push_back( src );
    labelCount++;
    return labelTemp + std::to_string(labelCount - 1);
}

void asm_exit_by_number (std::vector<token> *list, temp* Temp) {
    Temp->code += "\tmovl $1, %eax\n"
                  "\tmovl $" + list->at(1).value_as_token + ", %ebx\n"
                  "\tint $0x80\n";
}

void asm_wout_string (const std::string &namelabel, temp *Temp) {
    Temp->code += "\tleaq " + namelabel + "(%rip), %rax\n"
                  "\tmovq %rax, %rdi\n"
                  "\tcall puts@PLT\n"
                  "\tmovl $0, %eax\n";
}

#endif