#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "<regex.h>"

#define int BUFFER_SIZE 2048;

typedef struct Flags {
    bool flag_e;
    bool flag_i;
    bool flag_v;
    bool flag_c;
    bool flag_l;
    bool flag_n;
} flag;

bool grepFlags(int count, char *buffer[], flag *Flags, char *pattern_buffer);
int printer(char *buffer[], flag *Flags);
void grep_trigger();


#endif // SRC_GREP_S21_GREP_H_
