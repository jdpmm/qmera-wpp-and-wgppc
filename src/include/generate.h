/** This file has been created to parser all tokens into assembly code (GNU Assembly)
 * - Created by jpdmm on 23-01-2022 **/
#ifndef WG___GENERATE_H
#define WG___GENERATE_H

#include "assembly-help.h"
#include "variables.h"

/** To print strings we need definite it in the data section, so to not repeat
 * strings we'll have a vector to save the name of every string declared before
 * to not repeat it and don't spend memory foolishly **/
unsigned int labelCount = 1;
std::vector<std::string> labels;
const std::string labelTemp = ".lbp";

void wgpp_arith_function (std::vector<token> *op, temp* Temp, size_t from) {
    /** WGPP arith function:
     * The syntax of this function is:
     * ARITH ( n/v math_op n/v sub n/v ... )
     * where n/v could be a integer number or an integer variable.
     * from parameter indicates where is the first n/v token in the list **/
    Temp->code += "\tmovl $0, %r14d\n";
    variable* thisvariable;
    std::string value_number;
    int idx_type = 0;
    char type_operation = '-';

    while ( op->at(from).type != R_PAR ) {
        if ( !(idx_type % 2) ) {
            thisvariable = nullptr;
            value_number = "";

            if ( op->at(from).type != NUMBER && op->at(from).type != VAR_NAME ) token_expected("NUMBER OR INTEGER VARIABLE");
            if ( op->at(from).type == VAR_NAME )
                thisvariable = get_variable(op->at(from).value_as_token, INTEGER, Temp->def_name);
            else
                value_number = op->at(from).value_as_token;
        }
        else {
            if ( op->at(from).type != MATH_OP ) token_expected("MATH OPERATOR");
            if ( op->at(from).value_as_token == "add" ) type_operation = 'a';
            if ( op->at(from).value_as_token == "sub" ) type_operation = 's';
            if ( op->at(from).value_as_token == "mul" ) type_operation = 'm';
            if ( op->at(from).value_as_token == "div" ) type_operation = 'd';
            if ( op->at(from).value_as_token == "pow" ) type_operation = 'p';
            if ( op->at(from).value_as_token == "mod" ) type_operation = 'o';
        }

        if ( idx_type == 0 ) {
            if ( thisvariable ) Temp->code += "\tmovl -" + std::to_string(thisvariable->poStack) + "(%rbp), %r14d\n";
            else                Temp->code += "\tmovl $" + value_number + ", %r14d\n";
        }

        if ( !(idx_type % 2) ) {
            if ( type_operation == 'a' ) {
                if ( thisvariable ) Temp->code += "\taddl -" + std::to_string(thisvariable->poStack) + "(%rbp), %r14d\n";
                else                Temp->code += "\taddl $" + value_number + ", %r14d\n";
            }
            if ( type_operation == 's' ) {
                if ( thisvariable ) Temp->code += "\tsubl -" + std::to_string(thisvariable->poStack) + "(%rbp), %r14d\n";
                else                Temp->code += "\tsubl $" + value_number + ", %r14d\n";
            }
            if ( type_operation == 'm' ) {
                if ( thisvariable ) Temp->code += "\timull -" + std::to_string(thisvariable->poStack) + "(%rbp), %r14d\n";
                else                Temp->code += "\timull $" + value_number + ", %r14d\n";
            }
            if ( type_operation == 'd' || type_operation == 'o' ) {
                Temp->code += "\tmovl $0, %edx\n"
                              "\tmovl %r14d, %eax\n";
                if ( thisvariable ) Temp->code += "\tmovl -" + std::to_string(thisvariable->poStack) + "(%rbp), %ecx\n";
                else Temp->code += "\tmovl $" + value_number + ", %ecx\n";
                Temp->code += "\tidiv %ecx\n";

                if ( type_operation == 'd' ) Temp->code += "\tmovl %eax, %r14d\n";
                else                         Temp->code += "\tmovl %edx, %r14d\n";
            }
        }

        idx_type++;
        from++;
    }
}


void init_data_segment (FILE* dtS) {
    fprintf(dtS, ".text\n");
    fprintf(dtS, ".section .rodata\n");
    fprintf(dtS, "\t.globl main\n");
    fprintf(dtS, "\t.type main, @function\n");
    fprintf(dtS, "\t.printnum:\n");
    fprintf(dtS, "\t\t.string \"%%d\\n\"\n");
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

void asm_exit_by_integer_variable (const std::string &namevar, temp *Temp) {
    unsigned int poStackvar = get_variable(namevar, INTEGER, Temp->def_name)->poStack;
    Temp->code += "\tmovl $1, %eax\n"
                  "\tmovl -" + std::to_string(poStackvar) + "(%rbp), %ebx\n"
                  "\tint $0x80\n";
}

void asm_wout_string (const std::string &namelabel, temp *Temp) {
    Temp->code += "\tleaq " + namelabel + "(%rip), %rax\n"
                  "\tmovq %rax, %rdi\n"
                  "\tcall puts@PLT\n"
                  "\tmovl $0, %eax\n";
}

void asm_wout_variable (const std::string &namevar, temp* Temp) {
    variable* thisvar = get_variable(namevar, ANY_TYPE, Temp->def_name);
    unsigned int idxStack = thisvar->poStack;

    Temp->code += "\tmovl -" + std::to_string(idxStack) + "(%rbp), %eax\n"
                  "\tmovl %eax, %esi\n";

    if ( thisvar->type == INTEGER ) Temp->code += "\tleaq .printnum(%rip), %rax\n";

    Temp->code += "\tmovq %rax, %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";
}

void asm_make_int_by_number (std::vector<token> *list, temp *Temp) {
    Temp->code += "\tsubq $4, %rsp\n"
                  "\tmovl $" + list->at(3).value_as_token + ", -" + std::to_string(Temp->bytes4) + "(%rbp)\n";

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytes4, Temp->def_name);
    Temp->bytes4 += 4;
}

void asm_make_int_by_int (std::vector<token> *list, temp *Temp) {
    variable* thisvar = get_variable(list->at(3).value_as_token, ANY_TYPE, Temp->def_name);
    unsigned int posStack = thisvar->poStack;
    Temp->code += "\tsubq $4, %rsp\n";

    if ( thisvar->type == INTEGER ) {
        Temp->code += "\tmovl -" + std::to_string(posStack) + "(%rbp), %eax\n"
                      "\tmovl %eax, -" + std::to_string(Temp->bytes4) + "(%rbp)\n";
    }

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytes4, Temp->def_name);
    Temp->bytes4 += 4;
}

void asm_make_int_by_arith (std::vector<token> *list, temp *Temp) {
    wgpp_arith_function(list, Temp, 5);
    Temp->code += "\tsubq $4, %rsp\n";
    Temp->code += "\tmovl %r14d, -" + std::to_string(Temp->bytes4) + "(%rbp)\n";

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytes4, Temp->def_name);
    Temp->bytes4 += 4;
}

#endif
