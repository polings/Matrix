CC = g++
STDFLAGS = -Wall -Werror -Wextra -std=c++17
TARGET = s21_matrix_oop.a
LIBS = -lstdc++
TEST_FLAGS = -lgtest -lpthread
all: clean test gcov_report
	
$(TARGET): 
	$(CC) $(STDFLAGS) $(LIBS) -c s21*.cc 
	ar rc $@ *.o
	ranlib $@

test: clean $(TARGET)
	$(CC) $(STDFLAGS) *.cc $(TARGET) $(LIBS) $(TEST_FLAGS) -o test --coverage 
	./test

gcov_report: test
	lcov -t test -o test.info -c -d . --ignore-errors mismatch
	lcov -e test.info '*/src/s21_matrix_oop.cc' -o test_filtered.info
	genhtml -o gcov_report test_filtered.info
	open ./gcov_report/index.html

clean: 
	@rm -rf *.o *.a test_report *.g* *.info gcov_report test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test

style:
	clang-format -n -style=google *.cc *.h

