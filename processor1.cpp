#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

#include "processor1.h"

void run(SPV* spu);

int main()
{
    printf("c\n");
    SPV spu = {};
    run(&spu);

    return 0;
}

void run(SPV* spu)
{
    FILE* file_two = fopen("file_two.txt", "r");
   
    fseek(file_two, 0, SEEK_END);
    spu->size_code = ftell(file_two);
    rewind(file_two);

    spu->code = (int*) calloc(spu->size_code, sizeof(int));

    for (int i = 0; i < spu->size_code; i++)
    {
        fscanf(file_two, "%d", &((spu->code)[i]));    
    }

    stackCtor(&spu->stk, &spu->hash);
    spu->ip = 0;
    int a = 1;
    while(a != 0)
    {

        switch(spu->code[spu->ip])
        {
            case HLT: //hlt
            {
                a = 0;
                free(spu->code);
                //fclose(file_two);
                stackDestroy(&spu->stk, &spu->hash);
                return;
                break;
            }
            case PUSH:// push
            {
                push_start(spu);
                break;
            }
            case ADD: // сложение двух цифр add
            {
                int a1 = stackPop(&spu->stk,&spu->hash);
                int a2 = stackPop(&spu->stk,&spu->hash);
                stackPush(&spu->stk, a1 + a2, &spu->hash);
                spu->ip += 1;
                break;
            } 
            case SUB:// вычитание sub
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 - a1, &spu->hash);
                spu->ip += 1;
                break;
            }
            case MUL:// умножение mul
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 * a1, &spu->hash);   
                spu->ip += 1;
                break; 
            }
            case DIV:// деление div
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 / a1, &spu->hash);   
                spu->ip += 1;
                break;     
            }
            case SQRT:// возведение в квадрат sqrt
            {
                StackElem_t a1 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a1 * a1, &spu->hash);   
                spu->ip += 1;
                break; 
            }
            case SIN:// синус sin
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                stackPush(&spu->stk, sin(a1), &spu->hash);   
                spu->ip += 1;
                break;
            }
            case DUMP: // вывод всего стэка dump
            {
                processorDump(spu);
                spu->ip += 1;                                 // cpu
                //printf("%d\n", (spu->code)[spu->ip]);
                break;
            }
            case OUT_: // вывод последнего элемеента стэка out
            {
                StackElem_t el_1 = 0;
                el_1 = stackPop(&spu->stk,&spu->hash);
                spu->ip += 1;
                printf("out: %lg\n",el_1);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case COS: // косинус cos
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                stackPush(&spu->stk, cos(a1), &spu->hash);   
                spu->ip += 1;
                break;
            }
            case JMP: // jmp
            {
                spu->ip = spu->code[spu->ip + 1];
                break;
            } 
            case JA: // ja
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 > el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                else
                {
                    spu->ip += 2;
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case JAE: // jae
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 >= el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }else
                {
                    spu->ip += 2;
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case JB: // jb
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 < el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                else
                {
                    spu->ip += 2;
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case JBE: // jbe
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 <= el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                else
                {
                    spu->ip += 2;
                }

                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case JE: // je
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (compare(el_1,el_2) == 0) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                else
                {
                    spu->ip += 2;
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case JNE: // jne
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (compare(el_1,el_2) != 0) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                else
                {
                    spu->ip += 2;
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case POP: // pop ax
            {
                pop_start(spu);
                break;
            }
            case IN_:
            {
                int argg = 0;
                printf("in:\n");
                scanf("%d", &argg);
                stackPush(&spu->stk, argg, &spu->hash);
                spu->ip++;
                break;
            }
            case ROOT:
            {
                StackElem_t arg = stackPop(&spu->stk, &spu->hash);
                if (arg >= 0)
                {
                    stackPush(&spu->stk, (int) sqrt(arg), &spu->hash);
                }
                else
                {
                    printf("ERROR argument for root < 0\n");
                }    
                spu->ip++;
                break;
            }
            default:
            {
                exit(EXIT_SUCCESS);
            }

        }

    }
}
void processorDump(SPV* spu)
{
    printf("-------------------------------------------------------------------------------------------\n");
    stackDump(&spu->stk,&spu->hash);
    printf("elemenet in code:\n");
    for (int i = 0; i < spu->size_code; i++)
    {
        printf("%d ",(spu->code)[i]);
    }
    printf("\n");
    printf("element in register:\n");
    for (int i = 0; i < amount_registers; i++)
    {
        printf("%g ",(spu->registers)[i]);
    }
    printf("\n");
    printf("ip: %d\n", spu->ip);
    printf("-------------------------------------------------------------------------------------------\n");
    printf("\n\n\n\n");



}

int GetArg(SPV* spu)
{
    spu->ip++;
    int argType = (spu->code)[spu->ip];
    spu->ip++;
    return argType;
}

void push_start(SPV* spu)
{
    int arg = GetArg(spu);
    if (arg & stack_code)
    {
        stackPush(&spu->stk, (StackElem_t) (spu->code)[spu->ip], &spu->hash);
        spu->ip++;
    }
    else if (arg & register_code)
    {
        int num_reg = spu->code[spu->ip];
        stackPush(&spu->stk, spu->registers[num_reg], &spu->hash);
        spu->ip ++;   
    }
                /*if (arg & 3)
                {
                    int addr_RAM
                }*/    
}

void pop_start(SPV* spu)
{
    int arg = GetArg(spu);
    if (arg & stack_code)
    {

        int count_pop = spu->code[spu->ip];
        for (int i = 0; i < count_pop; i++)
        {
            stackPop(&spu->stk,&spu->hash);
 
        }    
        spu->ip++;
    }
    else if (arg & register_code)
    {
        spu->registers[spu->code[spu->ip]] = stackPop(&spu->stk,&spu->hash);
        spu->ip++;        
    }
}