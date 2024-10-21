typedef double StackElem_t; 
#define DEBUG

enum ERRORS
{
    OKEY                      = 0,
    ERROR_CTOR                = 1,
    ERROR_PUSH                = 2,
    ERROR_POP                 = 3,
    ERROR_DESTROY             = 4,
    ERROR_left_struct_canary  = 5,
    ERROR_right_struct_canary = 6,
    ERROR_left_stk_canary     = 7,
    ERROR_right_stk_canary    = 8,
    ERROR_hash_array          = 9,
    ERROR_hash_struct         = 10
};

enum canary
{
    left_stk_canary_values           = 0xDEAD,
    right_stk_canary_values          = 0xDEAD,
    left_struct_canary_values        = 0xDEAD,
    right_struct_canary_values       = 0xDEAD
};

enum num_commands
{
    HLT    = -1,
    PUSH   =  1,
    ADD    =  2,
    SUB    =  3,
    MUL    =  4,
    DIV    =  5,
    SQRT   =  6,
    SIN    =  7,
    DUMP   =  8,
    OUT_   =  9,
    COS    =  10,
    JMP    =  11,
    JA     =  12,
    JAE    =  13,
    JB     =  14,
    JBE    =  15,
    JE     =  16,
    JNE    =  17,
    PUSHR  =  18,
    POP    =  19,
    AX_num =  1,
    BX_num =  2,
    CX_num =  3,
    DX_num =  4
     
};

enum OTHERS
{
    START_SIZE        = 10,
    NULL_ELEMENT_DATA = 0xBEDA,
    LABEL             = 0xDEAD,
    stack_code        = 1,
    register_code     = 2   
};

struct Stack_t
{
    StackElem_t  left_struct_canary  = left_struct_canary_values;
    StackElem_t* data                {};
    int          size                = 0;
    int          capacity            = 0;
    int          error_code[10]      = {0};
    int          error_code_nume     = 0;
    int          amount_error        = 0;
    StackElem_t  right_struct_canary = right_struct_canary_values;
};

struct Hash_struct
{
    unsigned long long hash_array  = 0;
    unsigned long long hash_struct = 0;
};

struct SPV
{
    int* code            = {};
    int* registers       = {};
    int ip;
    int size_code;
    Stack_t stk          = {};
    Hash_struct hash     = {};
    int amount_registers = 4;
    int RAM              = {};
    int labels[4]        =  {-1};
};

int  stackPop(Stack_t* stk, Hash_struct* hash);

int  stackPush(Stack_t* stk, StackElem_t new_element, Hash_struct* hash);

int  stackCtor(Stack_t* stk, Hash_struct* hash); // static

void stackDump(Stack_t* stk, Hash_struct* hash);

int  stackDestroy(Stack_t* stk, Hash_struct* hash);

int  stackOkey(Stack_t* stk, Hash_struct* hash);

void stackCheck(Stack_t* stk, Hash_struct* hash);

int compare(StackElem_t a, StackElem_t b);

unsigned long long hash_func_array(Stack_t* stk);

unsigned long long hash_func_struct(Stack_t* stk);

void processorDump(SPV* spu);

int GetArg(SPV* spu);
