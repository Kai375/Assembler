 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

  /*Translates what the data structures hold to hexadecimal.*/

void final_Output(bmc_ptr b, data_ptr d, symbol_ptr s, char *end_result, int ic, int dc)
{
   bmc_ptr bptr = b; 

   data_ptr dptr = d;  

   symbol_ptr sptr = s;

   int i , j, counter = 0, buffer2 = 0, data_address = ic, removal_flag = 0;

   FILE *file;

   /*Allocate memory for .ob	.ent	.ext*/

   char *file_ob = malloc(strlen(end_result)+TYPE_OF_FILE_4);
   char *file_ext = malloc(strlen(end_result)+TYPE_OF_FILE_5);
   char *file_ent = malloc(strlen(end_result)+TYPE_OF_FILE_5);
   char *buffer = calloc(OUTPUT_LINE_LENGTH+1,sizeof(char));
   
   if (!buffer)
   {
      puts("\nCould not allocate memory for buffer.");

      exit(1);
   }

   if (!file_ob)
   {
      puts("\nCould not allocate memory for object file.");

      exit(1);
   }
   if (!file_ext)
   {
      puts("\nCould not allocate memory for external file.");

      exit(1);
   }
   if (!file_ent)
   {
      puts("\nCould not allocate memory for entry file.");

      exit(1);
   }
   
   strcpy(file_ob, end_result);
   strcpy(file_ext, end_result);
   strcpy(file_ent, end_result);

   strcat(file_ob, ".ob");
   strcat(file_ext, ".ext");
   strcat(file_ent, ".ent");

   file = fopen(file_ob, "w");

   fprintf(file, "\t%d %d\t\n", ic-100, dc);

   /*This while loop iterates BMC (bptr) and prints to file of type .ob.*/

   while(bptr)
   {
      fprintf(file, "%04d ", bptr->addr);

      for(j = 0; j < 4; j++)
      {
         for(i = 0; i <= BYTE-1; i++)
         {
     	      if(bptr->mila.m[j] & (1 << i))
      	      {
                 buffer2 |= (1 << i);
      	      }
         }
   
         fprintf(file, "%02X ", buffer2);

         buffer2 = 0;
      }

      fprintf(file, "\n");
     
      bptr = bptr->next;
   }

   fprintf(file, "%04d ", dptr->address);

   /*This while loop iterates data table (dptr) and prints to file of type .ob.*/

   while(dptr)
   {
      buffer2 = 0;

      if(!strcmp(dptr->type, ".dw"))
      {
         for(i = 0; i <= FOUR_BYTES-1; i++)
   	     {
     	       if(dptr->value & (1 << i))
      	    {
               buffer2 |= (1 << i);
      	    }
   	     }
	      sprintf(buffer, "%08X", buffer2);
      }
      else if(!strcmp(dptr->type, ".dh"))
      {
         for(i = 0; i <= TWO_BYTES-1; i++)
   	     {
     	       if(dptr->value & (1 << i))
      	    {
              buffer2 |= ( 1 << i);
      	    }
   	     }
	      sprintf(buffer, "%04X", buffer2);
      }
      else
      {
         for(i = 0; i <= BYTE-1; i++)
   	     {
     	       if(dptr->value & (1 << i))
      	    {
               buffer2 |= (1 << i);
      	    }
   	     }
      }

      if(!strcmp(dptr->type, ".db") || !strcmp(dptr->type,".asciz"))
      {
         fprintf(file, "%02X ", buffer2);

         counter++;

	     if (counter == NEW_LINE)
         {
	        fprintf(file, "\n%04d ", data_address += counter);

	        counter = 0;
	     }
      } 
      else
      {
         for(i = strlen(buffer)-1, j = strlen(buffer)-2; i >= 0 && j >= 0; i -= 2, j -= 2)
         { 
            fprintf(file, "%c%c ",buffer[j],buffer[i]);

            counter++;

	        if(counter == NEW_LINE)
            {
	           fprintf(file, "\n%04d ", data_address += counter);

	           counter = 0;
	        }
         }
      }

      strcpy(buffer, "\0");
	     
      dptr = dptr->next;
   }

   fclose(file);

   file = fopen(file_ent, "w");

   /*Generates a .ent file if any entry type variables are found.*/
   
   while(sptr)
   {
      if(sptr->type && !strcmp(sptr->type,"entry"))
      {
         removal_flag++;

	     fprintf(file, "%s %04d\n",sptr->symbol,sptr->address);
      }
      else if(sptr->opt_type && !strcmp(sptr->opt_type,"entry"))
      {
         removal_flag++;

	     fprintf(file, "%s %04d\n",sptr->symbol,sptr->address);
      }

      sptr = sptr->next;
   }
   
   fclose(file);

   file = fopen(file_ext, "w");

   /* Removes the entry file, that were created by fopen above, in case no entry types have been found.*/

   if(!removal_flag)
   {
      removal_flag = remove(file_ent);

      if(!removal_flag)
      {
	     puts("No entry file created.");
      }
   }

   removal_flag = 0;

   bptr = b;

   /*Generates a .ext file if any extern type variables are found.*/
   
   while(bptr)
   {
      if(bptr->var[0] != '\0')
      {
	     sptr = s;

	     while(sptr)
	     {
	        if(!strcmp(sptr->symbol,bptr->var))
	        {
		       if(!strcmp(sptr->type,"external"))
		       {
                   removal_flag++;

		           fprintf(file, "%s %04d\n",sptr->symbol,bptr->addr);
		       }
		       else if(sptr->opt_type && !strcmp(sptr->opt_type,"external"))
		       {
                   removal_flag++;

		           fprintf(file, "%s %04d\n",sptr->symbol,bptr->addr);
		       }
	        }	

            sptr = sptr->next;
	     }
      }

      bptr = bptr->next;
   }
  
   fclose(file);

   /* Removes the extern file, that were created by fopen above, in case no extern types have been found.*/

   if(!removal_flag)
   {
      removal_flag = remove(file_ext);

      if(!removal_flag)
      {
	     puts("No external file created.");
      }
   }

   free(buffer);
   buffer = NULL;

   free(file_ob);
   file_ob = NULL;

   free(file_ent);
   file_ent = NULL;

   free(file_ext);
   file_ext = NULL;
  
   return;
}

 /*Frees the data structures.*/

void free_List(void **list, int type)
{
   symbol_ptr s, sptr;

   data_ptr d, dptr;

   bmc_ptr b, bptr;

   validity_ptr vp, vpptr;

   switch(type)
   {
      case SYMBOL:

	     s = (symbol_ptr) *list;

	     sptr = s;

  	     while(s)
 	     {
	        s = s->next;

	        free(sptr);

	        sptr = NULL;

	        sptr = s;
 	     }

         break;

      case DATA:

	     d = (data_ptr) *list;

	     dptr = d;

  	     while(d)
 	     {
	        d = d->next;

	        free(dptr);

	        dptr = NULL;

	        dptr = d;
 	     }

         break;

      case BMC:

	     b = (bmc_ptr) *list;

	     bptr = b;

  	     while(b)
 	     {
	        b = b->next;

	        free(bptr);

	        bptr = NULL;

	        bptr = b;
 	     }

	    break;

      case VALIDITY:

	     vp = (validity_ptr) *list;

	     vpptr = vp;

  	     while(vp)
 	     {
	        vp = vp->next;

	        free(vpptr);

	        vpptr = NULL;

	        vpptr = vp;
 	     }
   }

   return;
}

