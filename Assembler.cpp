#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include <string.h>
#include "compiler1.h"

static void run_with_struct(COMPILERS* compiler_struct);

static int size_calculation(FILE* file_one);

static void push_analysis_compiler(COMPILERS* compiler_struct);

static void pop_analysis_compiler(COMPILERS* compiler_struct);

static int label_analysis_compiler(COMPILERS* compiler_struct);

static int jump_analysis(COMPILERS* compiler_struct);

static void commands_start( COMPILERS* compiler_struct);

static void do_commands(char* txt, COMPILERS* compiler_struct, int com_code, func_def func, func_def func_label);

static void do_hlt(COMPILERS* compiler_struct);

static void do_add(COMPILERS* compiler_struct);

static void do_root(COMPILERS* compiler_struct);

static void do_sub(COMPILERS* compiler_struct);

static void do_mul(COMPILERS* compiler_struct);

static void do_div(COMPILERS* compiler_struct);

static void do_sqrt(COMPILERS* compiler_struct);

static void do_dump(COMPILERS* compiler_struct);

static void do_out(COMPILERS* compiler_struct);

static void do_pop(COMPILERS* compiler_struct);

static void do_in(COMPILERS* compiler_struct);

static void do_jmp(COMPILERS* compiler_struct);

static void do_ja(COMPILERS* compiler_struct);

static void do_jb(COMPILERS* compiler_struct);

static void lab_push_pop(COMPILERS* compiler_struct);

static void lab_others(COMPILERS* compiler_struct);

static void lab_jmp(COMPILERS* compiler_struct);

static void do_call(COMPILERS* compiler_struct);

static void do_ret(COMPILERS* comppiler_struct);

static void do_jne(COMPILERS* comppiler_struct);

static void do_je(COMPILERS* comppiler_struct);

static void do_jae(COMPILERS* comppiler_struct);

static void do_jbe(COMPILERS* comppiler_struct);


int main()
{
    COMPILERS compiler_struct = {}; 
    compiler_struct.after_call = 0;
    
    compiler_struct.file_one = fopen("file_one.txt", "r");
    compiler_struct.file_two = fopen("file_two.txt", "w");

    int size_file_one = size_calculation(compiler_struct.file_one);
    compiler_struct.data1 = (char*) calloc(size_file_one, sizeof(char));
    commands_start(&compiler_struct);

    label_analysis_compiler(&compiler_struct);
    rewind(compiler_struct.file_one);

    run_with_struct(&compiler_struct);

    for (int i = 0; i < compiler_struct.amount_labels; i ++)
    {
        printf(" %s %d\n", compiler_struct.array_labels[i].label, compiler_struct.array_labels[i].addr);
    }
}
      

int size_calculation(FILE* file_one)
{
    fseek(file_one, 0, SEEK_END);
    int size_file_one = ftell(file_one);
    rewind(file_one);
    return size_file_one;
}

void push_analysis_compiler(COMPILERS* compiler_struct)
{
    fscanf(compiler_struct->file_one, "%s", compiler_struct->data1);
        const char* txt_command1 = compiler_struct->data1; 
        if (stricmp(txt_command1, "AX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d\n",PUSH, register_code, AX_num);
        }
        else if (stricmp(txt_command1, "BX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d\n",PUSH, register_code, BX_num);
        }
        else if (stricmp(txt_command1, "CX") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d %d\n",PUSH, register_code, CX_num);
        }
        else if (stricmp(txt_command1, "DX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d\n",PUSH, register_code, DX_num);
        }
        else
        {
            fprintf(compiler_struct->file_two, "%d %d %s \n", PUSH, stack_code, txt_command1);
        }
}

