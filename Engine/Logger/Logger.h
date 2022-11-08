#pragma once

#include<stdio.h>

#define ANSI_RED "\x1b[31m" 
#define ANSI_GREEN "\x1b[32m" 
#define ANSI_YELLOW "\x1b[33m" 
#define ANSI_CYAN "\x1b[36m" 
#define ANSI_RESET "\x1b[0m" 


#define LOG(message, type) if(type == 0) printf(ANSI_RESET message "\n" ANSI_RESET); if(type == 1) printf(ANSI_GREEN message "\n" ANSI_RESET); if(type == 2)printf(ANSI_YELLOW message "\n" ANSI_RESET); if(type == 3) printf(ANSI_RED message "\n" ANSI_RESET); if(type == 4) printf(ANSI_CYAN message "\n" ANSI_RESET)
#define DEBUGLOG LOG( "\n\nDEBUG LOG ----------------------------------------------------------------------------\n" "Function: " FUNCTIONNAME "\n" "File: "FILENAME "\nEND ----------------------------------------------------------------------------------\n\n",4)
#define LINENUMBER __LINE__
#define FILENAME __FILE__
#define FUNCTIONNAME __FUNCTION__
