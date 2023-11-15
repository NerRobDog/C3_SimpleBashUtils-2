FLAGS: c11 -Wall -Werror -Wextra

s21_grep:
	make clean
	gcc $(FLAGS) s21_grep.c -o s21_grep
	make run

run:
	./s21_grep -n 'abobus' Test.txt

clean:
	rm -rf *.o