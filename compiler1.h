typedef double StackElem_t; 

struct COMPILERS;
typedef void (*func_def) (COMPILERS*);

#define DEBUG
#define ADDR_LABEL_0() compiler_struct->addr_lab++; compiler_struct->jmp_analysis = 0;
#define ADDR_LABEL_1() compiler_struct->addr_lab += 2; compiler_struct->jmp_analysis = 1;
#define CALL_ANALYSIS_0() compiler_struct->after_call = 0;
#define CALL_ANALYSIS_1() compiler_struct->after_call = 1;


struct COMANDS;

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
    START_SIZE        = 10,
    NULL_ELEMENT_DATA = 0xBEDA,
    LABEL             = 0xDEAD,
    stack_code        = 1,
    register_code     = 2   
};

struct LABELS
{
    int addr;
    char* label;
};

struct COMANDS
{
    char* name_comands;
    func_def func;
    func_def func_label;
    int com_code;
};

struct COMPILERS
{
    struct LABELS array_labels[10];
    struct COMANDS array_comands[30];
    FILE* file_one;
    FILE* file_two;
    char* data1;
    int amount_comands;
    int amount_labels = 0;
    int jmp_analysis;
    int addr_lab;
    int after_call;

};

