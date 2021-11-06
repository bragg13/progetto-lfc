#ifndef REG_EXP__H
#define REG_EXP__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* utils function to get priority of an operator */
int get_priority(char c);

/* add '.' to explicit the concatenation operator to regular expressions which may not have it */
char* add_explicit_concat(char *str);

/* convert regular expression to postfix reverse polish notation */
char* infix_to_postfix(char *src_str);

#endif