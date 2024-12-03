CC=gcc
CPPFLAGS=-std=c++17 -Wall -Wextra -Werror
SRC=s21_matrix_oop.cc 

ifeq ($(OS),Windows_NT)
    LDFLAGS=-lgtest -lgmock -lstdc++ -lcheck -lm
    EXT=.exe
else
    LDFLAGS=-lgtest -lgmock -lstdc++ -lcheck -lm -pthread
    EXT=
endif


#Provide a Makefile for building the library and tests (with targets all, clean, test, s21_matrix_oop.a).
all: s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CPPFLAGS) -c $(SRC)
	ar rcs s21_matrix_oop.a *.o
	rm -f *.o

test: 
	g++ -std=c++17 -Wall -Wextra -Werror -c s21_matrix_oop.cc -o s21_matrix_oop.o
	g++ -std=c++17 -Wall -Wextra -Werror -c tests.cc -o tests.o
	g++ -std=c++17 -Wall -Wextra -Werror tests.o s21_matrix_oop.o $(LDFLAGS) -o tests
	./tests

style:
	clang-format --style=google -i *.h
	clang-format --style=google -i *.cc

clean:
	rm -f *.o main test.out tests s21_matrix_oop.a
	clear