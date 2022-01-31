/** This file has been created to parser all tokens into assembly code (GNU Assembly)
 * - Created by jpdmm on 23-01-2022 **/
#ifndef WGPP_GENERATE_H
#define WGPP_GENERATE_H

#include "assembly-help.h"
#include "token.h"
#include "template.h"
#include "variables.h"
#include "util.h"


/** To print strings we need definite them in the data section, so to not repeat
* strings we'll have a vector to save the name of every string declared before.
* it causes don't spend memory foolishly **/
unsigned int labelCount = 1;
std::vector<std::string> labels;
static const std::string labelTemp = ".lbp";

/** ------------------------------------------------------------------------------------------------
 * WG++ functions:                                                                                 |
 * These functions has been declared to make the necessary code in assembly to some operations     |
 * like arithmetic or change the value of one variable.                                            |
 * The WG++ functions are the tokens which whose value is a word with all letters are capitalized  |
 * ------------------------------------------------------------------------------------------------| */
void wgpp_arith_function (std::vector<token> *op, temp* Temp, size_t from) {
    /** WGPP arith function:
     * The syntax of this function is:
     * ARITH ( n/v math_op n/v sub n/v ... )
     * where n/v could be an integer number or an integer variable.
     * "from" parameter indicates where is the first n/v token in the list **/
    Temp->code += "\tmovl $0, %r14d\n";
    variable* thisvariable;
    std::string value_number;
    int idx_type = 0;
    char type_operation = '-';

    /** While the token isn't a ")" token means still don't end the operation
     * idx_type variable indicates if the current token (indicate by from) must be a n/v or a mathematical operator since
     * if idx_type is odd means the current token must be a mathematical operator because:
     * op = {..., ARIRH, (, n/v, add ..., ), ...}
     *                       ^
     *                       |
     *                       At the start "from" starts here and for per token "from" variable and "idx_type" increases
     *                       their value by 1, so at the start:
     *                          - idx_type = 0 -> It means the token is a n/v since 0 is even
     *                       but in the next iteration 1 isn't even so the current token must be a mathematical operator and the process
     *                       is repeated until found ")" token.
     * When idx_type is even we must set the value of the number or integer variable.
     * When idx_type is odd we must set the value of the mathematical operation. **/
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

        /** If idx_type is 0 it means this is the first iteration, when is the first iteration
         * the current token is a n/v so we must set that value as the main value for the operation:
         * 4 add 5 sub 1
         * \
         *  This value will be the base for whole operation **/
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

void wgpp_chg_function (std::vector<token> *list, temp *Temp, varType var_type, char chg_type) {
    // TODO: Make it with another types
    variable* vto_change = nullptr;
    if ( var_type == INTEGER || var_type == CHARACTER ) {
        vto_change = get_variable(list->at(1).value_as_token, var_type, Temp->def_name);
    }

    if ( var_type == INTEGER ) {
        /** CHG function with integers:
         * An integer variable could be changed by:
         * - 'c' -> constant   == CHG $v$ 4;             -> v = 4
         * - 'v' -> variable   == CHG $y$ $v$;           -> y = v
         * - 'm' -> arithmetic == CHG $d$ ARITH(3 add 3) -> d = 6 **/
        if ( chg_type == 'c' ) {
            Temp->code += "\tmovl $" + list->at(2).value_as_token + ", -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
        }
        if ( chg_type == 'v' ) {
            variable* vto_copy = get_variable(list->at(2).value_as_token, ANY_TYPE, Temp->def_name);
            if ( vto_copy->type == INTEGER ) {
                Temp->code += "\tmovl -" + std::to_string(vto_copy->poStack) + "(%rbp), %eax\n"
                              "\tmovl %eax, -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
            }
            if ( vto_copy->type == CHARACTER ) {
                Temp->code += "\tmovb -" + std::to_string(vto_copy->poStack) + "(%rbp), %al\n"
                              "\tmovb %al, -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
            }
        }
        if ( chg_type == 'm' ) {
            wgpp_arith_function(list, Temp, 4);
            Temp->code += "\tmovl %r14d, -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
        }
    }

    else if ( var_type == CHARACTER ) {
        if ( chg_type == 'c' ) {
            Temp->code += "\tmovb $" + list->at(2).value_as_token + ", -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
        }
        if ( chg_type == 'v' ) {
            variable* vto_copy = get_variable(list->at(2).value_as_token, ANY_TYPE, Temp->def_name);
            if ( vto_copy->type == CHARACTER ) {
                Temp->code += "\tmovb -" + std::to_string(vto_copy->poStack) + "(%rbp), %al\n"
                              "\tmovb %al, -" + std::to_string(vto_change->poStack) + "(%rbp)\n";
            }
        }

    }
}

void wgpp_integer_operation (std::vector<token> *list, temp *Temp) {
    unsigned int idxStack = get_variable(list->at(1).value_as_token, INTEGER, Temp->def_name)->poStack;
    if ( list->at(0).value_as_token == "INC" )
        Temp->code += "\tincl -" + std::to_string(idxStack) + "(%rbp)\n";
    else if ( list->at(0).value_as_token == "DEC" )
        Temp->code += "\tdecl -" + std::to_string(idxStack) + "(%rbp)\n";
    else
        Temp->code += "\tnegl -" + std::to_string(idxStack) + "(%rbp)\n";
}

/** ------------------------------------------------------------------------------------------------
 * Data space:                                                                                     |
 * These functions has been declared to write directly on the dataSegment file or on the           |
 * codeSegment file.                                                                               |
 * ------------------------------------------------------------------------------------------------| */
void init_data_segment (FILE* dtS) {
    fprintf(dtS, ".text\n");
    fprintf(dtS, ".section .rodata\n");
    fprintf(dtS, "\t.globl main\n");
    fprintf(dtS, "\t.type main, @function\n");
    fprintf(dtS, "\t.printnum:\n");
    fprintf(dtS, "\t\t.string \"%%d\\n\"\n");
    fprintf(dtS, "\t\t.text\n");
    fprintf(dtS, "\t.printchr:\n");
    fprintf(dtS, "\t\t.string \"%%c\\n\"\n");
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

/** ------------------------------------------------------------------------------------------------
 * exit function:                                                                                  |
 * These functions has been declared to set a exit operation in assembly code                      |
 * ------------------------------------------------------------------------------------------------| */
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

void asm_exit_by_arithmetic_op (std::vector<token> *list, temp *Temp) {
    wgpp_arith_function(list, Temp, 3);
    Temp->code += "\tmovl $1, %eax\n"
                  "\tmovl %r14d, %ebx\n"
                  "\tint $0x80\n";
}

/** ------------------------------------------------------------------------------------------------
 * wout function:                                                                                  |
 * These functions has been declared to set the necessary code in assembly to be able              |
 * of print any datatype on wg++ programming language                                              |
 * ------------------------------------------------------------------------------------------------| */
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
    if ( thisvar->type == CHARACTER ) Temp->code += "\tleaq .printchr(%rip), %rax\n";

    Temp->code += "\tmovq %rax, %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";
}

void asm_wout_arithmetic_op (std::vector<token> *list, temp *Temp) {
    wgpp_arith_function(list, Temp, 3);
    Temp->code += "\tmovl %r14d, %eax\n"
                  "\tmovl %eax, %esi\n"
                  "\tleaq .printnum(%rip), %rax\n"
                  "\tmovq %rax, %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";
}

/** ------------------------------------------------------------------------------------------------
 * integer declaration:                                                                            |
 * These functions has been declared to the creation of integer variables with assembly code       |
 * these integer variables are of 32 bits.                                                         |
 * ------------------------------------------------------------------------------------------------| */
void asm_make_int_by_number (std::vector<token> *list, temp *Temp) {
    get_poStack_for_this_one(Temp, "i");
    Temp->code += "\tsubq $4, %rsp\n"
                  "\tmovl $" + list->at(3).value_as_token + ", -" + std::to_string(Temp->bytesR) + "(%rbp)\n";

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytesR, Temp->def_name);
}

