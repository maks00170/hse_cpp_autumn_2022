CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: numpy test_bin

numpy: numpy.cpp numpy.hpp
	$(CC) $(FLAGS) -c numpy.cpp

test_bin: numpy.o tests.cpp
	$(CC) $(FLAGS) numpy.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin