#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include <string.h>
#include "compiler1.h"


int main()
{
    COMPILERS compiler_struct = {}; 
    
    compiler_struct.file_one = fopen("file_one.txt", "r");
    compiler_struct.file_two = fopen("file_two.txt", "w");

    int size_file_one = size_calculation(compiler_struct.file_one);
    compiler_struct.data1 = (char*) calloc(size_file_one, sizeof(char));

    label_analysis_compiler(&compiler_struct);
    rewind(compiler_struct.file_one);

    run_data(&compiler_struct);

    for (int i = 0; i < compiler_struct.amount_labels; i ++)
    {
        printf(" %s %d", compiler_struct.array_labels[i].label, compiler_struct.array_labels[i].addr);
    }
    
}

void run_data(COMPILERS* compiler_struct)
{
    int arg = 0;
    while (fscanf(compiler_struct->file_one, "%s", compiler_struct->data1) != EOF)
    {
        const char* txt_command = compiler_struct->data1;
        
        if (stricmp(txt_command, "push") == 0)
        {
            push_analysis_compiler(compiler_struct);
        }

        else if (stricmp(txt_command, "add") == 0)
        { // void (*func)(int, int) 
            fprintf(compiler_struct->file_two,"%d\n", ADD);
        }

        else if (stricmp(txt_command, "root") == 0)
        { // void (*func)(int, int) 
            fprintf(compiler_struct->file_two,"%d\n", ROOT);
        }

        else if (stricmp(txt_command, "in") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", IN_);
        }
        
        else if (stricmp(txt_command, "sub") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", SUB);
        }   

        else if (stricmp(txt_command, "mul") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", MUL);
        }  

        else if (stricmp(txt_command, "div") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", DIV);
        }   

        else if (stricmp(txt_command, "sqrt") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", SQRT);
        }   

        else if (stricmp(txt_command, "sin") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", SIN);
        }   

        else if (stricmp(txt_command, "dump") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", DUMP);
        }   
        else if (stricmp(txt_command, "out") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", OUT_);
        }   
        else if (stricmp(txt_command, "cos") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", COS);
        }   
        else if (stricmp(txt_command, "jmp") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JMP, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "ja") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n",JA, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "jae") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JAE, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "jb") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JB, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "jbe") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JBE, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "je") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JE, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "jne") == 0)
        {
            fprintf(compiler_struct->file_two,"%d %d\n", JNE, jump_analysis(compiler_struct));
        }   
        else if (stricmp(txt_command, "hlt") == 0)
        {
            fprintf(compiler_struct->file_two,"%d\n", HLT);
        } 
        
        else if (stricmp(txt_command, "pop") == 0)
        {
            pop_analysis_compiler(compiler_struct);
        }

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
    compiler_struct->amount_comands = 0;
    int jmp_analysis = 0;

    while (fscanf(compiler_struct->file_one, "%s", compiler_struct->data1) != EOF)
    {
        char* txt_command = compiler_struct->data1;
        const char* result = strchr(txt_command, ':');
        if (result != NULL && jmp_analysis != 1)
        {
            compiler_struct->array_labels[compiler_struct->amount_labels].addr = compiler_struct->amount_comands;

            compiler_struct->array_labels[compiler_struct->amount_labels].label = (char*) calloc(10, sizeof(char));
            compiler_struct->array_labels[compiler_struct->amount_labels].label = strdup(txt_command);

            compiler_struct->amount_labels++;
        }
        else if (stricmp(txt_command, "push") == 0)
        {
            compiler_struct->amount_comands += 3;
            jmp_analysis = 0;
        }

        else if (stricmp(txt_command, "in") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }

        else if (stricmp(txt_command, "add") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }

        else if (stricmp(txt_command, "sub") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   

        else if (stricmp(txt_command, "mul") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }  

        else if (stricmp(txt_command, "div") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   

        else if (stricmp(txt_command, "sqrt") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   

        else if (stricmp(txt_command, "sin") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   

        else if (stricmp(txt_command, "dump") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   
        else if (stricmp(txt_command, "out") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   
        else if (stricmp(txt_command, "cos") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        }   
        else if (stricmp(txt_command, "jmp") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "ja") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "jae") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "jb") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "jbe") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "je") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "jne") == 0)
        {
            compiler_struct->amount_comands += 2;
            jmp_analysis = 1;
        }   
        else if (stricmp(txt_command, "hlt") == 0)
        {
            compiler_struct->amount_comands++;
            jmp_analysis = 0;
        } 
        
        else if (stricmp(txt_command, "pop") == 0)
        {
            compiler_struct->amount_comands += 3;
            jmp_analysis = 0;
        }  
    }        
}

int jump_analysis(COMPILERS* compiler_struct)
{
    fscanf(compiler_struct->file_one, "%s", compiler_struct->data1);
    const char* txt_command1 = compiler_struct->data1; 
    //printf("%s, %s",txt_command1, txt_command2 );
    for (int i = 0; i < compiler_struct->amount_labels; i++)
    {
        const char* txt_command2 = compiler_struct->array_labels[i].label;
        if (stricmp(txt_command1, txt_command2) == 0) 
        {
            return compiler_struct->array_labels[i].addr;
        }   
    }
}

// пропуск комментриев 
// RISC_V X86-64
// 4 BYTE  instrhui 