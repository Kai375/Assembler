#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Data_File.h"

/*Checks R type command for various syntax errors and issues a detailed error message.*/
  
int R_Type_Error_Check(char *input, char *type, int length, int line)
{
   long val = 0;

   char *temp;

   if(length <= 1)
   {
      printf("Line %d: Missing registers.\n",line);

      return ERROR;
   }

   if(*input == ',')
   {
      printf("Line %d: Illegal comma.\n",line);

      return ERROR;
   }

   if(*input != '$')
   {
      printf("Line %d: Invalid register.\n",line);
      
      return ERROR;
   }

   if(*(input+1) == '\n' || *(input+1) == '\0' || !('0' <= *(input+1) && *(input+1) <= '9'))
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(!('0' <= *(input+1) && *(input+1) <= '9'))
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   }

   val = strtol(input+1, &temp, BASE10);

   if(val < 0 || TOTAL_REGISTERS < val)
   {
      printf("Line %d: Register out of bounds.\n",line);

      return ERROR;
   } 

   if(*temp == '\n' || *temp == '\0')
   {
      printf("Line %d: Missing registers.\n",line);

      return ERROR;
   }

   if(*temp != ',')
   {
      printf("Line %d: Missing comma.\n",line);

      return ERROR;
   } 

   if(*(temp+1) == ',')
   {
      printf("Line %d: Multiple consecutive commas.\n",line);

      return ERROR;
   }

   if(*(temp+1) == '\n' || *(temp+1) == '\0')
   {
      printf("Line %d: Missing registers.\n",line);

      return ERROR;
   }

   if(*(temp+1) != '$')
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   } 

   if(*(temp+2) == '\n' || *(temp+2) == '\0')
   {
      printf("Line %d: Missing registers.\n",line);

      return ERROR;
   }

   if(!('0' <= *(temp+2) && *(temp+2) <= '9'))
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   } 

   val = strtol(temp+2, &temp, BASE10);

   if(val < 0 || TOTAL_REGISTERS < val)
   {
      printf("Line %d: Register out of bounds.\n",line);

      return ERROR;
   } 

   if(!strcmp(type, "1"))
   {
      if(*temp != '\n' && *temp != '\0')
      {
         printf("Line %d: Extraneous input after end of command.\n",line);

         return ERROR;
      }

      return SUCCESS;
   }

   if(*temp == '\n' || *temp == '\0')
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(*temp != ',')
   {
      printf("Line %d: Missing comma.\n",line);

      return ERROR;
   } 

   if(*(temp+1) == ',')
   {
      printf("Line %d: Multiple consecutive commas.\n",line);

      return ERROR;
   }

   if(*(temp+1) == '\n' || *(temp+1) == '\0')
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(*(temp+1) != '$')
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   } 

   if(*(temp+2) == '\n' || *(temp+2) == '\0')
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(!('0' <= *(temp+2) && *(temp+2) <= '9'))
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   } 

   val = strtol(temp+2, &temp, BASE10);

   if(val < 0 || TOTAL_REGISTERS < val)
   {
      printf("Line %d: Register out of bounds.\n",line);

      return ERROR;
   } 

   if(*temp != '\n' && *temp != '\0')
   {
      printf("Line %d: Extraneous input after end of command.\n",line);

      return ERROR;
   }

   return SUCCESS;
}

/*Checks I type command for various syntax errors and issues a detailed error message.*/

