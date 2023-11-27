FLAGS: c11 -Wall -Werror -Wextra

s21_cat:
	make clean
	gcc $(FLAGS) s21_cat.c -o s21_cat
	make test

run:
	./s21_cat

clean:
	rm -rf *.o

test:
	python3 ../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h
	python3 cat_test.py