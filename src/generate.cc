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
void GEN_DATA::DATA_dataSegment () {
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

std::size_t GEN_DATA::DATA_setLabel (const std::string &lcontents) {
    for ( std::size_t i = 0; i < v_dataSeg::labels.size(); ++i )
        if ( v_dataSeg::labels.at(i) == lcontents )
            return i;

    fprintf(asmfiles_::dataSegment, "\t%s%d:\n", v_dataSeg::labelname.c_str(), (int) v_dataSeg::labels.size());
    fprintf(asmfiles_::dataSegment, "\t\t.string %s\n", lcontents.c_str());
    fprintf(asmfiles_::dataSegment, "\t\t.text\n");

    v_dataSeg::labels.push_back(v_dataSeg::labelname + std::to_string(v_dataSeg::labels.size()));
    return v_dataSeg::labels.size() - 1;
}

void GEN_DATA::DATA_write_templates () {
    for ( TEMP temp : templates )
        fprintf(asmfiles_::codeSegment, temp.temp.c_str(), temp.code.c_str());
    fclose(asmfiles_::codeSegment);
    fclose(asmfiles_::dataSegment);
}


/** GEN EXIT FUNCTION ----------------------------------------------------------- |
 * These functions has been declared to set a exit operation in assembly code ___ |
 * **/
void GEN_EXIT::EXIT_by_simple_value (std::vector<TOKEN> list, TEMP* temp) {
    temp->code += "\tmovq $60, %rax\n"
                  "\tmovq $" + list.at(1).value_as_token + ", %rdi\n"
                  "\tsyscall\n";
}

void GEN_EXIT::EXIT_by_variable_val (std::vector<TOKEN> list, TEMP* temp) {
    // TODO: Check: movs__
    unsigned int poStack = VAR_get_variable(list.at(1).value_as_token, temp->namefunc).poStack;
    temp->code += "\tmovq $60, %rax\n"
                  "\tmovslq -" + std::to_string(poStack) + "(%rbp), %rdi\n"
                  "\tsyscall\n";
}

/** GEN WOUT FUNCTION -------------------------------------------------------------------- |
 * These functions has been declared to set the necessary code in assembly to be able      |
 * of print any datatype on wg++ programming language ____________________________________ |
 * **/
void GEN_WOUT::WOUT_string (std::vector<TOKEN> list, TEMP* temp) {
    std::size_t idxLabel = GEN_DATA::DATA_setLabel(list.at(1).value_as_token);
    temp->code += "\tleaq " + v_dataSeg::labels.at(idxLabel) + "(%rip), %rax\n"
                  "\tmovq %rax, %rdi\n"
                  "\tcall puts@PLT\n"
                  "\tmovl $0, %eax\n";
}

void GEN_WOUT::WOUT_variable (std::vector<TOKEN> list, TEMP* temp) {
    VARIABLE variable = VAR_get_variable(list.at(1).value_as_token, temp->namefunc);
    if ( variable.type == TVar::INTEGER ) 
        temp->code += "\tmovl -" + std::to_string(variable.poStack) + "(%rbp), %eax\n";
    if ( variable.type == TVar::CHARACTER )
        temp->code += "\tmovsbl -" + std::to_string(variable.poStack) + "(%rbp), %eax\n";

    temp->code += "\tmovl %eax, %esi\n";
    if ( variable.type == TVar::INTEGER )
        temp->code += "\tleaq .printnum(%rip), %rax\n";
    if ( variable.type == TVar::CHARACTER )
        temp->code += "\tleaq .printchr(%rip), %rax\n";

    temp->code += "\tmovq %rax, %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";
}

/** GEN VARIABLES -------------------------------------------------------------------------------------------------- |
 * These functions has been declared to set the necessary code to create variables in assembly programming language  |
 * (UNIX Assembly) _________________________________________________________________________________________________ |
 * **/
void GEN_VARIABLES::VAR_int_by_number (std::vector<TOKEN> list, TEMP *temp) {
    TEMP_setpoStack(temp, TVar::INTEGER);
    VAR_make_variable(list.at(1).value_as_token, temp->namefunc, temp->rbytes, TVar::INTEGER);
    temp->code += "\tsubq $4, %rsp\n"
                  "\tmovl $" + list.at(3).value_as_token + ", -" + std::to_string(temp->rbytes) + "(%rbp)\n";
    temp->int_created++;
    temp->last_type = TVar::INTEGER;
}

void GEN_VARIABLES::VAR_chr_by_char (std::vector<TOKEN> list, TEMP *temp) {
    TEMP_setpoStack(temp, TVar::CHARACTER);
    VAR_make_variable(list.at(1).value_as_token, temp->namefunc, temp->rbytes, TVar::CHARACTER);
    temp->code += "\tsubq $4, %rsp\n"
                  "\tmovb $" + list.at(3).value_as_token + ", -" + std::to_string(temp->rbytes) + "(%rbp)\n";
    temp->char_created++;
    temp->last_type = TVar::CHARACTER;
}

void GEN_VARIABLES::VAR_copy_value_vTv (std::vector<TOKEN> list, TEMP *temp, TVar type) {
    if ( type == TVar::INTEGER ) TEMP_setpoStack(temp, TVar::INTEGER);
    else TEMP_setpoStack(temp, TVar::CHARACTER);

    VARIABLE toCopy = VAR_get_variable(list.at(3).value_as_token, temp->namefunc);
    temp->code += "\tsubq $4, %rsp\n";

    if ( type == TVar::INTEGER ) {
        if ( toCopy.type == TVar::INTEGER ) {
            temp->code += "\tmovl - " + std::to_string(toCopy.poStack) + "(%rbp), %eax\n"
                          "\tmovl %eax, -" + std::to_string(temp->rbytes) + "(%rbp)\n";
        }
        else {
            temp->code += "\tmovsbl -" + std::to_string(toCopy.poStack) + "(%rbp), %eax\n"
                          "\tmovl %eax, -" + std::to_string(temp->rbytes) + "(%rbp)\n";
        }
        temp->int_created++;
        temp->last_type = TVar::INTEGER;
    }
    else {
        if ( toCopy.type == TVar::INTEGER ) {
            temp->code += "\tmovl -" + std::to_string(toCopy.poStack) + "(%rbp), %eax\n"
                          "\tmovb %al, -" + std::to_string(temp->rbytes) + "(%rbp)\n";
        }
        else {
            temp->code += "\tmovzbl -" + std::to_string(toCopy.poStack) + "(%rbp), %eax\n"
                          "\tmovb %al, -" + std::to_string(temp->rbytes) + "(%rbp)\n";
        }

        temp->char_created++;
        temp->last_type = TVar::CHARACTER;
    }

    VAR_make_variable(list.at(1).value_as_token, temp->namefunc, temp->rbytes, type);
}

/** GEN PRINTF ----------------------------------------------------------------------------------------------------- |
 * The printf function works like printf function on C, since is the same code... But the maximum value to be        |
 * printed is 5 ____________________________________________________________________________________________________ |
 * **/
void GEN_PRINTF::PRINTF_call (std::vector<TOKEN> list, TEMP *temp) {
    std::string strs = list.at(1).value_as_token;
    std::string strf;

    int toprint_count = 0;
    std::size_t idx = 0;
    std::string toprint_name;
    char typeToPrint;

    while ( idx < strs.size() ) {
        typeToPrint = '-';
        toprint_name = "";

        if ( strs[idx] == '$' ) {
            toprint_name = UTL_get_until_delimiter(strs, idx, list.at(0).line_definition, '$');
            idx += toprint_name.size();
            typeToPrint = 'v';
        }
        if ( typeToPrint == 'v' ) {
            VARIABLE thisV = VAR_get_variable(toprint_name, temp->namefunc);
            if ( thisV.type == TVar::INTEGER ) strf += "%d";
            if ( thisV.type == TVar::CHARACTER ) strf += "%c";

            GEN_PRINTF::PRINTF_setR_variable(thisV, temp, toprint_count);
            toprint_count++;
        }
        if ( strs[idx] == '%' ) {
            strf += "%%";
            idx++;
        }
        if ( toprint_count == 6 ) ERR_printf_overflow();

        strf += strs[idx];
        idx++;
    }

    strf[strf.size() - 1] = '\\';
    strf += "n\"";
    std::size_t idxLabel = GEN_DATA::DATA_setLabel(strf);
    temp->code += "\tleaq " + v_dataSeg::labels.at(idxLabel) + "(%rip), %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";
}

void GEN_PRINTF::PRINTF_setR_variable (VARIABLE v, TEMP *temp, int toprint_count) {
    if ( v.type == TVar::INTEGER )
        temp->code += "\tmovl -" + std::to_string(v.poStack) + "(%rbp), " + ar_32b[toprint_count] + "\n";
    else
        temp->code += "\tmovsbl -" + std::to_string(v.poStack) + "(%rbp), " + ar_32b[toprint_count] + "\n";
}
