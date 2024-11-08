#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

#include "stack3.h"
#include "processor1.h"


static void make_el_struct(SPV* spu, int num_com, func_def func);

static void make_struct(SPV* spu);

static void run_with_struct(SPV* spu);

static void push_start(SPV* spu);

static void pop_start(SPV* spu); // static

static void do_hlt(SPV* spu);

static void do_push(SPV* spu);

static void do_add(SPV* spu);

static void do_sub(SPV* spu);

static void do_mul(SPV* spu);

static void do_div(SPV* spu);

static void do_sqrt(SPV* spu);

static void do_dump(SPV* spu);

static void do_out(SPV* spu);

static void do_jmp(SPV* spu);

static void do_ja(SPV* spu);

static void do_jb(SPV* spu);

static void do_pop(SPV* spu);

static void do_in(SPV* spu);

static void do_root(SPV* spu);

static void do_jne(SPV* spu);

static void do_je(SPV* spu);

static void do_jae(SPV* spu);

static void do_jbe(SPV* spu);


int main()
{
    printf("c\n");
    SPV spu = {};
    stackCtor(&spu.stk, &spu.hash);
    stackCtor(&spu.addrs_ret, &spu.hash_ret);
    make_struct(&spu);
    run_with_struct(&spu);

    return 0;
}


void processorDump(SPV* spu)
{
    printf("-------------------------------------------------------------------------------------------\n");
    stackDump(&spu->stk,&spu->hash);
    printf("---------------\n");
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
    printf("\n\n---------------");
    stackDump(&spu->addrs_ret, &spu->hash_ret);
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

void do_hlt(SPV* spu)
{
    spu->ip++;
    free(spu->code);
    //fclose(file_two);
    stackDestroy(&spu->stk, &spu->hash);
    stackDestroy(&spu->addrs_ret, &spu->hash_ret);
    exit(OKEY);
}

void do_push(SPV* spu)
{
    push_start(spu);
}

void do_add(SPV* spu)
{
    int a1 = stackPop(&spu->stk,&spu->hash);
    int a2 = stackPop(&spu->stk,&spu->hash);
    stackPush(&spu->stk, a1 + a2, &spu->hash);
    spu->ip += 1;    
}

void do_sub(SPV* spu)
{
    StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
    StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
    stackPush(&spu->stk, a2 - a1, &spu->hash);
    spu->ip += 1;
}

void do_mul(SPV* spu)
{
    StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
    StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
    stackPush(&spu->stk, a2 * a1, &spu->hash);   
    spu->ip += 1;
}

void do_div(SPV* spu)
{
    StackElem_t a1 = stackPop(&spu->stk,&spu->hash);
    StackElem_t a2 = stackPop(&spu->stk, &spu->hash);
    stackPush(&spu->stk, a2 / a1, &spu->hash);   
    spu->ip += 1;
}

void do_sqrt(SPV* spu)
{
    StackElem_t a1 = stackPop(&spu->stk, &spu->hash);
    stackPush(&spu->stk, a1 * a1, &spu->hash);   
    spu->ip += 1;    
}

void do_dump(SPV* spu)
{
    processorDump(spu);
    spu->ip += 1; 
}

void do_out(SPV* spu)
{
    StackElem_t el_1 = 0;
    el_1 = stackPop(&spu->stk,&spu->hash);
    spu->ip += 1;
    printf("out: %lg\n",el_1);
    stackPush(&spu->stk, el_1, &spu->hash);
}

void do_jmp(SPV* spu)
{
    spu->ip = spu->code[spu->ip + 1];
}

void do_call(SPV* spu)
{
    StackElem_t el = spu->ip + 2;
    stackPush(&spu->addrs_ret, el, &spu->hash_ret);
    spu->ip = spu->code[spu->ip + 1];
}
void do_ret(SPV* spu)
{
    int address_to_return_to_right_now = stackPop(&spu->addrs_ret, &spu->hash_ret);

    if (address_to_return_to_right_now < 0 || address_to_return_to_right_now > spu->size_code - 1)
    {
        fprintf(stderr, "Error: ret() is called for wrong ip\n");
    }

    spu->ip = address_to_return_to_right_now;

}

void do_ja(SPV* spu)
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
}
void do_jae(SPV* spu)
{
    StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
    StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
    if (el_1 >= el_2) 
    {
        spu->ip = spu->code[spu->ip + 1];
    }
    else
    {
        spu->ip += 2;
    }
    stackPush(&spu->stk, el_2, &spu->hash);
    stackPush(&spu->stk, el_1, &spu->hash);
}

