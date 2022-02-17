#include "include/err.hh"
#include "include/lexer.hh"
#include "include/token-op.hh"
#include <fstream>

void init (std::ifstream *file) {
    if ( !file->good() ) ERR_file_doesnt_exist();
    std::string contents;
    unsigned int INTline = 1;

    while ( !file->eof() ) {
        getline(*file, contents);
        if ( !contents.empty() )
            lexer(contents, INTline);
        INTline++;
    }
    TOKEN_parser();
}

int main (int argc, char* argv[]) {
    if ( argc != 3 ) ERR_argument_expected();

    std::ifstream file(argv[1]);
    init(&file);
    std::string _union = ".//sh/union.sh " + std::string(argv[2]);
    system(_union.c_str());
    return 0;
}
