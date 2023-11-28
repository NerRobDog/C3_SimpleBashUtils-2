#include "s21_grep.h"

int main(int count, char *buffer[]) {
    struct flag flag = {0};
    char pattern_buffer[BUFFER_SIZE] = {0};

    grep_flags(count, buffer, &flag, pattern_buffer);
    if (count >= 3) {
        grep_launcher(&flag, count, buffer, pattern_buffer);
    }
    return 0;
}

void grep_flags(int count, char **buffer, struct flag *flag, char *pattern_buffer) {
    int flag_value = 0;
    const char* f_options = "e:ivclnhsf:o";

    while ((flag_value = getopt(count, buffer, f_options)) != -1) {
        switch (flag_value) {
            case 'e':
                flag -> flag_e = 1;
                snprintf(pattern_buffer, BUFFER_SIZE, "%s", optarg);  // getopt(3) external variables
                break;
            case 'i':
                flag -> flag_i = 1;
                break;
            case 'v':
                flag -> flag_v = 1;
                break;
            case 'c':
                flag -> flag_c = 1;
                break;
            case 'l':
                flag -> flag_l = 1;
                break;
            case 'n':
                flag -> flag_n = 1;
                break;
            case 'h':
                flag -> flag_h = 1;
                break;
            case 's':
                flag -> flag_s = 1;
                break;
            case 'f':
                flag -> flag_f = 1;
                snprintf(pattern_buffer, BUFFER_SIZE, "%s", optarg);
                break;
            case 'o':
                flag -> flag_o = 1;
                break;
            default:
                printf("ERROR: invalid arguments\n");
                break;
        }
    }
}

void grep_launcher(struct flag *flag, int count, char **buffer, char *buff) {
    char pattern[BUFFER_SIZE] = {0}; // пустой шаблон
    int end_of_pattern = 0;
    if (!flag -> flag_f && !flag -> flag_e) { // если нет шаблона
        snprintf(pattern, BUFFER_SIZE, "%s", buffer[optind++]);
    }
    if (flag -> flag_f) { // регулярки (press F)
        end_of_pattern = grep_f_flag(pattern, buff); // вызов функции
    }
    if (!flag -> flag_f && flag -> flag_e) { // шаблон без регулярки
        snprintf(pattern, BUFFER_SIZE, "%s", buff);
    }
    if (end_of_pattern != -1) { //если без ошибок
        int file_count = 0;
        if (count - optind > 1) { // optind - индекс текущего параметра
            file_count = 1;
        }
        for (int i = optind; i < count; i++) { //
            if (file_count && !flag -> flag_h && !flag -> flag_l) { // если файл есть
                   printf("%s:", buffer[i]);
            }
            grep_file(flag, pattern, buffer[i]);
        }
    }
}

void grep_file(struct flag *flag, char *pattern, char *file_name) {
    int cflags = REG_EXTENDED; // расш. регулярные выражения
    regex_t reg; // f
    FILE *file;
    file = fopen(file_name, "r");
    if (flag -> flag_i) {
        cflags = REG_ICASE; // не учитывать регистр
    }
    if (file != NULL) {
        regcomp(&reg, pattern, cflags); // обработка рег. выр.
        grep_process(flag, file, reg, file_name);
        regfree(&reg); // высвобождение
        fclose(file);
    }
}

void grep_process(struct flag *flag, FILE *file, regex_t reg, char *file_name) {
    char text[BUFFER_SIZE] = {0};
    regmatch_t pmatch[1];
    int line_matches = 0, line_number = 1;

    while (fgets(text, BUFFER_SIZE - 1, file) != NULL) { // считывает данные с потока и делает из них строку
        int match = 0; //bool
        int success = regexec(&reg, text, 1, pmatch, 0);  // успешность поиска слова       может не bool

        if (strchr(text, '\n') == NULL) // порядковый номер (с единицы)
            strcat(text, "\n");
        if (success == 0 && !flag -> flag_v)
            match = 1;
        if (success == REG_NOMATCH && flag -> flag_v)
            match = 1;
        if (match && !flag -> flag_l && !flag -> flag_c && flag -> flag_n)
            printf("%d:", line_number); // нумерует все строки
        if (match && !flag -> flag_l && !flag -> flag_c && !flag -> flag_o)
            printf("%s", text);  // просто выводит совпадение
        if (match && flag -> flag_o) {
            for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) { // выводит нужный кусок строки (совпадение)
                printf("%c", text[i]);
            }
            printf("\n");
        }
        line_matches += (int)match;
        line_number++;
    }
    if (flag -> flag_l && line_matches > 0)
        printf("%s\n", file_name);
    if (flag -> flag_c && !flag -> flag_l)
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