void pop_analysis_compiler(COMPILERS* compiler_struct)
{
    fscanf(compiler_struct->file_one, "%s", compiler_struct->data1);
        const char* txt_command1 = compiler_struct->data1;
        if (stricmp(txt_command1, "AX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d \n", POP, register_code, AX_num);
        }
        else if (stricmp(txt_command1, "BX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d\n", POP, register_code, BX_num);
        }
        else if (stricmp(txt_command1, "CX") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d %d\n", POP, register_code, CX_num);
        }
        else if (stricmp(txt_command1, "DX") == 0)
        {
            fprintf(compiler_struct->file_two, "%d %d %d\n", POP, register_code, DX_num);
        }
        else
        {
            fprintf(compiler_struct->file_two, "%d %d %s \n", POP, stack_code, txt_command1);
        }
}

int label_analysis_compiler(COMPILERS* compiler_struct)
{
    compiler_struct->jmp_analysis = 0;
    compiler_struct->addr_lab = 0;

    while (fscanf(compiler_struct->file_one, "%s", compiler_struct->data1) != EOF)
    {
        char* txt_command = compiler_struct->data1;
        const char* result = strchr(txt_command, ':');
        if (result != NULL && compiler_struct->jmp_analysis != 1)
        {
            compiler_struct->array_labels[compiler_struct->amount_labels].addr = compiler_struct->addr_lab;

            compiler_struct->array_labels[compiler_struct->amount_labels].label = (char*) calloc(START_SIZE, sizeof(char));
            compiler_struct->array_labels[compiler_struct->amount_labels].label = strdup(txt_command);
            //if (compiler_struct->)
            compiler_struct->amount_labels++;
        }
        else
        {
            for (int i = 0; i <  compiler_struct->amount_comands; i++)
            {
                if (stricmp(txt_command,compiler_struct->array_comands[i].name_comands) == 0)
                {
                    compiler_struct->array_comands[i].func_label(compiler_struct);
                }    
            }
        }
   
    }   
}

int jump_analysis(COMPILERS* compiler_struct)
{
    fscanf(compiler_struct->file_one, "%s", compiler_struct->data1);
    const char* txt_command1 = compiler_struct->data1; 
    for (int i = 0; i < compiler_struct->amount_labels; i++)
    {
        const char* txt_command2 = compiler_struct->array_labels[i].label;
        if (stricmp(txt_command1, txt_command2) == 0) 
        {
            return compiler_struct->array_labels[i].addr;
        }   
    }
    return ERROR;
}



void commands_start(COMPILERS* compiler_struct)
{
    compiler_struct->amount_comands = 0;
    char* txt;

    func_def func = &do_hlt;
    func_def func_label = &lab_others;
    txt = "hlt";
    do_commands(txt, compiler_struct, HLT, func, func_label); // macros
    
    func_label = &lab_push_pop;
    func = push_analysis_compiler;
    txt = "push";
    do_commands(txt, compiler_struct, PUSH, func, func_label);

    func_label = &lab_others;
    func = do_add;
    txt = "add";
    do_commands(txt, compiler_struct, ADD, func , func_label);

    func_label = &lab_others;
    func = do_sub;
    txt = "sub";
    do_commands(txt, compiler_struct, SUB, func, func_label);

    func_label = &lab_others;
    func = do_mul;
    txt = "mul";
    do_commands(txt, compiler_struct, MUL, func, func_label);

    func_label = &lab_others;
    func = do_div;
    txt = "div";
    do_commands(txt, compiler_struct, DIV, func, func_label);

    func_label = &lab_others;
    func = do_sqrt;
    txt = "sqrt";
    do_commands(txt, compiler_struct, SQRT, func, func_label);

    func_label = &lab_others;
    func = do_dump;
    txt = "dump";
    do_commands(txt, compiler_struct, DUMP, func, func_label);

    func_label = &lab_others;
    func = do_out;
    txt = "out";
    do_commands(txt, compiler_struct, OUT_, func, func_label);

    func_label = &lab_jmp;
    func = do_jmp;
    txt = "jmp";
    do_commands(txt, compiler_struct, JMP, func, func_label);

    func_label = &lab_jmp;
    func = do_ja;
    txt = "ja";
    do_commands(txt, compiler_struct, JA, func, func_label);

    func_label = &lab_jmp;
    func = do_jb;
    txt = "jb";
    do_commands(txt, compiler_struct, JB, func, func_label);

    func_label = &lab_push_pop;
    func = do_pop;
    txt = "pop";
    do_commands("pop", compiler_struct, POP, func, func_label);

    func_label = &lab_others;
    func = do_in;
    txt = "in";
    do_commands("in", compiler_struct, IN_, func, func_label);

    func_label = &lab_others;
    func = do_root;
    txt = "root";
    do_commands("root", compiler_struct, ROOT, func, func_label);

    func_label = &lab_jmp;
    func = do_call;
    txt = "call";
    do_commands("call", compiler_struct, CALL, func, func_label);

    do_commands("ret", compiler_struct, RET, do_ret, lab_others);

    do_commands("jae", compiler_struct, JAE, do_jae, lab_jmp);

    do_commands("jbe", compiler_struct, JBE, do_jbe, lab_jmp);

    do_commands("je",  compiler_struct, JE,  do_je , lab_jmp);

    do_commands("jne", compiler_struct, JNE, do_jne, lab_jmp);

    
}

