#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

   /*Converts the command into binary. */

   void convert(char *ty, char *ft, char *oc, char *content, int addr, bmc_ptr *bmc)
{
   bmc_ptr p = *bmc, t;

   long val; 
  	 
   t = malloc(sizeof(struct CodeList));

   if(!t)
   {
      puts("Could not allocate memory for command table");

      exit(1);
   }

   t -> mila.m[0] = '\0';
   t -> mila.m[1] = '\0';
   t -> mila.m[2] = '\0';
   t -> mila.m[3] = '\0';
   t -> addr = addr;
   t -> type = *ty; 
   strcpy(t -> var, "\0");
	
   /*Switch case selects the command type: R I or J.*/

   switch(*ty)
   {
      case 'R':

         val = atol(ft);
   	     t -> mila.R.funct = val;
   	     val = atol(oc);
   	     t->mila.R.opcode = val;
   	     t->mila.R.not_in_use = 0;

	    if(*oc == '0')
	    {
	       val = strtol(content+1, &content, BASE10);
	       t -> mila.R.rs = val;

	       val = strtol(content+2, &content, BASE10);
	       t->mila.R.rt = val;

	       val = strtol(content+2, &content, BASE10);
	       t -> mila.R.rd = val;
	    }
	    else
	    {
	       val = strtol(content+1, &content, BASE10);
	       t -> mila.R.rs = val;

	       val = strtol(content+2, &content, BASE10);
	       t -> mila.R.rd = val;
	    }

	    break;

      case 'I':   

   	     val = atol(oc);
   	     t -> mila.I.opcode = val;

	     if(!strcmp(ft,"constant"))  
	     {
	        val = strtol(content+1, &content, BASE10);
	        t -> mila.I.rs = val;

	        val = strtol(content+1, &content, BASE10);
	        t -> mila.I.immed = val;

	        val = strtol(content+2, &content, BASE10);
	        t -> mila.I.rt = val;
	     }

	     if(!strcmp(ft,"variable"))
	     {
	        val = strtol(content+1, &content, BASE10);
	        t -> mila.I.rs = val;

	        val = strtol(content+2, &content, BASE10);
	        t -> mila.I.rt = val;

	        strcpy(t -> var,strtok(content+1,"\n"));
	     }

	     break;

      case 'J':

   	     val = atol(oc);
   	     t -> mila.J.opcode = val;

	     if(content[0] == '$' && !strcmp(oc,"30"))
         {
	        t -> mila.J.reg = 1;

	        val = strtol(content+1, &content, BASE10);

	        t -> mila.J.address = val;
	     }
	     else if(strcmp(oc, "63"))
	    {
	       strcpy(t -> var,strtok(content,"\n"));
	    }
   }

   if(!(*bmc))
   {
      t -> next = NULL;

      *bmc = t;

      return;
   }

   /*This while loop positions the pointer in case the table isn't empty.*/

   while(p -> next)
   {
      p = p -> next;
   }

   t -> next = NULL;
   p -> next = t; 

   return;
}

   /* Assigns the variables the program has encountered in a list, to be checked for thier validity.*/

void check_Validity_Of_Variables(validity_ptr *vp, char *temp, int line)
{
    validity_ptr sbp = *vp, t;

   if(!(*vp))
   {
	    t = malloc(sizeof(struct OnHoldList));

        if(!t)
        {
           puts("Could not allocate memory for validity list");

           exit(1);
        }
	    t -> next = NULL;
	    strcpy(t -> toCheck, temp);
	    t -> line = line;
	    *vp = t;
   	    return;
   }

   while(sbp->next)
   {
	  sbp = sbp->next;
   }

   t = malloc(sizeof(struct OnHoldList));

   if(!t)
   {
      puts("Could not allocate memory for validity list");

      exit(1);
   }

   t -> next = NULL;
   strcpy(t -> toCheck, temp);
   t -> line = line;
   sbp -> next = t;
   
   return;
}

/*Updates the addresses of the variables that weren't present at the first passage.*/

void update_BMC_Adresses(symbol_ptr s, bmc_ptr *b)
{
   symbol_ptr ps = s;
   bmc_ptr pb = *b;

   while(pb)
   {
      if (pb->var[0] != '\0')
      {
	     ps = s;

	     while(ps)
	     {
      	    if(!strcmp(ps->symbol,pb->var))
      	    {
	           if (pb->type == 'J')
	           {
	              pb->mila.J.address = ps->address;
	           }
	           else
	           {
	              pb->mila.I.immed = ps->address - pb->addr;
	           }
	        }
            ps = ps->next;
         }
      }

      pb = pb->next;
   }

   return;
}
