CFLAGS:=-Wall -Werror -Wextra -lstdc++ -std=c++17
UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	LDFLAGS= -lgtest -lgtest_main -pthread -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lgtest -lgtest_main -pthread
	OPEN_CM=open
endif


all: clean
	g++ main.cpp s21_list.hpp
	./a.out

t: clean
	g++ main2.cpp
	./a.out

test: clean
	g++ $(CFLAGS) -o s21_test s21_list_tests.cpp -lgtest -lgtest_main -pthread -lsubunit
	./s21_test

clean:
	rm -rf *.a *.o *.out *.gch s21_test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full -s ./s21_test

style:
	cp ../../../materials/linters/.clang-format .
	clang-format -n *.cpp *.hpp
	rm -rf .clang-format

edit_style:
	cp ../../../materials/linters/.clang-format .
	clang-format -i *.cpp *.hpp
	rm -rf .clang-format
