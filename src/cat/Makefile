FLAGS: C11 -Wall -Werror -Wextra

all:
	make s21_cat
	make test
s21_cat:
	make clean
	gcc $(FLAGS) s21_cat.c -o s21_cat

run:
	./s21_cat

clean:
	rm -rf *.o s21_cat *cat.txt

test:
	python3 cat_test.py