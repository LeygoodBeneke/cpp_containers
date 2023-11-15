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
	g++ $(CFLAGS) main.cpp s21_list.h
	./a.out

test: clean
	g++ $(CFLAGS) -o s21_test main.cpp s21_list.hpp s21_list_tests.cpp $(LDFLAGS) 

clean:
	rm -rf *.a *.o *.out *.gch s21_test

#s21_list_const_iterators.tpp s21_list_iterators.tpp