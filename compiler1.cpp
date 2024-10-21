#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include <string.h>
#include "processor1.h"

void run_data(FILE* file_one, FILE* file_two, char* data1);

int size_calculation(FILE* file_one);

int main()
{
    
    FILE* file_one = fopen("file_one.txt", "r");
    FILE* file_two = fopen("file_two.txt", "w");

    int size_file_one = size_calculation(file_one);
    char* data1 = (char*) calloc(size_file_one, sizeof(char));

    run_data(file_one, file_two, data1);
    
}

void run_data(FILE* file_one, FILE* file_two, char* data1)
{
    int arg = 0;
    while (fscanf(file_one, "%s", data1) != EOF)
    {
        const char* txt_command = data1;
        /*if (strchr(txt_command, (int) ";"))
        {
            fprintf(file_two, "%x\n", LABEL);
        }*/
        if (stricmp(txt_command, "push") == 0)
        {
            fscanf(file_one, "%s", data1);
            const char* txt_command1 = data1;
            if (stricmp(txt_command1, "AX") == 0)
            {
                fprintf(file_two, "%d %d %d\n",PUSH, register_code, AX_num);
            }
            else if (stricmp(txt_command1, "BX") == 0)
            {
                fprintf(file_two, "%d %d %d\n",PUSHR, register_code, BX_num);
            }
            else if (stricmp(txt_command1, "CX") == 0)
            {
                fprintf(file_two,"%d %d %d\n",PUSHR, register_code, DX_num);
            }
            else if (stricmp(txt_command1, "DX") == 0)
            {
                fprintf(file_two, "%d %d %d\n",PUSHR, register_code, CX_num);
            }
            else
            {
                fprintf(file_two, "%d %d %s \n", PUSH, stack_code, txt_command1);
            }
            //fscanf(file_one, "%d", &arg);
            //fprintf(file_two, "%d %d\n", PUSH, arg);
        }

        else if (stricmp(txt_command, "add") == 0)
        {
            fprintf(file_two,"%d\n", ADD);
        }

        else if (stricmp(txt_command, "sub") == 0)
        {
            fprintf(file_two,"%d\n", SUB);
        }   

        else if (stricmp(txt_command, "mul") == 0)
        {
            fprintf(file_two,"%d\n", MUL);
        }  

        else if (stricmp(txt_command, "div") == 0)
        {
            fprintf(file_two,"%d\n", DIV);
        }   

        else if (stricmp(txt_command, "sqrt") == 0)
        {
            fprintf(file_two,"%d\n", SQRT);
        }   

        else if (stricmp(txt_command, "sin") == 0)
        {
            fprintf(file_two,"%d\n", SIN);
        }   

        else if (stricmp(txt_command, "dump") == 0)
        {
            fprintf(file_two,"%d\n", DUMP);
        }   
        else if (stricmp(txt_command, "out") == 0)
        {
            fprintf(file_two,"%d\n", OUT_);
        }   
        else if (stricmp(txt_command, "cos") == 0)
        {
            fprintf(file_two,"%d\n", COS);
        }   
        else if (stricmp(txt_command, "jmp") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JMP, arg);
        }   
        else if (stricmp(txt_command, "ja") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n",JA, arg);
        }   
        else if (stricmp(txt_command, "jae") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JAE, arg);
        }   
        else if (stricmp(txt_command, "jb") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JB, arg);
        }   
        else if (stricmp(txt_command, "jbe") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JBE, arg);
        }   
        else if (stricmp(txt_command, "je") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JE, arg);
        }   
        else if (stricmp(txt_command, "jne") == 0)
        {
            fscanf(file_one, "%d", &arg);
            fprintf(file_two,"%d %d\n", JNE, arg);
        }   
        else if (stricmp(txt_command, "hlt") == 0)
        {
            fprintf(file_two,"%d\n", HLT);
        } 
        else if (stricmp(txt_command, "pushr") == 0)
        {
            fscanf(file_one, "%s", data1);
            const char* txt_command1 = data1;
            if (stricmp(txt_command1, "AX") == 0)
            {
                fprintf(file_two, "%d %d\n",PUSHR, AX_num);
            }
            else if (stricmp(txt_command1, "BX") == 0)
            {
                fprintf(file_two, "%d %d\n",PUSHR, BX_num);
            }
            else if (stricmp(txt_command1, "CX") == 0)
            {
                fprintf(file_two,"%d %d\n",PUSHR, DX_num);
            }
            else if (stricmp(txt_command1, "DX") == 0)
            {
                fprintf(file_two, "%d %d\n",PUSHR, CX_num);
            }
        }  
        else if (stricmp(txt_command, "pop") == 0)
        {
           
            fscanf(file_one, "%s", data1);
            const char* txt_command2 = data1;
            if (stricmp(txt_command2, "AX") == 0)
            {
                fprintf(file_two, "%d %d \n",POP, AX_num);
            }
            else if (stricmp(txt_command2, "BX") == 0)
            {
                fprintf(file_two, "%d %d \n",POP, BX_num);
            }
            else if (stricmp(txt_command2, "CX") == 0)
            {
                fprintf(file_two, "%d %d \n",POP, DX_num);
            }
            else if (stricmp(txt_command2, "DX") == 0)
            {
                fprintf(file_two, "%d %d \n",POP, CX_num);
            }
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
