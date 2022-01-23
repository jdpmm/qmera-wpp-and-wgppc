/** This file has been created to make some useful operations
 * - Created by jdpmm on 22-01-2022 **/
#ifndef WG___UTIL_H
#define WG___UTIL_H
#include <iostream>

std::string get_whole_number (std::string src, size_t from) {
    std::string num;
    do {
        num += src[from];
        from++;
    } while ( std::isdigit(src[from]) );
    return num;
}

#endif