#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "<regex.h>"

#define int BUFFER_SIZE 4096;

typedef struct Flags {
    bool flag_e;
    bool flag_i;
    bool flag_v;
    bool flag_c;
    bool flag_l;
    bool flag_n;
} flag;

struct option options[] = { // библиотека getopt
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0},
};

bool grepFlags(int count, char *buffer[], flag *Flags);
int printer(char *buffer[], flag *Flags);

#endif // SRC_GREP_S21_GREP_H_
