#include <stdio.h>
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

bool catFlags(int count, char *buffer[], flag *Flags);
void printer(char *buffer[], flag *Flags);

int main(int count, char *buffer[]) { //arg2[] - массив агрументов
    struct Flags flag = {0, 0, 0, 0, 0, 0};

    catFlags(count, buffer, &flag);
    // optind - возможно, хранит текущий индекс buffer
    while(optind < count) {
        printer(buffer, &flag);
        optind++;
    }
    return 0;
}

bool catFlags(int count, char *buffer[], flag *Flags) {
    int f; // что это?
    const char* f_options = "bEnsTvet";
    static struct option options[] = { // библиотека getopt
            {"number-nonblank", 0, 0, 'b'},
            {"number", 0, 0, 'n'},
            {"squeeze-blank", 0, 0, 's'},
            {0, 0, 0, 0},
    };
    while ((f = getopt_long(count, buffer, f_options, options, NULL)) != -1) {
        switch (f) {
            case 'b':
                Flags ->flag_b = 1;
                break;
            case 'E':
                Flags ->flag_e = 1;
                break;
            case 'n':
                Flags ->flag_n = 1;
                break;
            case 's':
                Flags ->flag_s = 1;
                break;
            case 'T':
                Flags ->flag_t = 1;
                break;
            case 'v':
                Flags ->flag_v = 1;
                break;
            case 'e':
                Flags ->flag_e = 1;
                Flags ->flag_v = 1;
                break;
            case 't':
                Flags ->flag_t = 1;
                Flags ->flag_v = 1;
                break;
            default:
                printf("error\n");
                break;
        }
        if (Flags ->flag_b  && Flags ->flag_n ) Flags ->flag_n  = 0;
    }
    return 0;
}

void printer(char *buffer[], flag *Flags) {
    FILE *fp;
    fp = fopen(buffer[optind], "r");
    if (fp != NULL) {
        int str_count = 1;
        int empty_str_count = 0;
        int last = '\n'; // ???
        while (!feof(fp)) {
            int c = fgetc(fp); // считывает данные с потока и делает из них строку
            if (c == EOF)
                break;
            if (Flags ->flag_s && c == '\n' && last == '\n') {
                empty_str_count++;
                if (empty_str_count > 1) { // ??
                    continue;
                }
            } else {
                empty_str_count = 0;
            }
            if (last == '\n' && ((Flags ->flag_b && c != '\n') ||Flags ->flag_n)) {
                printf("%6d\t", str_count++);
            }
            if (Flags ->flag_t && c == '\t') {
                printf("^");
                c = 'I';
            }
            if (Flags ->flag_e && c == '\n')
                printf("$");
            if (Flags ->flag_v) {
                if ((c >= 0 && c < 9) || (c > 10 && c < 32)
                    || (c > 126 && c <= 160)) {
                    printf("^");
                    if (c > 126) {
                        c -= 64;
                    } else {
                        c += 64;
                    }
                }
            }
            printf("%c", c);
            last = c;
        }
        fclose(fp);
    } else {
        printf("Error\n");
        exit(1);
    }
}