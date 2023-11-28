#include "s21_grep.h"

int main(int count, char* buffer[]) {
    struct Flags flag = {0, 0, 0, 0, 0, 0,0,0,0,0};
    char pattern_buffer[BUFFER_SIZE] = {0};

    grep_flags(count, buffer, &flag, pattern_buffer);
    if (count >= 3) {
        grep_launcher(&flag, count, buffer, pattern_buffer);
    }
    return 0;
}

void grep_flags(int count, char *buffer[], flag *Flags, char *pattern_buffer) {
    int flag_value;
    char* f_options = "e:ivclnhsf:o"; // убрал именнованные классы

    while ((flag_value = getopt(count, buffer, f_options)) != -1) {
        switch (flag_value) {
            case 'e':
                Flags -> flag_e = 1;
                snprintf(pattern_buffer, BUFFER_SIZE, "%s", optarg);  // getopt(3) external variables
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
            case 'h':
                Flags -> flag_h = 1;
                break;
            case 's':
                Flags -> flag_s = 1;
                break;
            case 'f':
                Flags -> flag_f = 1;
                snprintf(pattern_buffer, BUFFER_SIZE, "%s", optarg);
                break;
            case 'o':
                Flags -> flag_o = 1;
                break;
            default:
                printf("ERROR: invalid arguments\n");
                break;
        }
    }
}

void grep_launcher(flag *Flags, int count, char *buffer[], char *buff) {
    char pattern[BUFFER_SIZE] = {0}; // пустой шаблон
    int end_of_pattern = 0;
    if (!Flags -> flag_f && !Flags -> flag_e) { // если нет шаблона
        snprintf(pattern, BUFFER_SIZE, "%s", buffer[optind++]);
    }
    if (Flags -> flag_f) { // регулярки (press F)
        end_of_pattern = grep_f_flag(pattern, buff); // вызов функции
    }
    if (!Flags -> flag_f && Flags -> flag_e) { // шаблон без регулярки
        snprintf(pattern, BUFFER_SIZE, "%s", buff);
    }
    if (end_of_pattern != -1) { //если без ошибок
        int file_count = 0;
        if (count - optind > 1) { // optind - индекс текущего параметра
            file_count = 1;
        }
        for (int i = optind; i < count; i++) {
            if (file_count && !Flags -> flag_h && !Flags -> flag_l) { // если файл есть
                printf("%s:", buffer[i]);
            }
            grep_file(Flags, pattern, buffer[i]);
        }
    }
}

void grep_file(flag *Flags, char *pattern, char *file_name) {
    int cflags = REG_EXTENDED; // расш. регулярные выражения
    regex_t reg; // f
    FILE *file;
    file = fopen(file_name, "r");
    if (Flags -> flag_i) {
        cflags = REG_ICASE; // не учитывать регистр
    }
    if (file != NULL) {
        regcomp(&reg, pattern, cflags); // обработка рег. выр.
        grep_process(Flags, file, reg, file_name);
        regfree(&reg); // высвобождение
        fclose(file);
    }
}

void grep_process(flag *Flags, FILE *file, regex_t reg, char *file_name) {
    char text[BUFFER_SIZE] = {0};
    regmatch_t pmatch[1];
    int line_matches = 0, line_number = 1;

    while (fgets(text, BUFFER_SIZE - 1, file) != NULL) { // считывает данные с потока и делает из них строку
        bool match = 0;
        bool success = regexec(&reg, text, 1, pmatch, 0);  // успешность поиска слова

        if (strchr(text, '\n') == NULL) // порядковый номер (с единицы)
            strcat(text, "\n");
        if (success == 0 && !Flags -> flag_v)
            match = 1;
        if (success == REG_NOMATCH && Flags -> flag_v)
            match = 1;
        if (Flags -> flag_v && Flags -> flag_o) // результата нет, поэтому проброс
            continue;
        if (match && !Flags -> flag_l && !Flags -> flag_c && Flags -> flag_n)
            printf("%d:", line_number); // нумерует все строки
        if (match && !Flags -> flag_l && !Flags -> flag_c && !Flags -> flag_o)
            printf("%s", text);  // просто выводит совпадение
        if (match && Flags -> flag_o) {
            for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) { // выводит нужный кусок строки (совпадение)
                printf("%c", text[i]);
            }
            printf("\n");
        }
        line_matches += (int)match;
        line_number++;
    }
    if (Flags -> flag_l && line_matches > 0)
        printf("%s\n", file_name);
    if (Flags -> flag_c && !Flags -> flag_l)
        printf("%d\n", line_matches);
}

int grep_f_flag(char *pattern, char *file_name) {
    FILE *file;
    file = fopen(file_name, "r");
    int i = 0;
    if (file != NULL) {
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == 13 || ch == 10)
                pattern[i++] = '|';
            if (ch != 13 && ch != 10)
                pattern[i++] = ch;
        }
    } else {
        printf("error\n");
        i = -1;
    }
    if (pattern[i - 1] == '|')
        pattern[i - 1] = '\0';
    fclose(file);
    return i;
}