void do_jb(SPV* spu)
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
}

void do_jbe(SPV* spu)
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
}

void do_je(SPV* spu)
{
    StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
    StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
    if (el_1 == el_2) 
    {
        spu->ip = spu->code[spu->ip + 1];
    }
    else
    {
        spu->ip += 2;
    }
    stackPush(&spu->stk, el_2, &spu->hash);
    stackPush(&spu->stk, el_1, &spu->hash);
}

void do_jne(SPV* spu)
{
    StackElem_t el_1 = stackPop(&spu->stk, &spu->hash);
    StackElem_t el_2 = stackPop(&spu->stk, &spu->hash);
    if (el_1 != el_2) 
    {
        spu->ip = spu->code[spu->ip + 1];
    }
    else
    {
        spu->ip += 2;
    }
    stackPush(&spu->stk, el_2, &spu->hash);
    stackPush(&spu->stk, el_1, &spu->hash);
}

void do_pop(SPV* spu)
{
    pop_start(spu);
}

void do_in(SPV* spu)
{
    int argg = 0;
    printf("in:\n");
    scanf("%d", &argg);
    stackPush(&spu->stk, argg, &spu->hash);
    spu->ip++;
}

void do_root(SPV* spu)
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
}

void run_with_struct(SPV* spu)
{
    FILE* file_two = fopen("file_two.txt", "r");
   
    fseek(file_two, 0, SEEK_END);
    spu->size_code = ftell(file_two);
    rewind(file_two);

    spu->code = (int*) calloc(spu->size_code, sizeof(int));
    
    for (int i = 0; i < spu->size_code; i++)
    {
        (spu->code)[i] = -1;
    }

    for (int i = 0; i < spu->size_code; i++)
    {
        fscanf(file_two, "%d", &((spu->code)[i]));    
    }

    stackCtor(&spu->stk, &spu->hash);
    spu->ip = 0;
    while(spu->code[spu->ip] != -1)
    {
        for (int i = 0; i < spu->amount_comands; i++)
        {
            if (spu->array_comands[i].num_code == spu->code[spu->ip])
            {
                spu->array_comands[i].func(spu);
            }
        }
    }
}

void make_struct(SPV* spu)
{
    spu->amount_comands = 0;
    make_el_struct(spu, HLT,  do_hlt);
    make_el_struct(spu, PUSH, push_start);
    make_el_struct(spu, ADD,  do_add);
    make_el_struct(spu, SUB,  do_sub);
    make_el_struct(spu, MUL,  do_mul);
    make_el_struct(spu, DIV,  do_div);
    make_el_struct(spu, SQRT, do_sqrt);
    make_el_struct(spu, DUMP, do_dump);
    make_el_struct(spu, OUT_, do_out);
    make_el_struct(spu, JMP,  do_jmp);
    make_el_struct(spu, JA,   do_ja);
    make_el_struct(spu, JB,   do_jb);
    make_el_struct(spu, POP,  pop_start);
    make_el_struct(spu, IN_,  do_in);
    make_el_struct(spu, ROOT, do_root);
    make_el_struct(spu, CALL, do_call);
    make_el_struct(spu, RET,  do_ret);
    make_el_struct(spu, JAE,  do_jae);
    make_el_struct(spu, JBE,  do_jbe);
    make_el_struct(spu, JE,   do_je);
    make_el_struct(spu, JNE,  do_jne);
}

void make_el_struct(SPV* spu, int num_com, func_def func)
{
    spu->array_comands[spu->amount_comands].num_code = num_com;
    spu->array_comands[spu->amount_comands].func = func;  
    spu->amount_comands++;  
}