static void do_hlt(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", HLT);
}

static void do_add(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", ADD);
}

static void do_root(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", ROOT);
}

static void do_sub(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", SUB);
}

static void do_mul(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", MUL);
}

static void do_div(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", DIV);
}

static void do_sqrt(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", SQRT);
}

static void do_dump(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", DUMP);
}

static void do_out(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", OUT_);
}

static void do_pop(COMPILERS* compiler_struct)
{
    pop_analysis_compiler(compiler_struct);    
}

static void do_in(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d\n", IN_);    
}

static void do_jmp(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d %d\n", JMP, jump_analysis(compiler_struct));
}

static void do_jne(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d %d\n", JNE, jump_analysis(compiler_struct));
}

static void do_je(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d %d\n", JE, jump_analysis(compiler_struct));
}

static void do_jbe(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d %d\n", JBE, jump_analysis(compiler_struct));
}

static void do_jae(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d %d\n", JAE, jump_analysis(compiler_struct));
}

static void do_ja(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d %d\n",JA, jump_analysis(compiler_struct));
}

static void do_jb(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two,"%d %d\n",JB, jump_analysis(compiler_struct));
}

static void do_ret(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d", RET);
}

static void lab_push_pop(COMPILERS* compiler_struct)
{
    ADDR_LABEL_0();
    ADDR_LABEL_0();
    ADDR_LABEL_0();
}

static void lab_others(COMPILERS* compiler_struct)
{
    ADDR_LABEL_0();
}

static void lab_jmp(COMPILERS* compiler_struct)
{
    ADDR_LABEL_1();
}

static void do_call(COMPILERS* compiler_struct)
{
    fprintf(compiler_struct->file_two, "%d %d \n", CALL, jump_analysis(compiler_struct));
}

static void do_commands(char* txt, COMPILERS* compiler_struct, int com_code, func_def func, func_def func_lab)
{
    compiler_struct->array_comands[compiler_struct->amount_comands].name_comands = (char*) calloc(10, sizeof(char)); // todo
    compiler_struct->array_comands[compiler_struct->amount_comands].name_comands = strdup(txt);

    compiler_struct->array_comands[compiler_struct->amount_comands].com_code = com_code;

    compiler_struct->array_comands[compiler_struct->amount_comands].func = func;                                                                                    
    compiler_struct->array_comands[compiler_struct->amount_comands].func_label = func_lab;
    compiler_struct->amount_comands++;
}

static void run_with_struct(COMPILERS* compiler_struct)
{
    while (fscanf(compiler_struct->file_one, "%s", compiler_struct->data1) != EOF)
    {
        const char* txt_command = compiler_struct->data1;
        for (int i = 0; i <  compiler_struct->amount_comands; i++)
        {
            if (stricmp(txt_command,compiler_struct->array_comands[i].name_comands) == 0)
            {
                compiler_struct->array_comands[i].func(compiler_struct);
            }    
        }
    }        
}
// пропуск комментриев 
// RISC_V X86-64
// 4 BYTE  instrhui 