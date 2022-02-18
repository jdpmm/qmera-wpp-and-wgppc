/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_GENERATE_HH
#define WGPP_PROGRAMMING_LANGUAGE_GENERATE_HH

#include "token-types.hh"
#include "temp.hh"
#include "variables.hh"

namespace asmfiles_ {};
namespace v_dataSeg {};

class GEN_DATA {
public:
    static void GEN_dataSegment     ();
    static std::size_t GEN_setLabel (const std::string &lcontents);
    static void GEN_write_templates ();
};

class GEN_EXIT {
public:
    static void exit_by_simple_value (std::vector<TOKEN> list, TEMP* temp);
    static void exit_by_variable_val (std::vector<TOKEN> list, TEMP* temp);
};

class GEN_WOUT {
public:
    static void wout_string (std::vector<TOKEN> list, TEMP* temp);
};

class GEN_VARIABLES {
public:
    static void INT_by_number (std::vector<TOKEN> list, TEMP *temp);
    static void CHR_by_char   (std::vector<TOKEN> lits, TEMP *temp);
};

#endif
