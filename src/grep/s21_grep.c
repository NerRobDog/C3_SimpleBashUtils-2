#include "s21_grep.h"

int main(int count, char *buffer[]) {
    struct Flags flag = {0, 0, 0, 0, 0, 0};
    char pattern_buffer[BUFFER_SIZE] = {0};

    grepFlags(count, buffer, &flag, pattern_buffer);
    return 0;
}

bool grepFlags(int count, char *buffer[], flag *Flags, char *pattern_buffer) {
    bool flag_value; // будет ли работать с bool
    char* f_options = "eivcln";

    while ((flag_value = getopt_long(count, buffer, f_options)) != -1) {
        switch (flag_value) {
            case 'e':
                Flags -> flag_e = 1;
                snprintf(pattern_buffer, BUFFER_SIZE, "%s", optarg)// getopt(3) external variables
                break;
            case 'i':
                Flags -> flag_i = 1;
                break;
            case 'v':
                Flags -> flag_v = 1;
                break;
            case 'c':
                Flags -> flag_c = 1;
                break;
            case 'l':
                Flags -> flag_l = 1;
                break;
            case 'n':
                Flags -> flag_n = 1;
                break;
            default:
                printf("ERROR: invalid arguments\n");
                break;
        }
        //if (Flags -> flag_b && Flags -> flag_n) Flags -> flag_n  = 0;
    }
    return 0;
}

/**
 *  * поиск во всех файлах
 *  -e шаблон
 * -i поиск без учета регистра
 *  -w поиск всего слова
 *  -c кол-во совпадений
 *  -r поиск в подкаталогах
 *  -i инверсия
 *  -n номера строк
*/

void grep_trigger() {

}

int printer(char *buffer[], flag *Flags) {
    FILE *file;
    file = fopen(buffer[optind], "r");
    if (file != NULL) {
        int str_count = 1;
        bool empty_str_count = 0;
        int last = '\n';
        while (!feof(file)) {
            int c = fgetc(file); // считывает данные с потока и делает из них строку
            if (Flags -> flag_s && c == '\n' && last == '\n') {
                empty_str_count++;
                if (empty_str_count > 1) {
                    continue;
                }
            } else {
                empty_str_count = 0;
            }
            if (last == '\n' && ((Flags -> flag_b && c != '\n') ||Flags -> flag_n)) {
                printf("%6d  ", str_count++);
            }
            if (Flags -> flag_t && c == '\t') {
                printf("^");
                c = 'I';
            }
            if (Flags -> flag_e && c == '\n')
                printf("$");
            if (Flags -> flag_v) {
                if ((c >= 0 && c < 9) || (c > 10 && c < 32) || (c > 126 && c <= 160)) {
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
        fclose(file);
        printf("\n");
    } else {
        printf("ERROR: incorrect file name\n");
        return 1;
    }
}