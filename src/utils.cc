#include "include/utils.hh"

std::string UTL_get_whole_number (std::string src, std::size_t from, unsigned int intline) {
    std::string sn;
    do {
        if ( from > src.size() ) ERR_delimiter_expected(intline);
        sn += src[from];
        from++;
    } while ( std::isdigit(src[from]) );
    return sn;
}

std::string UTL_check_character  (std::string src, std::size_t from, unsigned int intline) {
    std::string chr = "'";
    if ( src[from + 1] == '\\' ) {
        if ( src[from + 2] != 'n' && src[from + 2] != 't' && src[from + 2] != '\'' && src[from + 2] != '0' ) ERR_scape_code_expected(intline);
        if ( src[from + 3] != '\'' ) ERR_delimiter_expected(intline);

        chr += src[from + 1];
        chr += src[from + 2];
        chr += src[from + 3];
        return chr;
    }
    if ( src[from + 2] == '\'' ) {
        chr += src[from + 1];
        chr += src[from + 2];
        return chr;
    }

    ERR_ilegal_character_definition(intline);
    return "";
}

std::string UTL_get_until_delimiter (std::string src, std::size_t from, unsigned int intline, char d) {
    std::string string_d;
    do {
        if ( from > src.size() ) ERR_delimiter_expected(intline);
        string_d +=  src[from];
        from++;
    } while ( src[from] != d );

    string_d += d;
    return string_d;
}
