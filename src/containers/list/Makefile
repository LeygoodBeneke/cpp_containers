UNAME:=$(shell uname -s)
GCC:= g++
CFLAGS:=-Wall -Werror -Wextra -lstdc++ -std=c++17

ifeq ($(UNAME),Linux)
	LDFLAGS= -lgtest -lgtest_main -pthread -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lgtest -lgtest_main -pthread
	OPEN_CM=open
endif

test: clean
	$(GCC) $(CFLAGS) -o s21_test s21_list.hpp s21_list_tests.cpp $(LDFLAGS) 
	./s21_test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full -s ./s21_test

clean: 
	rm -rf *.a *.o *.out *.gch s21_test

edit_style:
	cp ../../../materials/linters/.clang-format .
	clang-format -i *.cpp *.hpp
	rm -rf .clang-format
clean: 
	rm -rf *.a *.o *.out *.gch s21_test
