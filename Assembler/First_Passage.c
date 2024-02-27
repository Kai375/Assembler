#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

  /*The first passage's job is to recieve and procees data for validity; such as label check, command check and data check.*/

void firstPassage(FILE *fp, bmc_ptr *bmc, symbol_ptr *symbols, data_ptr *data, validity_ptr *vp, int *errors, int *IC, int *DC, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS])
{
    /*ATTENTION: since these statements are not referenced anywhere in the pdf, the libertey has been taken to ingnore them.
    1. A label can't be of type .extern and code.
    2. A label can't be of type .extern and data.
    3. A label can't be of type data and code.
    4. A label can't be of type .entry alone.*/
   
   /*The function's variables.*/

    int label_length = 0, instruction_length = 0, i = 0, label_flag = 0, line = 1;

   char input[MAX_INPUT_LENGTH+1], label[MAX_LABEL_LENGTH+1];

   char content[MAX_INPUT_LENGTH+1];

   fgets(input,MAX_INPUT_LENGTH+1, fp);

   /*The while loop processes the input from the file, line by line.*/

   while(!feof(fp))
    {

      remove_Space_And_Tab(input);

      /*Checks for the given length of 80.*/

      if(strlen(input) == MAX_INPUT_LENGTH && input[strlen(input)-1] != '\n' && input[strlen(input)-1] != '\0')
      {
         printf("Line %d: input's length is too long.\n",line);

         (*errors)++;
      }

      /*While the loop is running, the switch case checks for the input's type, by case to case basis.*/

      switch(check_Type(input, line, &label_flag, command_Table, instruction_Table))
      {
	      case EMPTY_LINE:

	      case COMMENT:

	         break;

	      case ENTRY:

	         if(label_flag)
	         {
	            copy_Label(label,input,errors,line);

	            label_length = strlen(label);
	         }
	         else
	         {
	            label_length = 0;
	         }

	         /*Takes the label that comes after the optional label and .entry and checks if it is legal. */

	         copy_Label(label,input + label_length + strlen(".entry"), errors, line);

	         if(valid_Label(command_Table, instruction_Table, label, strlen(label), line))
  	         {
	            (*errors)++;
	         }
	    
 	         break;

	      case EXTERN: 

	        if(label_flag)
	        {            
	           copy_Label(label,input,errors,line);

	           label_length = strlen(label);
	        }
	        else
	        {
	           label_length = 0;
	        }

	       /*Takes the label that comes after the optional label and .extern and checks if it is legal, if so adds it to the symbol list. */

	       copy_Label(label,input + label_length + strlen(".extern"), errors, line);

	       if(valid_Label(command_Table, instruction_Table, label, strlen(label), line))
  	       {
	          (*errors)++;
	       }	
 	       else 
 	       {
	          add_To_Symbol_List(label,EXTERN, 0, symbols);   
	       }    

	       break;
		 		
	      case COMMAND: 

             /*Takes the label at the beginning of the line (if there is) and adds it to symbol list.*/

	         if(label_flag)
	         {
	            copy_Label(label,input,errors,line);

 	            add_To_Symbol_List(label,COMMAND,*IC,symbols);

	            if(valid_Label(command_Table, instruction_Table, label, strlen(label), line))
  	            {
		           (*errors)++;

		           break;
	            }

	           label_length = strlen(label) + 1;

	         }
 	         else 
	         {
	           label_length = 0;
	         }

            /*The for loop goes through the command table and finds the type of command within the input, whether it is R I or J.*/

	        for(i = STOP_COMMAND; i >= 0; i--)
            {
	           if(!strncmp(input + label_length, command_Table[i][0], strlen(command_Table[i][0])))
	           {
		          instruction_length = label_length + strlen(command_Table[i][0]);

                  if(i < I_COMMAND_START)
		          {     
		             if(R_Type_Error_Check(input + instruction_length,command_Table[i][OPCODE], strlen(input + instruction_length), line))
		             {
			            (*errors)++;
		             }
		          }
 	 	          else if(i < J_COMMAND_START)
		          {
		             if(I_Type_Error_Check(vp, input + instruction_length, command_Table[i][FUNCT], strlen(input + instruction_length), line))
		             {
			            (*errors)++;
		             }
		          }
	 	          else if (i <= STOP_COMMAND)
		         {
        	        if(J_Type_Error_Check(vp,instruction_Table, command_Table, input+instruction_length, command_Table[i][OPCODE], strlen(input + instruction_length), line))
		            {
	         		   (*errors)++;
		            }
		         }
		  
  		        /*In case, no errors occured, the command will be proceesed into its selected data structure. */

		       if(!(*errors))
		       {
		          strcpy(content, input + instruction_length);

		          convert(command_Table[i][TYPE], command_Table[i][FUNCT], command_Table[i][OPCODE], content, *IC, bmc);
		       }

		       /* -1 to signal the loop's end. */

		       i = -1;

	       }
        }

	         (*IC) += COMMAND_JUMP_FACTOR; 

	         break;

	      case INSTRUCTION:

             /*Takes the label at the beginning of the line (if there is) and adds it to symbol list.*/

	         if(label_flag)
             {
	            copy_Label(label, input, errors, line);

 	            add_To_Symbol_List(label, INSTRUCTION, *DC, symbols);

	            if(valid_Label(command_Table, instruction_Table, label, strlen(label), line))
  	            {
		          (*errors)++;

		          break;
	            }

	            label_length = strlen(label)+1;
	         }
	         else 
             {
	            label_length = 0;
	         }

	        /*The for loop goes through the instruction table and finds the type of data within the input, whether it is .db .dh .dw .asciz.*/

	        for(i = 0; i < INSTRUCTIONS - 2; i++)
     	    {
	           if(!strncmp(input+label_length,instruction_Table[i],strlen(instruction_Table[i])))
	           {
                  if(Data_Error_Check(input + label_length + strlen(instruction_Table[i]), i, line))
		          {
		             (*errors)++;
		          }
		          else
		          {
		             strcpy(content, input + label_length + strlen(instruction_Table[i]));

		             retrieve(content, i, DC, data);
		          }

		          /*Signals the end of the loop.*/

		          i = 6;
	           }
	        } 

	        break;

	    default:

	    printf("\nLine %d: Unidentified input line.\n", line);

	      (*errors)++;
      }

      fgets(input, MAX_INPUT_LENGTH + 1, fp);

      /*In case the memory will exceed 2^25-1 milot.*/

      if(*IC > MEMORY_LIMIT)
      {
	       puts("Memory limit surpassed.");

	      (*errors)++;
      }

      line++;

      label_length = 0;

      label_flag = 0;

      strcpy(label, "\0");
   }

   /*End of first passage, incrementing the data addresses accordingly, in preparation for the next passage.*/

   update_Symbol_Address(symbols, *IC);

   update_Data_Address(data, *IC);
  
   return;
}