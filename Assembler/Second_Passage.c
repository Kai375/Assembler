#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

/*Completes the missing addresses and updates to the symbol list any .entry type data.*/

void secondPassage(FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, int *errors, int IC, int DC, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS])
{
   int label_length = 0, label_flag = 0, line = 1;

   char input[MAX_INPUT_LENGTH +1 ], label[MAX_LABEL_LENGTH + 1];

   fgets(input,MAX_INPUT_LENGTH, fp);

   remove_Space_And_Tab(input);

   /*The while loop goes through the input again to update any .entry type data.*/

   while (!feof(fp))
   {
      if(check_Type(input, line, &label_flag, command_Table, instruction_Table) == ENTRY)
      {
	       if(label_flag)
	       {
	          copy_Label(label,input,errors,line);
	          label_length = strlen(label);
	       }
	       else
	       {
	              label_length = 0;
	       }    
  
         /*This segment does the update part.*/

	       copy_Label(label, input + label_length + strlen(".entry"), errors, line);

	       update_Symbols_Entry(label, symbols, errors);		 		
      }

          fgets(input,MAX_INPUT_LENGTH, fp);

          remove_Space_And_Tab(input);

          line++;

          label_length = 0;

          label_flag = 0;

          label[0] = '\0';
   }

         /*Completes the missing addresses.*/

         update_BMC_Adresses(*symbols,bmc);
   
         return;
}