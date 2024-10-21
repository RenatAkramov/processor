#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "processor1.h"

void run(SPV* spu);

int main()
{
    SPV spu = {};
    printf("huiiiii\n");
    run(&spu);
}

void run(SPV* spu)
{
    FILE* file_two = fopen("file_two.txt", "r");
   
    fseek(file_two, 0, SEEK_END);
    spu->size_code= ftell(file_two);
    rewind(file_two);

    spu->registers = (int*) calloc(spu->amount_registers, sizeof(int));
    spu->code = (int*) calloc(spu->size_code, sizeof(int));

    for (int i = 0; i < spu->size_code; i++)
    {
        fscanf(file_two, "%d", &((spu->code)[i]));    
    }

    stackCtor(&spu->stk, &spu->hash);
    spu->ip = 0;
    int a = 1;
    while(a)
    {
        switch(spu->code[spu->ip])
        {
            case -1:
            {
                printf("huii");
                exit(EXIT_SUCCESS);
            }
            case 1:// push
            {
                int arg = GetArg(spu);
                printf("%d\n",arg);
                if (arg & 1)
                {
                    printf("%d\n", (spu->code)[spu->ip]);
                    stackPush(&spu->stk, (StackElem_t) (spu->code)[spu->ip], &spu->hash);
                    spu->ip++;
                    printf("%d\n", spu->ip);
                    break;
                }
                else if (arg & 2)
                {
                    int num_reg = spu->code[spu->ip];
                    stackPush(&spu->stk, spu->registers[num_reg], &spu->hash);
                    spu->ip ++;   
                    break;
                }
                /*if (arg & 3)
                {
                    int addr_RAM
                }*/
            }
            case 2: // сложение двух цифр add
            {
                int a1 = stackPop(&spu->stk,&spu->hash);
                int a2 = stackPop(&spu->stk,&spu->hash);
                printf("element stack pop: %d , %d\n", a1, a2);
                stackPush(&spu->stk, a1 + a2, &spu->hash);
                spu->ip += 1;
                break;
            } 
            case 3:// вычитание sub
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 - a1, &spu->hash);
                spu->ip += 1;
                break;
            }
            case 4:// умножение mul
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 * a1, &spu->hash);   
                spu->ip += 1;
                break; 
            }
            case 5:// деление div
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a2 / a1, &spu->hash);   
                spu->ip += 1;
                break;     
            }
            case 6:// возведение в квадрат sqrt
            {
                StackElem_t a1 = stackPop(&spu->stk, &spu->hash);
                stackPush(&spu->stk, a1 * a1, &spu->hash);   
                spu->ip += 1;
                break; 
            }
            case 7:// синус sin
            {
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                stackPush(&spu->stk, sin(a1), &spu->hash);   
                spu->ip += 1;
                break;
            }
            case 8: // вывод всего стэка dump
            {
                processorDump(spu);
                spu->ip += 1;
                break;
            }
            case 9: // вывод последнего элемеента стэка out
            {
                StackElem_t el_1 = 0;
                el_1 = stackPop(&spu->stk,&spu->hash);
                spu->ip += 1;
                printf("%lg",el_1);
                break;
            }
            case 10: // косинус cos
            {
                printf("ittttttttt");
                StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
                stackPush(&spu->stk, cos(a1), &spu->hash);   
                spu->ip += 1;
                break;
            }
            case 11: // jmp
            {
                spu->ip = spu->code[spu->ip + 1];
                printf("okk\n");
                break;
            } 
            case 12: // ja
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 > el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 13: // jae
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 >= el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 14: // jb
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 < el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 15: // jbe
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (el_1 <= el_2) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 16: // je
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (compare(el_1,el_2) == 0) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 17: // jne
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
                if (compare(el_1,el_2) != 0) 
                {
                    spu->ip = spu->code[spu->ip + 1];
                }
                stackPush(&spu->stk, el_2, &spu->hash);
                stackPush(&spu->stk, el_1, &spu->hash);
                break;
            }
            case 18: // pusr ax bx ...
            {
                int num_reg = spu->code[spu->ip + 1];
                stackPush(&spu->stk, spu->registers[num_reg], &spu->hash);
                spu->ip +=2;
            }
            case 19: // pop ax
            {
                StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
                (spu->registers)[spu->code[spu->ip + 1] = el_1];
            }

        }

    }
}
void processorDump(SPV* spu)
{
    stackDump(&spu->stk,&spu->hash);
    printf("elemenet in code:\n");
    for (int i = 0; i < spu->size_code; i++)
    {
        printf("%d ",(spu->code)[i]);
    }
    printf("\n");
    printf("element in register:\n");
    for (int i; i < spu->amount_registers; i++)
    {
        printf("%d ",(spu->registers)[i]);
    }
    printf("\n");
    printf("ip: %d\n", spu->ip);
    printf("\n");


}

int GetArg(SPV* spu)
{
    spu->ip++;
    int result = NULL_ELEMENT_DATA;
    int argType = (spu->code)[spu->ip];
    spu->ip++;
    return argType;
}