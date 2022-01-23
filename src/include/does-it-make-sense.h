/** This file has been created to check the syntax in the code
 * - Created by jdpmm on 23-01-2022 **/
#ifndef WG___DOES_IT_MAKE_SENSE_H
#define WG___DOES_IT_MAKE_SENSE_H

#include "token.h"
#include "err-report.h"

char check_exit (std::vector<token> *list) {
    if ( list->size() <= 2 )             no_make_sense();
    if ( list->at(1).type == NUMBER ) return 'n';

    token_expected("NUMBER");
    return '-';
}

#endif
