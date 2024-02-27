#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

/*Checks to see that all the labels at the symbol list exist.*/

void all_Variables_Defined(symbol_ptr symbol, validity_ptr vp, int *errors)
{
   symbol_ptr sptr = symbol;

   while(vp)
   {
      if(!strcmp(sptr->symbol,vp->toCheck))
      {
	     vp = vp->next;
	     sptr = symbol;
      }
      else if(!sptr->next)
      {
	     printf("\"%s\" has not been defined.\n",vp->toCheck);
         
	     (*errors)++;

	     vp = vp->next;

	     sptr = symbol;
      }
      else
      {
         sptr = sptr->next;
      }
   }

   return;
}

/*Checks to see that all the variables have been defined once.*/

void all_Variables_Defined_Once(symbol_ptr symbolx, int *errors)
{
   symbol_ptr sptr;

   while(symbolx)
   {
      sptr = symbolx->next;

      while(sptr)
      {
	     if(!strcmp(symbolx->symbol,sptr->symbol) && strcmp(symbolx->type,sptr->type))
	     {
	        printf("%s has already been defined.\n",symbolx->symbol);

	        (*errors)++;
	     }
         sptr = sptr->next;
      }

      symbolx = symbolx->next;
   }

   return;
}

/*Checks the validity of the variable within validity list.*/

void valid_Variables(validity_ptr vp, int *errors, char *Command_Table[][TOTAL_COMMAND_COLS], char **Instruction_Table)
{
   while(vp)
   {
      if(valid_Label(Command_Table, Instruction_Table, vp->toCheck, strlen(vp->toCheck), vp->line))
      {
         (*errors)++;
      }
      vp = vp->next;
   }

   return;
}

/*Checks to see that labels given to commands blt, bne, bgt, beq aren't of type extern.*/

void conditional_Branching_Check(symbol_ptr symbol, bmc_ptr bmc, int *errors)
{
    symbol_ptr sptr;

    while(bmc)
    {
        if(BNE_OPCODE <= bmc->mila.I.opcode && bmc->mila.I.opcode <= BGT_OPCODE)
        {
            sptr = symbol;

            while(sptr)
            {
                if(!strcmp(bmc->var,sptr->symbol) && !strcmp(sptr->type,"external"))
                {
                    printf("Command of type conditional branching can not accept variable of type extern, at address %d.\n",bmc->addr);

                    (*errors)++;
                }
                sptr = sptr->next;
            }
        }

        bmc = bmc->next;
    }

    return;
}
