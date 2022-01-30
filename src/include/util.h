/** This file has been created to make some useful operations
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WGPP_UTIL_H
#define WGPP_UTIL_H

#include "variables.h"
#include "err-report.h"
#include <iostream>

std::string get_whole_number (std::string src, size_t from) {
    std::string num;
    do {
        if ( from >= src.size() ) delimiter_expected();
        num += src[from];
        from++;
    } while ( std::isdigit(src[from]) );
    return num;
}

std::string get_whole_string (const std::string &src, size_t from) {
    std::string r;
    do {
        if ( from >= src.size() ) token_expected("DOUBLE QUOTE");
        r += src[from];
        from++;
    } while ( src[from] != '"' );
    return r;
}

std::string get_character_value (const std::string &src, size_t from) {
    std::string chr;
    chr.push_back('\'');
    chr.push_back(src[from + 1]);

    if ( src[from + 2] != '\'' ) token_expected("SINGLE QUOTE");
    chr.push_back('\'');

    return chr;
}

bool valid_char (char chr) {
    if ( chr >= 65 && chr <= 90 )  return true;
    if ( chr >= 97 && chr <= 122 ) return true;
    if ( chr >= 48 && chr <= 57 )  return true;
    if ( chr == '_' )              return true;

    return false;
}


std::string get_name_of (const std::string &src, size_t from, char delimiter, bool validchr) {
    std::string name;
    name.push_back(delimiter);
    from++;

    do {
        if ( from >= src.size() ) delimiter_expected();
        if ( !valid_char(src[from]) && validchr ) invalid_name(name);
        name += src[from];
        from++;
    } while ( src[from] != delimiter );

    name += delimiter;
    return name;
}

#endif
