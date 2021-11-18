#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "thompson_construction.h"
#include "reg_exp.h"
#include "getopt.h"
#define USAGE_STR "Usage:\n-i <path> specify a file to use as input file\n -o <path> specify a file to use as output file\n -H use human-readable output\n -h display this message\n"
#define MAX_FILE_LEN 50

int main(int argc, char **argv) {
    char c;
    char input_file[MAX_FILE_LEN], output_file[MAX_FILE_LEN];
    int custom_in=0, custom_out=0;
    int output_type = 0; // 0 default | 1 fancy

    /* ===== ARGs PARSER =====*/
    if (argc > 1) {
        while( (c = getopt(argc, argv, "i:o:Hh")) != -1) {
            switch(c){
                case 'i':
                    strcpy(input_file, optarg);
                    custom_in = 1;
                    break;
                case 'o':
                    strcpy(output_file, optarg);
                    custom_out = 1;
                    break;
                case 'H':
                    output_type = 1;
                    break;
                case 'h':
                    printf("%s\n", USAGE_STR);
                    break;
                case ':':
                    // if no operands specified for i or o
                    perror("Options -o and -i require parameters, running default.\n");
                    break;
                case '?':
                    perror("Unrecognized option from command line arguments, running default.\n");
                    break;
            }
        }
    }
    if (custom_in == 0) {
        strcpy(input_file, "input.txt");
    }
    if (custom_out == 0) {
       strcpy(output_file, "output.txt");
    }
    /* =======================*/

    // get input
    char *str = get_input(input_file);
    printf("%s\n", str);

    // add explicit concatenation to input string
    str = add_explicit_concat(str);
    printf("%s\n", str);

    // transform the expression to postfix
    str = infix_to_postfix(str);
    printf("%s\n", str);

    // construct the NFA
    NFA *final_nfa = nfa_build(str);
    nfa_print(final_nfa);

    // write output
    write_output(final_nfa, output_file, output_type);


    printf("\n");
    return 0;
}