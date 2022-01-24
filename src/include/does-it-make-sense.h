/** This file has been created to check the syntax in the code
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WG___DOES_IT_MAKE_SENSE_H
#define WG___DOES_IT_MAKE_SENSE_H

#include "token.h"
#include "err-report.h"

char check_exit (std::vector<token> *list) {
    if ( list->size() <= 2 )               tokens_lost();
    if ( list->at(1).type == NUMBER )   return 'n';
    if ( list->at(1).type == VAR_NAME ) return 'v';

    nonsense();
    return '-';
}

char check_wout (std::vector<token> *list) {
    if ( list->size() <= 2 )               tokens_lost();
    if ( list->at(1).type == STRING )   return 's';
    if ( list->at(1).type == VAR_NAME ) return 'v';

    nonsense();
    return '-';
}

char check_int_declaration (std::vector<token> *list) {
    // int $name$ = 45;
    if ( list->size() <= 4 )               tokens_lost();
    if ( list->at(1).type != VAR_NAME ) token_expected("NAME VARIABLE");
    if ( list->at(2).type != EQUALS_S ) token_expected("EQUALS SYMBOL");
    if ( list->at(3).type == NUMBER )   return 'n';

    nonsense();
    return '-';
}

#endif
