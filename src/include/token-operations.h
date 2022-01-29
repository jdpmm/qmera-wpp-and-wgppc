/** This file has been created to save all tokens found it and save the parser
 * function, a very useful function
 * - Created to jdpmm on 22-01-2022 **/
#ifndef WGPP_TOKEN_OPERATIONS_H
#define WGPP_TOKEN_OPERATIONS_H

#include "token.h"
#include "template.h"
#include "does-it-make-sense.h"
#include "generate.h"

size_t make_head_token () {
    /* Set a new head, every new head means new line of code which will have
     * N tokens */
    tokenHeads.emplace_back(std::vector<token> ());
    return tokenHeads.size() - 1;
}

void push_token (size_t idx, TokenType type, const std::string &tkn_value_str, int line_definition ) {
    token NewToken;
    NewToken.line_definition = line_definition;
    NewToken.type = type;
    NewToken.value_as_token = tkn_value_str;

    tokenHeads.at(idx).push_back(NewToken);
}

void print_line (std::vector<token> *line_tkns, std::string funcname) {
    /* Prints all tokens found it in every line, this is so useful
     * when there is an error because we show the struct of the line
     * and the line when the error happened */
    printf("%d :: TOKENS <", line_tkns->at(0).line_definition);
    for (auto & token : *line_tkns)
        printf(" %s", token.value_as_token.c_str());
    printf(" > (%s)\n", funcname.c_str());
}

void parser () {
    FILE* codeSegment = fopen("code.s", "w");
    FILE* dataSegment = fopen("data.s", "w");
    init_data_segment(dataSegment);
    char type;

    size_t currenTemp_idx = make_function_template("main", 0);
    for (auto & tokenHead : tokenHeads) {
        std::vector<token> *currntLine = &tokenHead;
        temp* currnTemp = get_temp(currenTemp_idx);
        print_line(currntLine, currnTemp->def_name);
        type = '-';

        if ( currntLine->at(0).type == EXIT_FUNC ) {
            type = check_exit(currntLine);
            if ( type == 'n' ) asm_exit_by_number(currntLine, currnTemp);
            if ( type == 'v' ) asm_exit_by_integer_variable(currntLine->at(1).value_as_token, currnTemp);
            if ( type == 'm' ) asm_exit_by_arithmetic_op(currntLine, currnTemp);
        }

        if ( currntLine->at(0).type == WOUT_FUNC ) {
            type = check_wout(currntLine);
            if ( type == 's' ) {
                std::string labelString = set_string_in_data_segment(currntLine->at(1).value_as_token, dataSegment);
                asm_wout_string(labelString, currnTemp);
            }
            if ( type == 'v' ) asm_wout_variable(currntLine->at(1).value_as_token, currnTemp);
            if ( type == 'm' ) asm_wout_arithmetic_op(currntLine, currnTemp);
        }

        if ( currntLine->at(0).type == INT_RW ) {
            type = check_int_declaration(currntLine, currnTemp->def_name);
            if ( type == 'n' ) asm_make_int_by_number(currntLine, currnTemp);
            if ( type == 'v' ) asm_make_int_by_var(currntLine, currnTemp);
            if ( type == 'm' ) asm_make_int_by_arith(currntLine, currnTemp);
        }

        if ( currntLine->at(0).type == CHG_CALL ) {
            type = check_chg(currntLine, currnTemp->def_name);
            if ( type == 'n' ) wgpp_chg_int_by_number(currntLine, currnTemp);
            if ( type == 'v' ) wgpp_chg_int_by_int(currntLine, currnTemp);
            if ( type == 'm' ) wgpp_chg_int_by_arithmetic(currntLine, currnTemp);
        }

        if ( currntLine->at(0).type == PRINTF_FUNC ) {
            check_printf(currntLine);
            asm_printf_function(currntLine, currnTemp, dataSegment);
        }

        if ( currntLine->at(0).type == INT_OP ) {
            check_int_op(currntLine);
            asm_integer_operation(currntLine, currnTemp);
        }

        if ( currntLine->at(0).type == CHR_RW ) {
            type = check_chr_declaration(currntLine);
            if ( type == 'c' ) asm_make_chr_by_character(currntLine, currnTemp);
            if ( type == 'v' ) asm_make_chr_by_var(currntLine, currnTemp);
        }

    }

    fclose(dataSegment);
    for (auto & temp : templates) {
        fprintf(codeSegment, temp.temp.c_str(), temp.code.c_str());
    }
    fclose(codeSegment);
}

#endif
