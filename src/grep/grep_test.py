import os
import sys
from random import randint

test_resolution = 1 + 5  # максимальное количество флагов в тесте
counter_success = 0
counter_fail = 0
test_file = "test.txt"
#sys.stdout = open("log.txt", "w")
test_flags = ""
flags = ["-e", "-i", "-v", "-c", "-l", "-n", "-h", "-s", "-f", "-o"]
template = ''
test_files = ''


def combinator_duplicator(flags, jars_count):  # def - тип данных не имеет значения
    # jars_count (2) --> AA AB AC | jars_count (3) --> AAA AAB AAC
    flags = tuple(flags)  # константный массив
    pool_len = len(flags)
    index = [0] * jars_count
    yield tuple(flags[i] for i in index)  # yield - заполняет весь массив index элементом i
    while True:
        for j in reversed(range(jars_count)):  # j - содержимое банки | jars_count - номер банки
            if index[j] != pool_len - 1:  #если индекс не дошел до конца массива
                break
        else:
            return #завершает работу функции когда цикл закончен
        index[j:] = [index[j] + 1] * (jars_count - j)
        yield tuple(flags[k] for k in index)


for jars_count in range(1, test_resolution):  # start, stop, step
    jars = list(combinator_duplicator(flags, jars_count))
    for i in range(len(jars)):
        # цикл приносит по очереди каждый кортеж | len(jars) = количество возможных комбинаций (количество кортежей)
        for j in reversed(range(jars_count)):  # приносит по очереди банки
            test_flag = str(jars[i][j - 1])
            test_flags += test_flag + " "
        template = open('test.txt', 'r')
        template = template.read()
        template = template.split('.')
        big_template = template[randint(0, len(template) - 1)]
        big_template = big_template.split(' ')
        notvalid_template = big_template\
                           [randint(0, len(big_template) - 1)] + big_template[randint(0, len(big_template) - 1)]
        valid_template = big_template\
                        [randint(0, len(big_template) - 1)]
        if i%2 == 0:
            template = valid_template
        else:
            template = notvalid_template
        os.system('echo "test flags = {0} template = {1}"'.format(test_flags, template))
        os.system("./s21_grep {flags} '{template}' {test_files} > s21_grep.txt".format\
                  (flags=test_flags, template=valid_template, test_files=test_file))
        os.system("grep {flags} '{template}' {test_files} > grep.txt".format\
                  (flags=test_flags, template=valid_template, test_files=test_file))
        s21_grep = open('s21_grep.txt', 'r')
        s21_grep = s21_grep.read()
        grep = open('grep.txt', 'r')
        grep = grep.read()
        if s21_grep == grep:
            counter_success += 1
            print('\n')
        else:
            counter_fail += 1
            print('ne Nice')
            print('Error with flags {} and template {}\n'.format(test_flags, template))
        test_flags = ''
print('Nice tests = {}'.format(counter_success))
print('Bad tests = {}'.format(counter_fail))
