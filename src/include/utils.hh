/** Created by jdpmm on 12-02-2022 **/
#ifndef WGPP_PROGRAMMING_LANGUAGE_UTILS_HH
#define WGPP_PROGRAMMING_LANGUAGE_UTILS_HH

#include "err.hh"

std::string UTL_get_whole_number    (std::string src, std::size_t from, unsigned int intline);
std::string UTL_check_character     (std::string src, std::size_t from, unsigned int intline);
std::string UTL_get_until_delimiter (std::string src, std::size_t from, unsigned int intline, char d);

#endif