void asm_make_int_by_var (std::vector<token> *list, temp *Temp) {
    get_poStack_for_this_one(Temp, "i");

    variable* varto_copy = get_variable(list->at(3).value_as_token, ANY_TYPE, Temp->def_name);
    unsigned int posStack = varto_copy->poStack;
    Temp->code += "\tsubq $4, %rsp\n";

    if ( varto_copy->type == INTEGER || varto_copy->type == CHARACTER ) {
        Temp->code += "\tmovl -" + std::to_string(posStack) + "(%rbp), %eax\n"
                      "\tmovl %eax, -" + std::to_string(Temp->bytesR) + "(%rbp)\n";
    }

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytesR, Temp->def_name);
}

void asm_make_int_by_arith (std::vector<token> *list, temp *Temp) {
    get_poStack_for_this_one(Temp, "i");
    wgpp_arith_function(list, Temp, 5);
    Temp->code += "\tsubq $4, %rsp\n";
    Temp->code += "\tmovl %r14d, -" + std::to_string(Temp->bytesR) + "(%rbp)\n";

    push_variable(list->at(1).value_as_token, INTEGER, Temp->bytesR, Temp->def_name);
}

/** ------------------------------------------------------------------------------------------------
 * printf function:                                                                                |
 * This function has been declared to set the values in the printf function, the maximum number of |
 * variables into this function is 5. the syntax is:                                               |
 * printf "str $variable$ dwefrgt $anothervar$ ...";                                               |
 * ------------------------------------------------------------------------------------------------| */
