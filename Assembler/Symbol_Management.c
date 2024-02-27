#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

/*Adds labels to the symbol table.*/

void add_To_Symbol_List(char *sym, int line_type, int addr, symbol_ptr *s)
{
   char *types[] = {"external", "entry", "code", "data"};

   symbol_ptr p = *s;

   symbol_ptr t = malloc (sizeof(struct SymbolList));

   if(!t)
   {
      puts("Could not allocate memory for symbol table");

      exit(1);
   }

   t -> opt_type = NULL;

   strcpy(t -> symbol, sym);

   t -> address = addr;

   /*Switch case, selects the symbol type.*/

   switch (line_type)
   {
      case EXTERN:

	     t -> type = types[0];
	     break;

      case ENTRY:

	    t -> type = types[1];
	    break;

      case COMMAND:

	     t -> type = types[2];
	     break;

      case INSTRUCTION:

	     t -> type = types[3];
	     break;

      default:

	     t -> type = NULL;
   }

   if(!(*s))
   {
      t -> next = NULL;

      *s = t;

      return;
   }
 
   /*Positions the pointer in case it is not empty.*/

   while(p -> next)
   {
      p = p -> next;
   }

   t -> next = NULL;

   p -> next = t; 

   return;
}

/*Updates the addresses of data type symbols with IC.*/

void update_Symbol_Address(symbol_ptr *symbols, int addr)
{
   symbol_ptr p = *symbols;

   while(p)
   {
      if(!strcmp(p -> type,"data"))
      {
	     p -> address += addr;
      }

      p = p -> next;
   }

   return;
}
  
/*Updates any symbols in case they're entry also.*/

void update_Symbols_Entry(char *symbol, symbol_ptr *s, int *errors)
{ 
   symbol_ptr ps = *s;

   /*This while loop updates the symbol table accordingly.*/

   while(ps)
   {
      if(!strcmp(ps -> type,"external") && !strcmp(ps -> symbol,symbol))
      {
	     (*errors)++;

         printf("%s can not be entry and external.\n",ps -> symbol);

	     return;
      }
      else if(!strcmp(ps -> symbol,symbol))
      { 
	     ps -> opt_type = "entry";
      }
      ps = ps -> next;
   }

   return;
}  