/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_TEMP_HH
#define WGPP_PROGRAMMING_LANGUAGE_TEMP_HH

#include "functions.hh"


enum class TyTemp : unsigned int {
    FUNCTION
};

struct TEMP {
    std::string temp;
    std::string code;
    TyTemp      type;

    /** For functions **/
    std::string namefunc;
    unsigned int rbytes;
    int          rbytes_aux;
    int          int_created;
    int          n_parameters;
    int          char_created;
    TVar         last_type;
};
extern std::vector<TEMP> templates;

extern std::string ar_64b [5];
extern std::string ar_32b [5];
extern std::string ar_16b [5];
extern std::string ar_8b  [5];

std::size_t TEMP_make_function_temp (std::string fn, int np);
TEMP* TEMP_get_template             (std::size_t idx);
void TEMP_setpoStack                (TEMP* temp, TVar type);
#endif
