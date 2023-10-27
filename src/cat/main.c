#include <stdio.h>
#include <string.h>

// arg2 - аргумент
// arg3 - название файла

int main(int arg1, char* arg2[], char* arg3[]) {
    FILE* file;
    file = fopen(arg3[1], "r"); // arg3[0] ссылается на ./a.out
    
    // обработка некорректных данных
    if(!file || arg1 != 2) { // 2 = ложь
        printf("error");
    }
    
    // обработка аргумента команды
    switch(arg2[0]) {
        case 'b':
            // нумерация непустых строк
        case 'e':
            // отображает символы конца строки как $
        case 'n':
            // нумерует все выходные строки
        case 's':
            // сжимает несколько смежных пустых строк
        case 't':
            // также отображает табы как ^I
        default:
            //неверный ввод
    }
    
    //обработка введенных данных
    char ch;
    while((ch = fgetc(file)) != EOF) { // достигает конца файла
        printf("%c", ch);
    }
    fclose(file);
}
