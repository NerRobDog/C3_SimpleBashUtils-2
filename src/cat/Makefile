FLAGS: c11 -Wall -Werror -Wextra

s21_cat:
	make clean
	gcc $(FLAGS) s21_cat.c -o s21_cat
	make run

run:
	./s21_cat -b test.txt

clean:
	rm -rf *.o

test:
	./s21_cat -b test.txt