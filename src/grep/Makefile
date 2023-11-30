FLAGS: c11 -Wall -Werror -Wextra

all:
	make s21_grep
	make test
s21_grep:
	make clean
	gcc $(FLAGS) s21_grep.c -o s21_grep

run:
	./s21_grep

clean:
	rm -rf *.o s21_grep *grep.txt

test:
	python3 grep_test.py