int I_Type_Error_Check(validity_ptr *vp, char *input, char *type, int length, int line)
{
   long val = 0;

   char *temp;

   if(length <= 1)
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(*input == ',')
   {
      printf("Line %d: Illegal comma.\n",line);

      return ERROR;
   }

   if(*input != '$')
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   }

   if(*(input+1) == '\n' || *(input+1) == '\0' || !('0' <= *(input+1) && *(input+1) <= '9'))
   {
      printf("Line %d: Missing register.\n",line);

      return ERROR;
   }

   if(!('0' <= *(input+1) && *(input+1) <= '9'))
   {
      printf("Line %d: Invalid register.\n",line);

      return ERROR;
   }

   val = strtol(input+1, &temp, BASE10);

   if(val < 0 || TOTAL_REGISTERS < val)
   {
      printf("Line %d: Register out of bounds.\n",line);
      
      return ERROR;
   } 

   if(*temp == '\n' || *temp == '\0')
   {
      printf("Line %d: Missing parameters.\n",line);

      return ERROR;
   }

   if(*temp != ',')
   {
      printf("Line %d: Invalid parameter.\n",line);

      return ERROR;
   }

   if(*(temp+1) == ',')
   {
      printf("Line %d: Multiple consecutive commas.\n",line);

      return ERROR;
   }

   if(!strcmp(type,"constant"))  
   {
      if(*(temp+1) == '\n' || *(temp+1) == '\0')
      {
         printf("Line %d: Missing a constant.\n",line);

         return ERROR;
      }

      if(*(temp+1) != '+' && *(temp+1) != '-' && !('0' <= *(temp+1) && *(temp+1) <= '9'))
      {
         printf("Line %d: Invalid constant.\n",line);

         return ERROR;
      } 

      val = strtol(temp+1, &temp, BASE10);

      if( val < SHRT_MIN || USHRT_MAX < val) 
      {
         printf("Line %d: Constant out of bounds.\n",line);

         return ERROR;
      } 

      if(*temp == '\n' || *temp == '\0')
      {
         printf("Line %d: Missing register.\n",line);

         return ERROR;
      }

      if(*temp != ',')
      {
         printf("Line %d: Missing comma.\n",line);

         return ERROR;
      }

      if(*(temp+1) == ',')
      {
         printf("Line %d: Multiple consecutive commas.\n",line);

         return ERROR;
      }

      if(*(temp+1) == '\n' || *(temp+1) == '\0')
      {
         printf("Line %d: Missing register.\n",line);

         return ERROR;
      }

      if(*(temp+1) != '$')
      {
         printf("Line %d: Invalid register.\n",line);

         return ERROR;
      }

      if(!('0' <= *(temp+2) && *(temp+2) <= '9'))
      {
         printf("Line %d: Missing register.\n",line);

         return ERROR;
      }

      val = strtol(temp+2, &temp, BASE10);

      if(val < 0 || TOTAL_REGISTERS < val) 
      {
         printf("Line %d: Register out of bounds.\n",line);

         return ERROR;
      }

      if(*temp != '\n' && *temp != '\0') 
      {
         printf("Line %d: Extraneous input after end of command.\n",line);

         return ERROR;
      }
   }

   if(!strcmp(type, "variable")) 
   {
      if(*(temp+1) == '\n' || *(temp+1) == '\0')
      {
         printf("Line %d: Missing a register.\n",line);

         return ERROR;
      }

      if(*(temp+1) != '$')
      {
         printf("Line %d: Missing register.\n",line);

         return ERROR;
      } 

      if(*(temp+2) == '\n' || *(temp+2) == '\0')
      {
        printf("Line %d: Missing register.\n",line);

        return ERROR;
      }

      if(!('0' <= *(temp+2) && *(temp+2) <= '9'))
      {
         printf("Line %d: Invalid register.\n",line);

         return ERROR;
      } 

      val = strtol(temp+2, &temp, BASE10);

      if(val < 0 || TOTAL_REGISTERS < val)
      {
         printf("Line %d: Register out of bounds.\n",line);

         return ERROR;
      } 

      if(*temp == '\n' || *temp == '\0')
      {
         printf("Line %d: Missing variable.\n",line);

         return ERROR;
      }

      if(*temp != ',')
      {
         printf("Line %d: Missing comma.\n",line);

         return ERROR;
      }

      if(*(temp+1) == ',')
      {
         printf("Line %d: Multiple consecutive commas.\n",line);

         return ERROR;
      }

      if(*(temp+1) == '\n' || *(temp+1) == '\0')
      {
         printf("Line %d: Missing a variable.\n",line);

         return ERROR;
      }

      if(!('a' <=  *(temp+1) && *(temp+1) <= 'z') && !('A' <=  *(temp+1) && *(temp+1) <= 'Z'))
      {
         printf("Line %d: Invalid variable.\n",line);

         return ERROR;
      }

      temp = strtok(temp+1,"\n");
  
      if(strlen(temp) > MAX_LABEL_LENGTH-1)
      {
         printf("Line %d: Variable length is too long.\n",line);

         return ERROR;
      }

      check_Validity_Of_Variables(vp, temp, line);
   }

   return SUCCESS;
}

