#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

/*The passages hold the 1st and 2nd passages, as previously mentioned in the main program.*/

void the_Passages(char ** argv, int argc, FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, validity_ptr *vp, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table)
{
   int number_Of_Files = 1, errors = 0, IC = 100, DC = 0;
   
   char *end_result;

   while(number_Of_Files < argc) 
   {
      printf("\n\n%s\n\n",argv[number_Of_Files]);

      /*Check if the file is valid (Assembly file).*/

      if(valid_Assembly_File(argv[number_Of_Files]))
      {
	      puts("Invalid file.");

	      errors++;
      }
      else
      {
   	     /*Opens the file and allocates memory in advance to the .ob file.*/

         fp = fopen(argv[number_Of_Files],"r");

         end_result = malloc(strlen(argv[number_Of_Files])+2);

         if(!fp) 
         {
             printf("\nCould not open file.\n"); 

  	         errors++;
         }

         if(!end_result)
         {
	         puts("Could not allocate memory for output file");

	         errors++;
         }	 
      }

      /*In case, the program hadn't stumbled upon errors up to this point, the program will commence the first passage.*/

      if(!errors)
      {
         strcpy(end_result, strtok(argv[number_Of_Files], "."));

         /*Below is the call to the first passage- it proccesses the labels and their addressses and the data for their validity. */

         firstPassage(fp,bmc,symbols,data,vp,&errors,&IC,&DC,instruction_Table,command_Table);
      }

      /*In case, no errors occured during the first passage, the program will proceed to the pre second error check phase.*/

      if(!errors)
      {
        /*Checks the validity of the data processed so far in preparation for the second passage.*/

         pre_Second_Passage_Error_Check(*symbols,*bmc,*vp,command_Table, instruction_Table,&errors);

         /*In case, no errors occured as well, the program will proceed to the second passage.*/

          if(!errors)
	      {
	          fseek(fp,0,SEEK_SET);

              /*Below is the call to the second passage- it completes the missing addresses and entry type varaibles. */

	          secondPassage(fp,bmc,symbols,data,&errors,IC,DC,instruction_Table,command_Table);

	          if(!errors)
	          {
	             final_Output(*bmc,*data,*symbols,end_result, IC, DC);
	          }
	      }
      }

      /*Freeing/resetting parameters accordingly for the next file in line.*/

      free_List((void **) bmc, BMC);

      free_List((void **) data, DATA);

      free_List((void **) symbols, SYMBOL);

      free_List((void **) vp, VALIDITY);

      /*In case there is end result.*/
	
      if(!end_result) 
      {
        free(end_result);
      }
      
      end_result = NULL;
	
      *bmc = NULL;

      *symbols = NULL;

      *data = NULL;

      *vp = NULL;

      errors = 0; 

      IC = 100; 

      DC = 0;

      /*Closes the file.*/

      if(fp) 
      {
	      fclose(fp);

         fp = NULL;
      }

      number_Of_Files++;
   }

   return;
}