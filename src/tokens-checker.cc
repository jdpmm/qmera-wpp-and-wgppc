#include "include/tokens-checker.hh"

char SC_exit_funtion (std::vector<TOKEN> list) {
    if ( list.size() <= 2 )                     ERR_tokens_expected("exit");;
    if ( list.at(1).type == TType::NUMBER_V )     return 's';
    if ( list.at(1).type == TType::CHARCTER_V ) return 's';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_wout_function (std::vector<TOKEN> list) {
    if ( list.size() <= 2 )                 ERR_tokens_expected("wout");
    if ( list.at(1).type == TType::STRING_V ) return 's';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_int_defintion (std::vector<TOKEN> list) {
    if ( list.size() <= 4 )                   ERR_tokens_expected("int-definition");
    if ( list.at(1).type != TType::ID )       ERR_tokens_expected("int-definition");
    if ( list.at(2).type != TType::EQUALS_S ) ERR_tokens_expected("int-definition");

    if ( list.at(3).type == TType::NUMBER_V ) return 'n';

    ERR_line_doesnt_make_sense();
    exit(1);
}
