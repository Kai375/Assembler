#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

   /*Converts the data from the instruction line and into binary. */

   void retrieve(char *content, int table_idx, int *addr, data_ptr *d)
{
   data_ptr p = *d, t = NULL;
   int i = 1;
   long b = 0;

   /*This while loop positions the pointer to the end of the data table.*/

   if (*d)
   {
      while (p->next)
      {
         p = p->next;
      }
   }

   /*Switch case for, .dh .dw .db and .asciz.*/
	
   switch (table_idx)
   {
      case DH:

	 b = strtol(content, &content, BASE10);

         while (*content != '\0' && *content != '\n')
	 {
	    content++;

        /*Malloc for a node of the selected data structure.*/

   	    t = malloc(sizeof(struct DataList));
            if (!t)
   	    {
     	       puts("Could not allocate memory for data table");
     	       exit(1);
            }
	    t->type = ".dh";
	  
	    t->address = *addr;
	    (*addr) += DH_ADDRESS_JUMP_FACTOR;
	    t->value = b;
   	    t->next = NULL;

   	    if (!(*d))   
   	    {
      	    *d = t;	
	        p = *d;
   	    }
	    else
	    {
   	       p->next = t; 
	       p = p->next;
	    }

	    b = strtol(content, &content, BASE10);
	 }

        /*Malloc for a node of the selected data structure.*/

         t = malloc(sizeof(struct DataList));
         if (!t)
   	 {
     	    puts("Could not allocate memory for data table");
     	    exit(1);
         }
	 t->type = ".dh";

	 t->address = *addr;
	 (*addr) += DH_ADDRESS_JUMP_FACTOR;
	 t->value = b;
   	 t->next = NULL;

   	 if (!(*d))   
   	 {
      	    *d = t;	
   	 }
	 else
	 {
   	    p->next = t; 
	 }

	 break;

      case DW:

	 b = strtol(content, &content, BASE10);

         while (*content != '\0' && *content != '\n')
	 {
	    content++;
   	    t = malloc(sizeof(struct DataList));
            if (!t)
   	    {
     	       puts("Could not allocate memory for data table");
     	       exit(1);
            }
	    t->type = ".dw";
	  
	    t->address = *addr;
	    (*addr) += DW_ADDRESS_JUMP_FACTOR;
	    t->value = b; 
   	    t->next = NULL;

   	    if (!(*d))   
   	    {
      	        *d = t;	
	        p = *d;
   	    }
	    else
	    {
   	       p->next = t; 
	       p = p->next;
	    }

	    b = strtol(content, &content, BASE10);
	 }
	
         t = malloc(sizeof(struct DataList));
         if (!t)
   	 {
     	    puts("Could not allocate memory for data table");
     	    exit(1);
         }
	 t->type = ".dw";

	 t->address = *addr;
	 (*addr) += DW_ADDRESS_JUMP_FACTOR;
	 t->value = b;
   	 t->next = NULL;

   	 if (!(*d))   
   	 {
      	    *d = t;
   	 }
	 else
	 {
   	    p->next = t; 
	 }
	 break;

      case DB:

	 b = strtol(content, &content, BASE10);

         while (*content != '\0' && *content != '\n')
	 {
	    content++;
   	    t = malloc(sizeof(struct DataList));
            if (!t)
   	    {
     	       puts("Could not allocate memory for data table");
     	       exit(1);
            }
	    t->type = ".db";
	  
	    t->address = *addr;
	    (*addr)++;
	    t->value = b; 
   	    t->next = NULL;

   	    if (!(*d))   
   	    {
      	        *d = t;	
	        p = *d;
   	    }
	    else
	    {
   	       p->next = t; 
	       p = p->next;
	    }

	    b = strtol(content, &content, BASE10);
	 }

         t = malloc(sizeof(struct DataList));
         if (!t)
   	 {
     	    puts("Could not allocate memory for data table");
     	    exit(1);
         }
	 t->type = ".db";

	 t->address = *addr;
	 (*addr)++;
	 t->value = b;
   	 t->next = NULL;

   	 if (!(*d))   
   	 {
      	    *d = t;	
   	 }
	 else
	 {
   	    p->next = t; 
	 }

	 break;

      case ASCIZ:

	 while (content[i] != '"')
	 {
   	    t = malloc(sizeof(struct DataList));
            if (!t)
   	    {
     	       puts("Could not allocate memory for data table");
     	       exit(1);
            }
	    t->type = ".asciz";

	    t->address = *addr;
	    (*addr)++;
	    t->value = (int) content[i]; 
   	    t->next = NULL;

   	    if (!(*d))   
   	    {
      	       *d = t;
	       p = *d;	
   	    }
	    else
	    {
   		p->next = t; 
		p = p->next;
	    }

	    i++;
	 }

         t = malloc(sizeof(struct DataList));
         if (!t)
   	 {
     	    puts("Could not allocate memory for data table");
     	    exit(1);
         }
	 t->type = ".asciz";
	 t->address = *addr;
	 (*addr)++;
	 t->value = 0; 
   	 t->next = NULL;

   	 if (!(*d))   
   	 {
      	    *d = t;	
   	 }
	 else
	 {
   	    p->next = t; 
	 } 
   }

   return;
}

   /*updates the data addresses with IC.*/

   void update_Data_Address(data_ptr *data, int addr)
{
   data_ptr p = *data;

   while (p)
   {
      p->address += addr;
      p = p->next;
   }

   return;
}

 