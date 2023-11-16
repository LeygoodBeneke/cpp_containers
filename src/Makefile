FLAGS=-Wall -Werror -Wextra -std=c++17
COVERAGE=

.PHONY: all clean test add_coverage gcov_report

all: clean s21_containers.a
deafult: all

s21_containers.o: containers/*/*.cc
	g++ $(FLAGS) -c $^

s21_containers.a: s21_containers.o
	ar rvs s21_containers.a *.o


test: clean s21_containers.a
	g++ $(FLAGS) $(COVERAGE) tests/s21_tests.cpp tests/*/*.cpp s21_containers.a -o s21_test -lgtest
	./s21_test

add_coverage:
	$(eval FLAGS += --coverage)

style_test:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" | xargs clang-format -n

style_edit:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" | xargs clang-format -i

valgrind: test
	valgrind --leak-check=full ./s21_test

clean:
	rm -rf *.a *.o *.out *.html *.css *.gcno *.gcov *.gcda s21_test report
