import os

test_resolution = 1 + 6  # максимальное количество флагов в тесте
counter_success = 0
counter_fail = 0
test_file = "test.txt"
test_flags = ""
flags = ["-b", "-e", "-n", "-s", "-t", "-v", "-E", "-T", "--number-nonblank", "--number", "--squeeze-blank"]


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
            test_flags += test_flag + " "
        os.system('echo "{}"'.format(test_flags))
        os.system('./s21_cat {} {} > s21cat.txt'.format(test_flags, test_file))
        os.system('cat {} {} > cat.txt'.format(test_flags, test_file))
        s21cat = open('s21cat.txt', encoding="utf8", errors='ignore')
        s21cat = s21cat.read()
        cat = open('cat.txt', encoding="utf8", errors='ignore')
        cat = cat.read()
        if s21cat == cat:
            counter_success += 1
        else:
            counter_fail += 1
            print('ne Nice')
            print('Error with flags {}'.format(test_flags))
        test_flags = ''
print('Nice tests = {}'.format(counter_success))
print('Bad tests = {}'.format(counter_fail))
