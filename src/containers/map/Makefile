UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux)
	LDFLAGS= -lgtest -lgtest_main -pthread -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lgtest -lgtest_main -pthread
	OPEN_CM=open
endif



all: g++ s21_map.hpp main.cpp

test: 
	g++ -o s21_test s21_map.hpp s21_map_tests.cpp -Wall -Werror -Wextra -lstdc++ -std=c++17 $(LDFLAGS) 
	./s21_test
	
deafult: all


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
clean: 
	rm -rf *.a *.o *.out *.gch s21_test