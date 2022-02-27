#include "include/generate.hh"

namespace asmfiles_ {
    FILE* codeSegment = fopen("code.s", "w");
    FILE* dataSegment = fopen("data.s", "w");
};

namespace v_dataSeg {
    std::vector<std::string> labels = {};
    std::string labelname           = ".labl";
};

namespace helpersCODE {
    // To printf function
    bool PFFagrs_gt_5          = false;
    std::string PFFcodetempaux = "";
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

void GEN_EXIT::EXIT_by_var_val (std::vector<TOKEN> list, TEMP* temp) {
    VARIABLE thisV = VAR_get_variable(list.at(1).value_as_token, temp->namefunc);
    temp->code += "\tmovq $60, %rax\n";

    if ( thisV.type == TVar::INTEGER )
        temp->code += "\tmovslq -" + std::to_string(thisV.poStack) + "(%rbp), %rdi\n";
    else
        temp->code += "\tmovsbq -" + std::to_string(thisV.poStack) + "(%rbp), %rdi\n";
    temp->code += "\tsyscall\n";
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

void GEN_WOUT::WOUT_var (std::vector<TOKEN> list, TEMP* temp) {
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
void GEN_VARIABLES::VAR_int_by_constant_value (std::vector<TOKEN> list, TEMP *temp) {
    TEMP_setpoStack(temp, TVar::INTEGER);
    VAR_make_variable(list.at(1).value_as_token, temp->namefunc, temp->rbytes, TVar::INTEGER);
    temp->code += "\tsubq $4, %rsp\n"
                  "\tmovl $" + list.at(3).value_as_token + ", -" + std::to_string(temp->rbytes) + "(%rbp)\n";
    temp->int_created++;
    temp->last_type = TVar::INTEGER;
}

void GEN_VARIABLES::VAR_chr_by_constant_value (std::vector<TOKEN> list, TEMP *temp) {
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
 * printed is 5 (for the moment)____________________________________________________________________________________ |
 * **/
void GEN_PRINTF::PRINTF_call (std::vector<TOKEN> list, TEMP *temp) {
    /* strsc = String definided in the wgpp code
     * strfl = String that will work as label to assembly code
     * idxsx = Index to iter the strsc
     * nametoprint = Name of the anything to print their value
     * typetoprint = Type to print
     * nPF_arguments = Count to know how many values will be printed */
    std::string strsc = list.at(1).value_as_token;
    std::string strfl;
    std::size_t idxsc = 0;
    std::string nametoprint;
    char typetoprint;
    int nPF_arguments = 0;

    while ( idxsc < strsc.size() ) {
        typetoprint = '-';
        nametoprint = "";

        // To variables
        GET_VARNAME:
        if ( strsc[idxsc] == '$'  ) {
            nametoprint = UTL_get_until_delimiter(strsc, idxsc, list.at(0).line_definition, '$');
            idxsc += nametoprint.size();
            typetoprint = 'v';
        }

        if ( typetoprint == 'v' ) {
            VARIABLE thisV = VAR_get_variable(nametoprint, temp->namefunc);
            if ( thisV.type == TVar::INTEGER ) strfl += "%d";
            if ( thisV.type == TVar::CHARACTER ) strfl += "%c";

            GEN_PRINTF::PRINTF_setR_var(thisV, &temp->code, nPF_arguments);
            nPF_arguments++;

            if ( strsc[idxsc] == '$' ) goto GET_VARNAME;
        }

        if ( strsc[idxsc] == '%' ) {
            strfl += "%%";
            idxsc++;
        }

        strfl += strsc[idxsc];
        idxsc++;
    }

    temp->code += helpersCODE::PFFcodetempaux;
    strfl[strfl.size() - 1] = '\\';
    strfl += "n\"";
    std::size_t idxLabel = GEN_DATA::DATA_setLabel(strfl);
    temp->code += "\tleaq " + v_dataSeg::labels.at(idxLabel) + "(%rip), %rdi\n"
                  "\tmovl $0, %eax\n"
                  "\tcall printf@PLT\n"
                  "\tmovl $0, %eax\n";

    if ( helpersCODE::PFFagrs_gt_5 )
        temp->code += "\taddq $8, %rsp\n";
    helpersCODE::PFFagrs_gt_5 = false;
    helpersCODE::PFFcodetempaux = "";
}

void GEN_PRINTF::PRINTF_setR_var (VARIABLE v, std::string *temp, int nargs_count) {
    if ( nargs_count <= 4 ) {
        if ( v.type == TVar::INTEGER )
            *temp += "\tmovl -" + std::to_string(v.poStack) + "(%rbp), " + ar_32b[nargs_count] + "\n";
        else
            *temp += "\tmovsbl -" + std::to_string(v.poStack) + "(%rbp), " + ar_32b[nargs_count] + "\n";
    }
    else {
        if ( !((nargs_count+1) % 2) && !helpersCODE::PFFagrs_gt_5 ) *temp += "\tsubq $8, %rsp\n";
        if ( v.type == TVar::INTEGER ) {
            helpersCODE::PFFcodetempaux.insert(0, "\tmovl -" + std::to_string(v.poStack) + "(%rbp), %eax\n\tpushq %rax\n");
        }
        else {
            helpersCODE::PFFcodetempaux.insert(0, "\tmovsbl -" + std::to_string(v.poStack) + "(%rbp), %eax\n\tpushq %rax\n");
        }
        helpersCODE::PFFagrs_gt_5 = true;
    }
}

/** GEN CHG ------------------------------------------------------------------------------------------------------- |
 * CHG function is used to change the value of one variable________________________________________________________ |
 * **/
void GEN_CHG::CHG_varto_const (std::vector<TOKEN> list, TEMP* temp) {
    VARIABLE thisV = VAR_get_variable(list.at(1).value_as_token, temp->namefunc);
    if ( thisV.type == TVar::INTEGER )
        temp->code += "\tmovl $" + list.at(2).value_as_token + ", -" + std::to_string(thisV.poStack) + "(%rbp)\n";
    else
        temp->code += "\tmovb $" + list.at(2).value_as_token + ", -" + std::to_string(thisV.poStack) + "(%rbp)\n";
}

void GEN_CHG::CHG_varto_var (std::vector<TOKEN> list, TEMP* temp) {
    VARIABLE tochg = VAR_get_variable(list.at(1).value_as_token, temp->namefunc);
    VARIABLE tocpy = VAR_get_variable(list.at(2).value_as_token, temp->namefunc);

    if ( tochg.type == TVar::INTEGER ) {
        if ( tocpy.type == TVar::INTEGER ) {
            temp->code += "\tmovl -" + std::to_string(tocpy.poStack) + "(%rbp), %eax\n"
                          "\tmovl %eax, -" + std::to_string(tochg.poStack) + "(%rbp)\n";
        }
        else {
            temp->code += "\tmovb -" + std::to_string(tocpy.poStack) + "(%rbp), %al\n"
                          "\tmovl %eax, -" + std::to_string(tochg.poStack) + "(%rbp)\n";
        }
    }
    else {
        if ( tocpy.type == TVar::INTEGER ) {
            temp->code += "\tmovzbl -" + std::to_string(tocpy.poStack) + "(%rbp), %eax\n"
                          "\tmovb %al, -" + std::to_string(tochg.poStack) + "(%rbp)\n";
        }
        else {
            temp->code += "\tmovb -" + std::to_string(tocpy.poStack) + "(%rbp), %al\n"
                          "\tmovb %al, -" + std::to_string(tochg.poStack) + "(%rbp)\n";
        }
    }
}

/** GEN INTF ------------------------------------------------------------------------------------------------------ |
 * The int functions are generated as a "--" (DEC) "++" (INC) and "n*=1" (NEG) in C++ or C (Probably in anothers) _ |
 * **/
void GEN_INTF::INTF_incvar (unsigned int postack, TEMP* temp) {
    temp->code += "\tincl -" + std::to_string(postack) + "(%rbp)\n";
}

void GEN_INTF::INTF_decvar (unsigned int postack, TEMP* temp) {
    temp->code += "\tdecl -" + std::to_string(postack) + "(%rbp)\n";
}

void GEN_INTF::INTF_negvar (unsigned int postack, TEMP* temp) {
    temp->code += "\tnegl -" + std::to_string(postack) + "(%rbp)\n";
}
