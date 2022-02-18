#include "include/token-op.hh"

std::vector<std::vector<TOKEN>> tokens = {};
std::size_t TOKEN_make_iniToken () {
    tokens.emplace_back(std::vector<TOKEN> ());
    return tokens.size() - 1;
}

void TOKEN_push_token (std::size_t idx, TType type, std::string vast, int ld) {
    TOKEN newT;
    newT.type = type;
    newT.line_definition = ld;
    newT.value_as_token = vast;
    tokens.at(idx).push_back(newT);
}

void TOKEN_print_tokens_found (std::vector<TOKEN> lineT, std::string nameFUNC) {
    printf("<%d> :: [", lineT.at(0).line_definition);
    for ( TOKEN tkn : lineT ) {
        printf(" %s", tkn.value_as_token.c_str());
    }
    printf(" ] (%s)\n", nameFUNC.c_str());
}

void TOKEN_parser () {
    std::size_t idxTemp = TEMP_make_function_temp("main", 0);
    TEMP *cTemp = TEMP_get_template(idxTemp);
    char type = '-';
    GEN_DATA::GEN_dataSegment();

    for ( std::vector<TOKEN> cToken : tokens ) {
        TOKEN_print_tokens_found(cToken, "main");

        if ( cToken.at(0).type == TType::EXIT_FUNC ) {
            type = SC_exit_funtion(cToken);
            if ( type == 's' ) GEN_EXIT::exit_by_simple_value(cToken, cTemp);
            if ( type == 'i' ) GEN_EXIT::exit_by_variable_val(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::WOUT_FUNC ) {
            type = SC_wout_function(cToken);
            if ( type == 's' ) GEN_WOUT::wout_string(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::INT_RW ) {
            type = SC_int_defintion(cToken);
            if ( type == 'n' ) GEN_VARIABLES::INT_by_number(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::CHR_RW ) {
            type = SC_chr_defintion(cToken);
            if ( type == 'c' ) GEN_VARIABLES::CHR_by_char(cToken, cTemp);
        }


    }

    GEN_DATA::GEN_write_templates();
}
