#pragma once

#include<stdio.h>

#define ANSI_RED "\x1b[31m" 
#define ANSI_GREEN "\x1b[32m" 
#define ANSI_YELLOW "\x1b[33m" 
#define ANSI_CYAN "\x1b[36m" 
#define ANSI_RESET "\x1b[0m" 

/*
* Prints any message to log with a specific color;
* 
* type 0 -> Default color (Verbose)
* type 1 -> Green Text (Info)
* type 2 -> Yellow Text (Warnings)
* type 3 -> Red Text (Errors)
* type 4 -> Cyan Text (anything else the developer sees fit)
* DISCLAIMER:
*		this log isnt capable of printing variables, for that use the macro LOGVAR
*/
#define LOG(message, type) if(type == 0) printf(ANSI_RESET message "\n" ANSI_RESET); if(type == 1) printf(ANSI_GREEN message "\n" ANSI_RESET); if(type == 2)printf(ANSI_YELLOW message "\n" ANSI_RESET); if(type == 3) printf(ANSI_RED message "\n" ANSI_RESET); if(type == 4) printf(ANSI_CYAN message "\n" ANSI_RESET)
//logs the file name and the function that called this macro... this is useful to check execution orders
#define EXECUTIONLOG LOG( "\n\nDEBUG LOG ----------------------------------------------------------------------------\n" "Function: " FUNCTIONNAME "\n" "File: "FILENAME "\nEND ----------------------------------------------------------------------------------\n\n",4)
//logs anything provided as log as it is valid and has a value to print... this log does not support coloring
#define LOGALL(message) std::cout << message << std::endl;
// Returns the line of code (number) in which this macro is called from
#define LINENUMBER __LINE__
//returns the file name in which this macro is called from
#define FILENAME __FILE__
//returns the function name in which this macro is called from
#define FUNCTIONNAME __FUNCTION__
