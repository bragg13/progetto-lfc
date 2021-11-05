#ifndef REG_EXP__H
#define REG_EXP__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_priority(char c);

void parse_string(char *str, unsigned int dim);

/* add '.' to explicit the concatenation operator to regular expressions which may not have it */
void add_explicit_concat(char *str, char *output_str);

/* convert regular expression to postfix reverse polish notation */
void infix_to_postfix(char *src_str, char *dst_str);

#endif