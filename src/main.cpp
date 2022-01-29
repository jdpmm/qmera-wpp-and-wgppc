#include "include/err-report.h"
#include "include/lexer.h"
#include "include/token-operations.h"
#include <iostream>
#include <fstream>

void init (std::ifstream *file) {
    std::string line_content;
    int current_line = 1;

    while ( !file->eof() ) {
        std::getline(*file, line_content);
        if ( !line_content.empty() )
            start_lexer(line_content, current_line);
        current_line++;
    }
}

int main (int argc, char* argv[]) {
    if ( argc == 0 ) file_expected();

    std::ifstream file (argv[1]);
    if ( !file.good() ) file_doesnt_exist(argv[1]);

    init(&file);
    parser();

    std::string lastep = "./sh/final.sh " + std::string(argv[1]);
    system(lastep.c_str());
    return 0;
}
