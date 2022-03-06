/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_GENERATE_HH
#define WGPP_PROGRAMMING_LANGUAGE_GENERATE_HH

#include "token-types.hh"
#include "temp.hh"
#include "variables.hh"
#include "utils.hh"
#include <algorithm>

namespace asmfiles_   {};
namespace v_dataSeg   {};
namespace helpersCODE {};

class GEN_DATA {
public:
    static void DATA_dataSegment     ();
    static std::size_t DATA_setLabel (const std::string &lcontents);
    static void DATA_write_templates ();
};

class GEN_EXIT {
public:
    static void EXIT_by_simple_value (std::vector<TOKEN> list, TEMP* temp);
    static void EXIT_by_var_val       (std::vector<TOKEN> list, TEMP* temp);
};

class GEN_WOUT {
public:
    static void WOUT_string (std::vector<TOKEN> list, TEMP* temp);
    static void WOUT_var    (std::vector<TOKEN> list, TEMP* temp);
    static void WOUT_arith  (std::vector<TOKEN> list, TEMP *temp);
};

class GEN_VARIABLES {
public:
    static void VAR_int_by_constant_value (std::vector<TOKEN> list, TEMP *temp);
    static void VAR_chr_by_constant_value (std::vector<TOKEN> list, TEMP *temp);
    static void VAR_copy_value_vTv        (std::vector<TOKEN> list, TEMP *temp, TVar type);
};

class GEN_PRINTF {
public:
    static void PRINTF_call     (std::vector<TOKEN> list, TEMP *temp);
    static void PRINTF_setR_var (VARIABLE v, std::string *temp, int nargs_count, char type);
};

class GEN_CHG {
public:
    static void CHG_varto_const (std::vector<TOKEN> list, TEMP* temp);
    static void CHG_varto_var   (std::vector<TOKEN> list, TEMP* temp);
};

class GEN_INTF {
public:
    static void INTF_variable (VARIABLE var, TEMP* temp, char typeop);
};

class GEN_ARITH {
public:
    static void ARITH_check_call     (std::vector<TOKEN> list, TEMP *temp);
    static void ARITH_gen_operations (TOKEN v, TEMP* temp, char typeValue, char typeOperation);
    static void ARITH_gen_opsort     (TOKEN v1, TOKEN v2, TOKEN operation, TEMP *temp);
};

class GEN_PTR {
public:
    static void PTR_to_address (std::vector<TOKEN> list, TEMP *temp);
};

#endif
