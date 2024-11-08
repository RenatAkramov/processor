struct SPV;
typedef double StackElem_t; 
typedef void(*func_def) (SPV*);
#define DEBUG


struct Stack_t;

struct Hash_struct;

enum num_commands
{
    HLT    =  0x00,
    PUSH   =  0x01,
    ADD    =  0x02,
    SUB    =  0x03,
    MUL    =  0x04,
    DIV    =  0x05,
    SQRT   =  0x06,
    DUMP   =  0x07,
    OUT_   =  0x08,
    JMP    =  0x09,
    JA     =  0x0A,
    JB     =  0x0B,
    POP    =  0x0C,
    IN_    =  0x0D,
    ROOT   =  0x0E,
    CALL   =  0x0F,
    RET    =  0x10,
    JAE    =  0x11,
    JBE    =  0x12,
    JE     =  0x13,
    JNE    =  0x14,
    AX_num =  0,
    BX_num =  1,
    CX_num =  2,
    DX_num =  3
};    

enum OTHERS
{
    LABEL             = 0xDEAD,
    stack_code        = 1,
    register_code     = 2,   
    amount_registers  = 4

};

struct proc_com
{
    int num_code;
    func_def func;

};


struct SPV
{

    int*        code                        = {};
    StackElem_t registers[amount_registers] = {0};
    int         ip                          = 0;
    int         size_code                   = 0;
    Stack_t     stk                         = {};
    Hash_struct hash                        = {};
    Stack_t     addrs_ret                   = {};
    Hash_struct hash_ret                    = {};
    struct proc_com array_comands[17]; 
    int         RAM[24]                     = {};
    int amount_comands;
};