/*Checks J type command for various syntax errors and issues a detailed error message.*/

int J_Type_Error_Check(validity_ptr *vp, char **instruction_Table, char *command_Table[][TOTAL_COMMAND_COLS], char *input, char *opcode, int length, int line)
{
   long val = 0;

   char *temp = NULL;

   int i = 0;

   if(!strcmp(opcode,"63"))
   {
      if(input[0] != '\0' && input[0] != '\n')
      {
         printf("Line %d: Extraneous input after end of command.\n",line);

         return ERROR;
      }
      return SUCCESS;
   }

   if(length <= 1)
   {
      printf("Line %d: Missing parameter.\n",line);

      return ERROR;
   }

   for(i = 0; i < length; i++)
   {
      if(input[i] == ',')
      {
         printf("Line %d: Illegal comma.\n",line);

         return ERROR;
      }
   }

   if(!strcmp(opcode, "30"))
   {
      if(*input != '$' && !('a' <=  *input && *input <= 'z') && !('A' <=  *input && *input <= 'Z'))
      {
         printf("Line %d: Invalid parameter.\n",line);

         return ERROR;
      } 
      else if(*input == '$')
      {
   	     if(*(input+1) == '\n' || *(input+1) == '\0')
   	     {
      	    printf("Line %d: Missing register.\n",line);

            return ERROR;
   	     }

   	     if(!('0' <= *(input+1) && *(input+1) <= '9'))
   	     {
      	    printf("Line %d: Invalid register.\n",line);

            return ERROR;
   	     }

         val = strtol(input+1, &temp, BASE10);

         if(val < 0 || TOTAL_REGISTERS < val) 
         {
            printf("Line %d: Register out of bounds.\n",line);

            return ERROR;
         }

   	     if(*temp != '\n' && *temp != '\0')
   	     {
      	    printf("Line %d: Extraneous input after end of command.\n",line);

      	    return ERROR;
    	 }

      }
      else if(('a' <=  *input && *input <= 'z') || ('A' <=  *input && *input <= 'Z'))
      {
         temp = strtok(input,"\n");

         if(strlen(temp) > MAX_LABEL_LENGTH-1)
         {
            printf("Line %d: Variable length is too long.\n",line);

            return ERROR;
         }

         check_Validity_Of_Variables(vp, temp, line);
      } 
   }
   else if(!strcmp(opcode, "31") || !strcmp(opcode, "32"))
   {
      if(!('a' <=  *input && *input <= 'z') && !('A' <=  *input && *input <= 'Z'))
      {
         printf("Line %d: Invalid variable.\n",line);

         return ERROR;
      } 

      temp = strtok(input,"\n");

      if(strlen(temp) > MAX_LABEL_LENGTH-1)
      {
         printf("Line %d: Variable length is too long.\n",line);

         return ERROR;
      }

      check_Validity_Of_Variables(vp, temp, line);

   }

   return SUCCESS;
}

/*Checks data instruction for various syntax errors, within boundaries of bits (8 for .DB and .ASCIZ, 16 for .DH, 32 for .DW) and issues a detailed error message.*/

