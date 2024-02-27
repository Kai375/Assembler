/*Declarations of different data types, command, flags and constants.*/

#define SUCCESS 0
#define ERROR 1

#define MAX_INPUT_LENGTH 80
#define MAX_LABEL_LENGTH 31

/*The given limit of 2^25-1.*/

#define MEMORY_LIMIT 33554431

/*This is the factors for the type of file- ".ob\0" length 4, ".ent\ext\0" length 5.*/

#define TYPE_OF_FILE_4 4
#define TYPE_OF_FILE_5 5

#define TOTAL_COMMAND_COLS 4
#define STOP_COMMAND 26
#define I_COMMAND_START 8
#define J_COMMAND_START 23
#define INSTRUCTIONS 6
#define ENTRY_INSTRUCTION 4
#define EXTERN_INSTRUCTION 5

#define EMPTY_LINE 10
#define COMMENT 20
#define ENTRY 30
#define EXTERN 40
#define COMMAND 50
#define INSTRUCTION 60
#define UNDEFINED 70

#define SYMBOL 100
#define DATA 200
#define BMC 300
#define VALIDITY 400

#define TYPE 1
#define FUNCT 2
#define OPCODE 3

#define OPCODE_FIELD 6
#define FUNCT_FIELD 5
#define RS_FIELD 5
#define RT_FIELD 5
#define RT_FIELD 5
#define NOT_IN_USE 6
#define IMMED_FIELD 16
#define ADDRESS_FIELD 25

#define DH 0
#define DW 1
#define DB 2
#define ASCIZ 3

#define TOTAL_REGISTERS 31
#define BASE10 10

#define FOUR_BYTES 32
#define TWO_BYTES 16
#define BYTE 8
#define DW_ADDRESS_JUMP_FACTOR 4 
#define DH_ADDRESS_JUMP_FACTOR 2
#define COMMAND_JUMP_FACTOR 4

#define OUTPUT_LINE_LENGTH 4
#define NEW_LINE 4

#define BGT_OPCODE 18
#define BNE_OPCODE 15

/*Declarations of data structures and their pointers.*/

typedef struct SymbolList * symbol_ptr;
typedef struct CodeList * bmc_ptr;
typedef struct DataList * data_ptr;
typedef struct OnHoldList * validity_ptr;

typedef struct 
{

   unsigned int not_in_use : 6;
   unsigned int funct : 5;
   unsigned int rd : 5;
   unsigned int rt : 5;
   unsigned int rs : 5;
   unsigned int opcode : 6;

}commandR;

typedef struct 
{

   int immed : 16;
   unsigned int rt : 5;
   unsigned int rs : 5;
   unsigned int opcode : 6;

}commandI;

typedef struct 
{

   int address : 25;
   unsigned int reg : 1;
   unsigned int opcode : 6;

}commandJ;

typedef union 
{
   char m[4];
   commandR R;
   commandI I;
   commandJ J;

}Mila;

struct SymbolList 
{
   char symbol[MAX_LABEL_LENGTH];
   int address;
   char *type;
   char *opt_type;
   symbol_ptr next;
}; 

struct CodeList
{
   char var[MAX_LABEL_LENGTH];
   char type;
   int addr;
   Mila mila;
   bmc_ptr next;
};

struct DataList 
{
   char *type;
   int value;
   int address;
   data_ptr next;
};

struct OnHoldList
{
   char toCheck[MAX_LABEL_LENGTH];
   int line;
   validity_ptr next;
};

/*Function declarations
Function index menu- their appearances here correspond to the appearance in their respective file throughout the project. */

/*ProjectOutput.c*/
void final_Output(bmc_ptr b, data_ptr d, symbol_ptr s, char *end_result, int ic, int dc);
void free_List(void **list, int t);

/*The_Passsages.c*/
void the_Passages(char ** argv, int argc, FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, validity_ptr *vp, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table);

/*First_Passsage.c*/
void firstPassage(FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, validity_ptr *vp, int *errors, int *IC, int *DC, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS]);

/*Second_Passage.c*/
void secondPassage(FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, int *errors, int IC, int DC, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS]);

/*input_Proccessor.c*/
int valid_Assembly_File(char *file);
void remove_Space_And_Tab(char *input);
int check_Type(char *input, int line, int *flag, char *command_able[][TOTAL_COMMAND_COLS], char **instruction_Table);
void copy_Label(char *label, char *input, int *errors, int line);
int valid_Label(char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table, char *input, int length, int line);

/*instruction_Organizer.c*/
void retrieve(char *content, int table_idx, int *addr, data_ptr *d);
void update_Data_Address(data_ptr *data, int addr);

/*Symbol_Management.c*/
void add_To_Symbol_List(char *sym, int line_type, int addr, symbol_ptr *s);
void update_Symbol_Address(symbol_ptr *symbols, int addr);
void update_Symbols_Entry(char *sym, symbol_ptr *s, int *errors);

/*Assembly_To_Binary.c*/
void convert(char *ty, char *ft, char *oc, char *content, int addr, bmc_ptr *bmc);
void check_Validity_Of_Variables(validity_ptr *vp, char *temp, int line);
void update_BMC_Adresses(symbol_ptr s, bmc_ptr *b);

/*First_Passage_Error_Check.c*/
int R_Type_Error_Check(char *input, char *type, int length, int line);
int I_Type_Error_Check(validity_ptr *vp, char *input, char *type, int length, int line);
int J_Type_Error_Check(validity_ptr *vp, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS], char *input, char *opcode, int length, int line);
int Data_Error_Check(char *input, int table_idx, int line);

/*Second_Passage_Error_Check.c*/
void pre_Second_Passage_Error_Check(symbol_ptr symbols, bmc_ptr b, validity_ptr vp, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table, int *errors);

/*Second_Passage_Error_Utility.c*/
void all_Variables_Defined(symbol_ptr s, validity_ptr sb, int *errors);
void all_Variables_Defined_Once(symbol_ptr s, int *errors);
void valid_Variables(validity_ptr vp, int *errors, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table);
void conditional_Branching_Check(symbol_ptr s, bmc_ptr b, int *errors);
