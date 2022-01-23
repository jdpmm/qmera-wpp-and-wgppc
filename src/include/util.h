/** This file has been created to make some useful operations
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___UTIL_H
#define WG___UTIL_H
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

std::string str_until_ (const std::string &src, size_t from, char until) {
    std::string r;
    do {
        if ( from >= src.size() ) delimiter_expected();
        r += src[from];
        from++;
    } while ( src[from] != until );

    return r;
}

#endif