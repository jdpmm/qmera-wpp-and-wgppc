#include "include/generate.hh"

namespace asmfiles_ {
    FILE* codeSegment = fopen("code.s", "w");
    FILE* dataSegment = fopen("data.s", "w");
};

namespace v_dataSeg {
    std::vector<std::string> labels = {};
    std::string labelname           = ".labl";
};

/** GEN DATA ------------------------------------------------------------------------------------------------- |
 * All these functions has been declared to make the necessary code in the data segment (assembly code) such   |
 * as: Strings to print or global variables __________________________________________________________________ |
 * **/
void GEN_DATA::GEN_dataSegment () {
    fprintf(asmfiles_::dataSegment, ".text\n");
    fprintf(asmfiles_::dataSegment, ".section .rodata\n");
    fprintf(asmfiles_::dataSegment, "\t.globl main\n");
    fprintf(asmfiles_::dataSegment, "\t.type main, @function\n");
    fprintf(asmfiles_::dataSegment, "\t.printnum:\n");
    fprintf(asmfiles_::dataSegment, "\t\t.string \"%%d\\n\"\n");
    fprintf(asmfiles_::dataSegment, "\t\t.text\n");
    fprintf(asmfiles_::dataSegment, "\t.printchr:\n");
    fprintf(asmfiles_::dataSegment, "\t\t.string \"%%c\\n\"\n");
    fprintf(asmfiles_::dataSegment, "\t\t.text\n");
}

std::size_t GEN_DATA::GEN_setLabel (const std::string &lcontents) {
    for ( std::size_t i = 0; i < v_dataSeg::labels.size(); ++i )
        if ( v_dataSeg::labels.at(i) == lcontents )
            return i;

    fprintf(asmfiles_::dataSegment, "\t%s%d:\n", v_dataSeg::labelname.c_str(), (int) v_dataSeg::labels.size());
    fprintf(asmfiles_::dataSegment, "\t\t.string %s\n", lcontents.c_str());
    fprintf(asmfiles_::dataSegment, "\t\t.text\n");

    v_dataSeg::labels.push_back(v_dataSeg::labelname + std::to_string(v_dataSeg::labels.size()));
    return v_dataSeg::labels.size() - 1;
}

void GEN_DATA::GEN_write_templates () {
    for ( TEMP temp : templates )
        fprintf(asmfiles_::codeSegment, temp.temp.c_str(), temp.code.c_str());
    fclose(asmfiles_::codeSegment);
    fclose(asmfiles_::dataSegment);
}


/** GEN EXIT FUNCTION ----------------------------------------------------------- |
 * These functions has been declared to set a exit operation in assembly code ___ |
 * **/
void GEN_EXIT::exit_by_simple_value (std::vector<TOKEN> list, TEMP* temp) {
    temp->code += "\tmovq $60, %rax\n"
                  "\tmovq $" + list.at(1).value_as_token + ", %rdi\n"
                  "\tsyscall\n";
}


/** GEN WOUT FUNCTION -------------------------------------------------------------------- |
 * These functions has been declared to set the necessary code in assembly to be able      |
 * of print any datatype on wg++ programming language ____________________________________ |
 * **/
void GEN_WOUT::wout_string (std::vector<TOKEN> list, TEMP* temp) {
    std::size_t idxLabel = GEN_DATA::GEN_setLabel(list.at(1).value_as_token);
    temp->code += "\tleaq " + v_dataSeg::labels.at(idxLabel) + "(%rip), %rax\n"
                  "\tmovq %rax, %rdi\n"
                  "\tcall puts@PLT\n"
                  "\tmovl $0, %eax\n";
}


/** GEN VARIABLES -------------------------------------------------------------------------------------------------- |
 * These functions has been declared to set the necessary code to create variables in assembly programming language  |
 * (UNIX Assembly) _________________________________________________________________________________________________ |
 * **/
void GEN_VARIABLES::INT_by_number (std::vector<TOKEN> list, TEMP *temp) {
    TEMP_setpoStack(temp, TVar::INTEGER);
    VAR_make_variable(list.at(1).value_as_token, temp->namefunc, temp->rbytes, TVar::INTEGER);
    temp->code += "\tsubq $4, %rsp\n"
                  "\tmovl $" + list.at(3).value_as_token + ", -" + std::to_string(temp->rbytes) + "(%rbp)\n";
}
