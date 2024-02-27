#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

int main(int argc, char *argv[])
{
   char *command_Table[27][4] = { {"add", "R", "1", "0"},   {"sub", "R", "2", "0"},   {"and", "R", "3", "0"},   {"or", "R", "4", "0"},   {"nor", "R", "5", "0"},   {"move", "R", "1", "1"},   {"mvhi", "R", "2", "1"},   {"mvlo", "R", "3", "1"},    {"addi", "I", "constant", "10"},   {"subi", "I", "constant", "11"},   {"andi", "I", "constant", "12"},
                                  
   {"ori", "I", "constant", "13"},   {"nori", "I", "constant", "14"},   {"bne", "I", "variable", "15"},   {"beq", "I", "variable", "16"},   {"blt", "I", "variable", "17"},   {"bgt", "I", "variable", "18"},   {"lb", "I", "constant", "19"},    {"sb", "I", "constant", "20"},   {"lw", "I", "constant", "21"},   {"sw", "I", "constant", "22"},

   {"lh", "I", "constant", "23"},   {"sh", "I", "constant", "24"},   {"jmp", "J", "0", "30"},   {"la", "J", "0", "31"},   {"call", "J", "0", "32"},   {"stop", "J", "0", "63"}

   };

   char *instruction_Table[6] = {".dh", ".dw", ".db", ".asciz", ".entry", ".extern"};

   /*Declarations of various pointers for different data types throughout the program.*/

   FILE *fp = NULL;

   bmc_ptr bmc = NULL;

   symbol_ptr symbols = NULL;

   data_ptr data = NULL;

   validity_ptr vp = NULL;

   /*This is the call to the passages function that holds 1st and 2nd passages.*/

   the_Passages(argv, argc, fp, &bmc, &symbols, &data, &vp, command_Table, instruction_Table);
	
   return 0;
}