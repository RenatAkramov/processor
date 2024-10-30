typedef double StackElem_t; 
#define DEBUG

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
    IN_    =  20,
    ROOT   =  21,
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

struct COMPILERS
{
    struct LABELS array_labels[10];
    FILE* file_one;
    FILE* file_two;
    char* data1;
    int amount_comands;
    int amount_labels = 0;

};


void run_data(COMPILERS* compiler_struct);

int size_calculation(FILE* file_one);

void push_analysis_compiler(COMPILERS* compiler_struct);

void pop_analysis_compiler(COMPILERS* compiler_struct);

int label_analysis_compiler(COMPILERS* compiler_struct);

int jump_analysis(COMPILERS* compiler_struct);

int check_func(const char* txt_command , COMPILERS* compiler_struct);