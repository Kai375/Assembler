 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"
 
   /*Checks the validity of the given file. Specifically, that it contains '.as' at its postfix.*/

int valid_Assembly_File(char *file)
{
   int i, found_dot = -1;

   for(i = 0; i < strlen(file); i++)
   {
      if (file[i] == '.')
      {
	      found_dot = i;

 	      i = strlen(file);
      }
   }

   if(found_dot+3 <= strlen(file) && file[found_dot+1] == 'a' && file[found_dot+2] == 's' && file[found_dot+3] == '\0')
   {
      return SUCCESS;
   }

   return ERROR;
}


  /*Cleans the input from spaces and tabs.*/

  void remove_Space_And_Tab(char *input)
{
   int n = 0, i = 0;

   while(input[i] != '\0') 
   {

      if(input[i] != ' ' && input[i] !=  '	') 
      {
	      input[n] = input[i]; 

	      n++; 
      }

      i++;

   }
	
   input[n] = '\0';

   return;
}

   /*Returns the type of the input.*/

int check_Type(char *input, int line, int *flag, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table)
{
        int i = 0, label_length = 0;
 
       if(input[0] == '\n')
       {
            return EMPTY_LINE;
       }
       else if(input[0] == ';')
       {
            return COMMENT;
       }
   
         /*Checks the position of the label.*/

   while(input[i] != '\0') 
   {
      if(input[i] == ':') 
      {
	        label_length = i+1;

	       (*flag)++;
      }
          i++;
   }

   /*Checks if the input is a command line.*/

   for(i = STOP_COMMAND; i >= 0; i--)
   {

      if(!strncmp(input+label_length,command_Table[i][0],strlen(command_Table[i][0])))
      {
	        return COMMAND;
      }
   } 

   /*Checks if the input is an instruction line. */

   for(i = 0; i < INSTRUCTIONS; i++)
   {
      if(!strncmp(input + label_length, instruction_Table[i], strlen(instruction_Table[i])))
      {
	       if(i == ENTRY_INSTRUCTION)
	       {
	          return ENTRY;
	       }  
	       else if(i == EXTERN_INSTRUCTION)
	       {
	         return EXTERN;
	       }
	         return INSTRUCTION;
      }
   }

   return UNDEFINED;
}

   /*Copies the label (if present).*/

   void copy_Label(char *label, char *input, int *errors, int line)
{
   char *temp;

   temp = strtok(input, ":\n");

   /*Checks for valid length.*/

   if (strlen(temp) > MAX_LABEL_LENGTH)
   {
      printf("Line %d: Label \"%s\" length is exceeded.\n",line,temp);

      (*errors)++;

      return;
   }

   strcpy(label, temp);

   return;
}

  /*Check the validity of the label.*/

   int valid_Label(char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table, char *input, int length, int line)
{
   int i;

   /*Checks to see if the first letter of the label is a capital or small letter.*/

   if (!('a' <=  *input && *input <= 'z') && !('A' <=  *input && *input <= 'Z') && *input != '\0')
   {
      printf("Line %d: First letter of the label is invalid.\n",line);

      return ERROR;
   }

   /*Checks to see that the label isn't a command.*/

   for(i = STOP_COMMAND; i >= 0; i--)
   {
      if(!strncmp(input,command_Table[i][0],strlen(command_Table[i][0])) )
      {
	     if(*(input+strlen(command_Table[i][0])) == '\0')
	     {
            printf("Line %d: Label can not be a command.\n",line);

            return ERROR;
	     }
      }
   }

   /*Checks to see that the label isn't an instruction.*/

   for(i = 0; i < INSTRUCTIONS; i++)
   {
      if(!strncmp(input,instruction_Table[i]+1,strlen(instruction_Table[i])-1) )
      {
	     if(*(input+strlen(instruction_Table[i])-1) == '\0')
	     {
            printf("Line %d: Label can not be an instruction.\n",line);

            return ERROR;
	    }
      }
   }
 
   input++;
   
   /*Checks to see that all the characters in the label are either a capital letter, small letter or a number.*/

   while(*input != '\0' && *input != '\n')
   {

      if(!('a' <=  *input && *input <= 'z') && !('A' <=  *input && *input <= 'Z'))
      {
	     if(!('0' <= *input && *input <= '9'))
	     {
            printf("Line %d: Illegal label.\n",line);
            
            return ERROR;
	     }
      }

      input++;
   }

   return SUCCESS;
}
