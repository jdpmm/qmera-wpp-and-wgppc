#include "include/tokens-checker.hh"

char SC_exit_funtion (std::vector<TOKEN> list) {
    if ( list.size() <= 2 )                      ERR_tokens_expected("exit");;
    if ( list.at(1).type == TType::CONSTANT )    return 's';
    if ( list.at(1).type == TType::ID_VARIABLE ) return 'v' ;

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_wout_function (std::vector<TOKEN> list) {
    if ( list.size() <= 2 )                      ERR_tokens_expected("wout");
    if ( list.at(1).type == TType::STRING )      return 's';
    if ( list.at(1).type == TType::ID_VARIABLE ) return 'v';
    if ( list.at(1).type == TType::ARITH_CALL )  return 'a';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_int_defintion (std::vector<TOKEN> list) {
    if ( list.size() <= 4 )                      ERR_tokens_expected("int-definition");
    if ( list.at(1).type != TType::ID_VARIABLE ) ERR_tokens_expected("int-definition");
    if ( list.at(2).type != TType::EQUALS_S )    ERR_tokens_expected("int-definition");

    if ( list.at(3).type == TType::CONSTANT )    return 'c';
    if ( list.at(3).type == TType::ID_VARIABLE ) return 'v';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_chr_defintion (std::vector<TOKEN> list) {
    if ( list.size() <= 4 )                      ERR_tokens_expected("chr-definition");
    if ( list.at(1).type != TType::ID_VARIABLE ) ERR_tokens_expected("chr-definition");
    if ( list.at(2).type != TType::EQUALS_S )    ERR_tokens_expected("chr-definition");

    if ( list.at(3).type == TType::CONSTANT )    return 'c';
    if ( list.at(3).type == TType::ID_VARIABLE ) return 'v';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_ptr_defintion (std::vector<TOKEN> list) {
    if ( list.size() <= 4 )                     ERR_tokens_expected("ptr-definition");
    if ( list.at(1).type != TType::ID_PTR )     ERR_tokens_expected("ptr-definition");
    if ( list.at(2).type != TType::EQUALS_S )   ERR_tokens_expected("ptr-definition");

    if ( list.at(3).type == TType::ID_ADDRESS ) return 'a';
    if ( list.at(3).type == TType::ID_PTR )     return 'p';

    ERR_line_doesnt_make_sense();
    return '-';
}

void SC_printf_function (std::vector<TOKEN> list) {
    if ( list.size() <= 2 )                   ERR_tokens_expected("printf");
    if ( list.at(1).type != TType::STRING )   ERR_line_doesnt_make_sense();
}

char SC_chg_fucntion (std::vector<TOKEN> list, char *ttchg) {
    if ( list.size() <= 2 )                      ERR_tokens_expected("CHG");
    if ( list.at(1).type == TType::ID_VARIABLE ) *ttchg = 'v';
    else                                         ERR_tokens_expected("CHG");

    if ( list.at(2).type == TType::ID_VARIABLE ) return 'v';
    if ( list.at(2).type == TType::CONSTANT )    return 'c';

    ERR_line_doesnt_make_sense();
    return '-';
}

char SC_int_function (std::vector<TOKEN> list, char *tvintf) {
    if ( list.size() <= 2 )                      ERR_tokens_expected("INTF");
    if ( list.at(1).type == TType::ID_VARIABLE ) *tvintf = 'v';

    if ( list.at(0).value_as_token == "INC" ) return 'i';
    if ( list.at(0).value_as_token == "DEC" ) return 'd';
    if ( list.at(0).value_as_token == "NEG" ) return 'n';

    ERR_line_doesnt_make_sense();
    return '-';
}