void asm_printf_function (std::vector<token> *list, temp *Temp, FILE *dataS) {
    std::string str_to_asm;
    std::string format_str = list->at(1).value_as_token;
    size_t idx = 0;
    std::string var_name;
    variable* thisvar = nullptr;
    std::vector<variable> vars;

    while ( format_str[idx] != '\0' ) {
        // TODO: with another types
        if ( format_str[idx] == '$' ) {
            var_name = get_name_of(format_str, idx, '$', false);
            thisvar = get_variable(var_name, ANY_TYPE, Temp->def_name);
        }
        if ( thisvar ) {
            if ( thisvar->type == INTEGER ) {
                str_to_asm += "%d";
                idx += var_name.size();
            }
            if ( thisvar->type == CHARACTER ) {
                str_to_asm += "%c";
                idx += var_name.size();
            }

            vars.push_back(*thisvar);
            thisvar = nullptr;
        }
        if ( format_str[idx] == '%' ) {
            str_to_asm += "%%";
            idx++;
        }

        str_to_asm += format_str[idx];
        idx++;
    }
    thisvar = nullptr;
    free(thisvar);

    if ( vars.size() >= 6 ) printf_err();
    std::string labelprint = set_string_in_data_segment(str_to_asm, dataS);
    for (size_t i = 0; i < vars.size(); ++i) {
        if ( vars.at(i).type == INTEGER )
            Temp->code += "\tmovl -" + std::to_string(vars.at(i).poStack) + "(%rbp), " + args_r32b[i] + "\n";
        if ( vars.at(i).type == CHARACTER )
            Temp->code += "\tmovsbl -" + std::to_string(vars.at(i).poStack) + "(%rbp), " + args_r32b[i] + "\n";
    }

    Temp->code += "\tleaq " + labelprint + "(%rip), %rax\n"
                                           "\tmovq %rax, %rdi\n"
                                           "\tmovl $0, %eax\n"
                                           "\tcall printf@PLT\n"
                                           "\tmovl $0, %eax\n";
}

/** ------------------------------------------------------------------------------------------------
 * character declaration:                                                                          |
 * These functions has been declared to the creation of character variables with assembly code     |
 * ------------------------------------------------------------------------------------------------| */
void asm_make_chr_by_character (std::vector<token> *list, temp *Temp) {
    get_poStack_for_this_one(Temp, "c");
    Temp->code += "\tsubq $4, %rsp\n"
                  "\tmovb $" + list->at(3).value_as_token + ", -" + std::to_string(Temp->bytesR) + "(%rbp)\n";

    push_variable(list->at(1).value_as_token, CHARACTER, Temp->bytesR, Temp->def_name);
}

void asm_make_chr_by_var (std::vector<token> *list, temp *Temp) {
    get_poStack_for_this_one(Temp, "c");
    variable *varto_copy = get_variable(list->at(3).value_as_token, ANY_TYPE, Temp->def_name);
    unsigned int idxStack = varto_copy->poStack;
    Temp->code += "\tsubq $4, %rsp\n";

    if ( varto_copy->type == CHARACTER ) {
        Temp->code += "\tmovb -" + std::to_string(idxStack) + "(%rbp), %al\n"
                      "\tmovb %al, -" + std::to_string(Temp->bytesR) + "(%rbp)\n";
    }
    if ( varto_copy->type == INTEGER ) {
        Temp->code += "\tmovl -" + std::to_string(idxStack) + "(%rbp), %eax\n"
                      "\tmovl %eax, -" + std::to_string(Temp->bytesR) + "(%rbp)\n";
    }

    push_variable(list->at(1).value_as_token, CHARACTER, Temp->bytesR, Temp->def_name);
}


#endif
