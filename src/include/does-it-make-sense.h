/** This file has been created to check the syntax in the code
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WGPP_DOES_IT_MAKE_SENSE_H
#define WGPP_DOES_IT_MAKE_SENSE_H

#include "token.h"
#include "err-report.h"
#include "variables.h"

char check_exit (std::vector<token> *list) {
    /** The exit operation could have three modes:
     * - Exit by one integer number
     * - Exit by one integer variable value
     * - Exit by one arithmetic operation **/
    if ( list->size() <= 2 ) tokens_lost();
    if ( list->at(1).type == NUMBER ) return 'n';
    if ( list->at(1).type == VAR_NAME ) return 'v';
    if ( list->at(1).type == ARITH_CALL ) return 'm';

    nonsense();
    return '-';
}

char check_wout (std::vector<token> *list) {
    /** Wout operation (wg++ output, yeah, like "cout" by C++)
     * This operation at this moment can have three modes:
     * - Print a simple string
     * - Print a variable value
     * - Print an arithmetic operation **/
    if ( list->size() <= 2 ) tokens_lost();
    if ( list->at(1).type == STRING ) return 's';
    if ( list->at(1).type == VAR_NAME ) return 'v';
    if ( list->at(1).type == ARITH_CALL ) return 'm';

    nonsense();
    return '-';
}

char check_int_declaration (std::vector<token> *list, const std::string &defname) {
    /** Integer variables declaration can have three modes:
     * - Create an integer with a constant value
     * - Copy the value of another integer variable
     * - The value will be given by an arithmetic operation **/
    variable* var = get_variable_without_error(list->at(1).value_as_token, INTEGER, defname);
    if ( var ) trying_to_overwrite_variable();

    if ( list->size() <= 4 ) tokens_lost();
    if ( list->at(1).type != VAR_NAME ) token_expected("NAME VARIABLE");
    if ( list->at(2).type != EQUALS_S ) token_expected("EQUALS SYMBOL");
    if ( list->at(3).type == NUMBER ) return 'n';
    if ( list->at(3).type == VAR_NAME ) return 'v';
    if ( list->at(3).type == ARITH_CALL ) return 'm';

    nonsense();
    return '-';
}

char check_chg (std::vector<token> *list, const std::string &defname) {
    /** CHG operation:
     * Allow you change the value of one variable
     * - The variable and the new value must has the same datatype! **/
    if ( list->size() <= 3 ) tokens_lost();
    if ( list->at(1).type != VAR_NAME ) token_expected("VARIABLE NAME");
    if ( list->at(2).type == NUMBER ) return 'n';
    if ( list->at(2).type == VAR_NAME ) return 'v';
    if ( list->at(2).type == ARITH_CALL ) return 'm';

    nonsense();
    return '-';
}

void check_printf (std::vector<token> *list) {
    /** printf:
     * Allow you print 5 variables at the same time with text in itself, like printf C function
     * - The unique next token after "printf" token must be a string **/
    if ( list->size() <= 2 ) tokens_lost();
    if ( list->at(1).type != STRING ) token_expected("STRING");
}

void check_int_op (std::vector<token> *list) {
    /** Integer operations:
     * It's the same than "--" or "++" in some high level programming languages
     * but in this case isn't with these symbols, also i added a new operation
     * which is "neg" and is: n = n * - 1; :D **/
    if ( list->size() <= 2 ) tokens_lost();
    if ( list->at(1).type != VAR_NAME  ) token_expected("INTEGER VARIABLE");
}

char check_chr_declaration (std::vector<token> *list) {
    // chr $f$ = 5;
    if ( list->size() <= 4 ) tokens_lost();
    if ( list->at(1).type != VAR_NAME ) token_expected("NAME VARIABLE");
    if ( list->at(2).type != EQUALS_S ) token_expected("EQUALS SYMBOL");
    if ( list->at(3).type == CHR_VAL ) return 'c';

    nonsense();
    return '-';
}

#endif
