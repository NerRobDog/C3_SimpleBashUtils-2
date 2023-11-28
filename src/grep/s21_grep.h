#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>
#include "regex.h"

#define BUFFER_SIZE 4096

typedef struct Flags {
    int flag_e;
    int flag_i;
    int flag_v;
    int flag_c;
    int flag_l;
    int flag_n;
    int flag_h;
    int flag_s;
    int flag_f;
    int flag_o;
} flag;

void grep_flags(int count, char *buffer[], flag *Flags, char *pattern_buffer);
void grep_launcher(flag *Flags, int count, char *buffer[], char *buff);
void grep_file(flag *Flags, char *pattern, char *file_name);
void grep_process(flag *Flags, FILE *file, regex_t reg, char *file_name);
int grep_f_flag(char *pattern, char *file_name);

#endif // SRC_GREP_S21_GREP_H_
