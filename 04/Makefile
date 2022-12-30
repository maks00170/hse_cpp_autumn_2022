CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: big test_bin

big: big.cpp big.hpp
	$(CC) $(FLAGS) -c big.cpp

test_bin: big.o test.cpp
	$(CC) $(FLAGS) big.o test.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin