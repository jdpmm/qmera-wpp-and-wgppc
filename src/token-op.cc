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
    char typeAux = '-';
    GEN_DATA::DATA_dataSegment();

    for ( std::vector<TOKEN> cToken : tokens ) {
        // TODO: Possible cToken empty
        TOKEN_print_tokens_found(cToken, "main");
        cTemp->code += "\t# < " + std::to_string(cToken.at(0).line_definition) + " > #\n";

        if ( cToken.at(0).type == TType::EXIT_FUNC ) {
            type = SC_exit_funtion(cToken);
            if ( type == 's' ) GEN_EXIT::EXIT_by_simple_value(cToken, cTemp);
            if ( type == 'v' ) GEN_EXIT::EXIT_by_var_val(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::WOUT_FUNC ) {
            type = SC_wout_function(cToken);
            if ( type == 's' ) GEN_WOUT::WOUT_string(cToken, cTemp);
            if ( type == 'v' ) GEN_WOUT::WOUT_var(cToken, cTemp);
            if ( type == 'a' ) GEN_WOUT::WOUT_arith(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::INT_RW ) {
            type = SC_int_defintion(cToken);
            if ( type == 'c' ) GEN_VARIABLES::VAR_int_by_constant_value(cToken, cTemp);
            if ( type == 'v' ) GEN_VARIABLES::VAR_copy_value_vTv(cToken, cTemp, TVar::INTEGER);
        }

        if ( cToken.at(0).type == TType::CHR_RW ) {
            type = SC_chr_defintion(cToken);
            if ( type == 'c' ) GEN_VARIABLES::VAR_chr_by_constant_value(cToken, cTemp);
            if ( type == 'v' ) GEN_VARIABLES::VAR_copy_value_vTv(cToken, cTemp, TVar::CHARACTER);
        }

        if ( cToken.at(0).type == TType::PRINTF_FUNC ) {
            SC_printf_function(cToken);
            GEN_PRINTF::PRINTF_call(cToken, cTemp);
        }

        if ( cToken.at(0).type == TType::CHG_FUNC ) {
            type = SC_chg_fucntion(cToken, &typeAux);
            if ( typeAux == 'v' ) {
                if ( type == 'c' ) GEN_CHG::CHG_varto_const(cToken, cTemp);
                if ( type == 'v' ) GEN_CHG::CHG_varto_var(cToken, cTemp);
            }
        }

        if ( cToken.at(0).type == TType::INT_FUNC ) {
            type = SC_int_function(cToken, &typeAux);
            if ( typeAux == 'v' ) {
                VARIABLE thisV = VAR_get_variable(cToken.at(1).value_as_token, cTemp->namefunc);
                if ( thisV.type != TVar::INTEGER ) ERR_type_requierd("INTEGER");
                if ( type == 'i' ) GEN_INTF::INTF_incvar(thisV.poStack, cTemp);
                if ( type == 'd' ) GEN_INTF::INTF_decvar(thisV.poStack, cTemp);
                if ( type == 'n' ) GEN_INTF::INTF_negvar(thisV.poStack, cTemp);
            }
        }

        if ( cToken.at(0).type == TType::PTR_RW ) {
            type = SC_ptr_defintion(cToken);
            GEN_PTR::PTR_to_address(cToken, cTemp);
        }


    }

    GEN_DATA::DATA_write_templates();
}
