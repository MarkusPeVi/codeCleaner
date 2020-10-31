
This is an comment cleaner written in C language. 
It removes comments in form // or "/* */".
It cleans files that are given to it as arguments and writes cleaned code to a new file named "originalname".clean.

Compile the code with make command. Clean files by writing command ./cleanCode "filename.c".
Program writes a log file of everything it has done, which is named "cleanComments.log".
If you want to clean .o files use command, " make cleanO".
Cleaning everything except codefiles use command "make cleanAll". This removes .o .log .clean -files and binaries.
