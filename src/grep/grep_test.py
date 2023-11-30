import os
from random import randint

test_resolution = 1 + 2  # максимальное количество флагов в тесте
counter_success = 0
counter_fail = 0
test_file = "test.txt"
test_flags = ""
flags = ["-e", "i", "v", "c", "o", "n", "h", "s", "o"]


def combinator_duplicator(flags, jars_count):  # def - тип данных не имеет значения
    # jars_count (2) --> AA AB AC | jars_count (3) --> AAA AAB AAC
    flags = tuple(flags)  # константный массив
    pool_len = len(flags)
    index = [0] * jars_count
    yield tuple(flags[i] for i in index)  # yield - заполняет весь массив index элементом i
    while True:
        for j in reversed(range(jars_count)):  # j - содержимое банки | jars_count - номер банки
            if index[j] != pool_len - 1:  # если индекс не дошел до конца массива
                break
        else:
            return  # завершает работу функции когда цикл закончен
        index[j:] = [index[j] + 1] * (jars_count - j)
        yield tuple(flags[k] for k in index)


for jars_count in range(1, test_resolution):  # start, stop, step
    jars = list(combinator_duplicator(flags, jars_count))
    for i in range(len(jars)):
        # цикл приносит по очереди каждый кортеж | len(jars) = количество возможных комбинаций (количество кортежей)
        for j in reversed(range(jars_count)):  # приносит по очереди банки
            test_flag = str(jars[i][j - 1])
            test_flags += test_flag
        test_flags = '-' + test_flags
        test_template = ''
        input_str = '{flags}'.format(flags=test_flags)
        input_str = input_str.replace('--e', '-e')
        delete = 0
        for o in 'vclhi':
            if input_str.find(f'{o}') > 0 and input_str.find('o') > 0:
                input_str = ''
                delete = 1
        if delete == 1:
            test_flags = ''
            continue
        template = open('test.txt', 'r')
        template = template.read()
        template = template.split('.')
        big_template = template[0]  # Номер строки шаблонов
        big_template = big_template.split(' ')
        not_valid_template = big_template[randint(0, len(big_template) - 1)] * 2
        valid_template = big_template[randint(0, len(big_template) - 1)]

        if i % 2 == 0:  # Частота отсутствующих шаблонов
            template = valid_template
        else:
            template = not_valid_template

        if input_str[0:2] == '-e':
            input_str = " " + input_str
            input_str = input_str.replace('-e', '-e ')
            for k in flags[1:]:
                input_str = input_str.replace(' {char}'.format(char=k), ' -{char}'.format(char=k))
            input_str = input_str.replace('-e', "-e '{template}'".format(template=template))
        elif '-e' in input_str:
            input_str = input_str[1:]
            for k in flags[1:]:
                input_str = input_str.replace('{char}'.format(char=k), ' -{char}'.format(char=k))
            input_str = input_str.replace('-e', " -e '{template}'".format(template=template))
        else:
            input_str = input_str + ' ' + template
            input_str = " " + input_str

        os.system('echo "test command = {input}"'.format(input=input_str))
        os.system("./s21_grep{input} {test_files} > s21_grep.txt".format(input=input_str, test_files=test_file))
        os.system("grep{input} {test_files} > grep.txt".format(input=input_str, test_files=test_file))
        s21_grep = open('s21_grep.txt', 'r')
        s21_grep = s21_grep.read()
        grep = open('grep.txt', 'r')
        grep = grep.read()
        if s21_grep == grep:
            counter_success += 1
        else:
            counter_fail += 1
            print('ne Nice')
            print('Error with flags {}'.format(test_flags))
            exit(1)
        test_flags = ''
print('Nice tests = {}'.format(counter_success))
print('Bad tests = {}'.format(counter_fail))
exit(0)
