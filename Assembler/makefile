Assembler: Main.o ProjectOutput.o First_Passage.o Second_Passage.o The_Passages.o input_Proccessor.o Symbol_Management.o Instruction_Organizer.o Assembly_To_Binary.o First_Passage_Error_Check.o Second_Passage_Error_Utility.o Second_Passage_Error_Check.o
	gcc -g -Wall -ansi -pedantic Main.o  ProjectOutput.o First_Passage.o Second_Passage.o The_Passages.o input_Proccessor.o Symbol_Management.o Instruction_Organizer.o Assembly_To_Binary.o First_Passage_Error_Check.o Second_Passage_Error_Utility.o Second_Passage_Error_Check.o -o Assembler 

Instruction_Organizer.o: Instruction_Organizer.c Data_File.h
	gcc -c -Wall -ansi -pedantic Instruction_Organizer.c -o Instruction_Organizer.o 

Main.o: Main.c Data_File.h
	gcc -c -Wall -ansi -pedantic Main.c -o Main.o 

Assembly_To_Binary.o: Assembly_To_Binary.c Data_File.h
	gcc -c -Wall -ansi -pedantic Assembly_To_Binary.c -o Assembly_To_Binary.o

First_Passage.o: First_Passage.c Data_File.h
	gcc -c -Wall -ansi -pedantic First_Passage.c -o First_Passage.o

Second_Passage.o: Second_Passage.c Data_File.h
	gcc -c -Wall -ansi -pedantic Second_Passage.c -o Second_Passage.o

The_Passages.o: The_Passages.c Data_File.h
	gcc -c -Wall -ansi -pedantic The_Passages.c -o The_Passages.o

input_Proccessor.o: input_Proccessor.c Data_File.h
	gcc -c -Wall -ansi -pedantic input_Proccessor.c -o input_Proccessor.o

ProjectOutput.o: ProjectOutput.c Data_File.h
	gcc -c -Wall -ansi -pedantic ProjectOutput.c -o ProjectOutput.o
	
Symbol_Management.o: Symbol_Management.c Data_File.h
	gcc -c -Wall -ansi -pedantic Symbol_Management.c -o Symbol_Management.o

First_Passage_Error_Check.o: First_Passage_Error_Check.c Data_File.h
	gcc -c -Wall -ansi -pedantic First_Passage_Error_Check.c -o First_Passage_Error_Check.o

Second_Passage_Error_Utility.o: Second_Passage_Error_Utility.c Data_File.h
	gcc -c -Wall -ansi -pedantic Second_Passage_Error_Utility.c -o Second_Passage_Error_Utility.o

Second_Passage_Error_Check.o: Second_Passage_Error_Check.c  Data_File.h
	gcc -c -Wall -ansi -pedantic Second_Passage_Error_Check.c -o Second_Passage_Error_Check.o
