FLAGS: c11 -Wall -Werror -Wextra

s21_grep:
	make clean
	gcc $(FLAGS) s21_grep.c -o s21_grep
	make run

run:
	./s21_grep

clean:
	rm -rf *.o

test:
	python3 grep_test.py