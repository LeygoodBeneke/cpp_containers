FLAGS=-Wall -Werror -Wextra -std=c++17
COVERAGE=

.PHONY: all clean test add_coverage gcov_report

all: clean test
deafult: all

test: clean
	g++ $(FLAGS) $(COVERAGE) tests/s21_tests.cpp tests/*/*.cpp -o s21_test -lgtest
	./s21_test

add_coverage:
	$(eval FLAGS += --coverage)

style_test:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" -or -name "*.hpp" | xargs clang-format -n

style_edit:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" -or -name "*.hpp" | xargs clang-format -i

valgrind: test
	valgrind --leak-check=full ./s21_test

clean:
	rm -rf *.a *.o *.out *.html *.css *.gcno *.gcov *.gcda s21_test report
