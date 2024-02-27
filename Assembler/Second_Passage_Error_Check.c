#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_File.h"

/*This function checks for errors before commencing the second passage.*/

void pre_Second_Passage_Error_Check(symbol_ptr symbols, bmc_ptr b, validity_ptr vp, char *command_Table[][TOTAL_COMMAND_COLS], char **instruction_Table, int *errors)
{
    all_Variables_Defined(symbols, vp, errors);

    all_Variables_Defined_Once(symbols, errors);

    valid_Variables(vp, errors, command_Table, instruction_Table);

    conditional_Branching_Check(symbols, b, errors);

    return;
}