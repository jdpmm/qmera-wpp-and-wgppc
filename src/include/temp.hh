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
    int          variables_created;
    int          n_parameters;
};
extern std::vector<TEMP> templates;

std::size_t TEMP_make_function_temp (std::string fn, int np);
TEMP* TEMP_get_template             (std::size_t idx);
void TEMP_setpoStack                (TEMP* temp, TVar type);
#endif
