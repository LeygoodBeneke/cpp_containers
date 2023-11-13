style_test:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" | xargs clang-format -n

style_edit:
	find . -name "*.cpp" -or -name ".cc" -or -name "*.h" -or -name "*.c" | xargs clang-format -i

valgrind: test
	valgrind --leak-check=full ./s21_test