int Data_Error_Check(char *input, int table_idx, int line)
{
   double val;

   char *temp;

   int double_quotas = 0;

   /*Switch case selects the type of data and checks for errors within each case.*/

   switch(table_idx)
   {
      case DH:

  	    if(*input == '\0' || *input == '\n')
 	    {
	      printf("Line %d: Missing parameters.\n",line);

	      return ERROR;
	    }

        val = strtod(input, &temp);

        if( val < SHRT_MIN || USHRT_MAX < val) 
        {
           printf("Line %d: Integer out of bounds.\n",line);

           return ERROR;
        } 

	   while(*temp != '\0' && *temp != '\n')
	   {
	     if(*temp != ',')
	     {
              printf("Line %d: Invalid integer.\n",line);

              return ERROR;
	     }

   	     if(*(temp+1) == ',')
   	     {
      	      printf("Line %d: Multiple consecutive commas.\n",line);

      	      return ERROR;
   	     }

         val = strtod(temp+1, &temp);

         if( val < SHRT_MIN || USHRT_MAX < val) 
         {
              printf("Line %d: Integer out of bounds.\n",line);

              return ERROR;
         } 
	   }

	   break;
 
      case DW:

    	if(*input == '\0' || *input == '\n')
 	    {
	       printf("Line %d: Missing parameters.\n",line);

	       return ERROR;
	    }

        val = strtod(input, &temp);

        if( val < INT_MIN || UINT_MAX < val) 
        {
           printf("Line %d: Integer out of bounds.\n",line);

           return ERROR;
        } 

	    while(*temp != '\0' && *temp != '\n')
	    {
	       if(*temp != ',')
	       {
              printf("Line %d: Invalid integer.\n",line);

              return ERROR;
	       }

   	    if(*(temp+1) == ',')
   	    {
      	   printf("Line %d: Multiple consecutive commas.\n",line);

      	   return ERROR;
   	    }

           val = strtod(temp+1, &temp);

           if( val < INT_MIN || UINT_MAX < val ) 
           {
              printf("Line %d: Integer out of bounds.\n",line);

              return ERROR;
           } 
	    }

	    break;

      case DB:

  	    if(*input == '\0' || *input == '\n')
 	    {
	       printf("Line %d: Missing parameters.\n",line);

	       return ERROR;
	    }

        val = strtod(input, &temp);

        if( val < CHAR_MIN || UCHAR_MAX < val) 
        {
           printf("Line %d: Integer out of bounds.\n",line);

           return ERROR;
        } 

	    while(*temp != '\0' && *temp != '\n')
	    {

	      if(*temp != ',')
	      {
              printf("Line %d: Invalid integer.\n",line);

              return ERROR;
	      }

   	      if(*(temp+1) == ',')
   	      {
      	      printf("Line %d: Multiple consecutive commas.\n",line);

      	      return ERROR;
   	      }

          val = strtod(temp+1, &temp);

          if( val < SCHAR_MIN || UCHAR_MAX < val) 
          {
              printf("Line %d: Integer out of bounds.\n",line);

              return ERROR;
          } 
	    }

	    break;

      case ASCIZ:

  	     if(*input == '\0' || *input == '\n')
 	     {
	        printf("Line %d: Missing parameters.\n",line);

	        return ERROR;
	     }

       	if(*input != '"')
 	    {
	       printf("Line %d: Missing \" at the beginning of a string.\n",line);

	       return ERROR;
	    } 

	input++;

	while(*input != '\0' && *input != '\n')
	{
	   if(double_quotas)
	   {
      	      printf("Line %d: Extraneous input after end of string.\n",line);

      	      return ERROR;
	   }

	   if(*input == '"')
	   {
              double_quotas++;
	   }

 	   input++;
	}

	   if(!double_quotas)
	   {
      	   printf("Line %d: String not closed properly.\n",line);

      	   return ERROR;
	   }
   }

   return SUCCESS;
}
