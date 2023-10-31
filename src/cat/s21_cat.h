#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

typedef struct Flags {
    bool flag_b;
    bool flag_e;
    bool flag_n;
    bool flag_s;
    bool flag_t;
    bool flag_v;
} flag;

static struct option options[] = { // библиотека getopt
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0},
};

bool catFlags(int count, char *buffer[], flag *Flags);
void printer(char *buffer[], flag *Flags);

#endif // SRC_S21_CAT_H_
