CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: token_split test_bin

token_split: token_split.cpp token_split.hpp
	$(CC) $(FLAGS) -c token_split.cpp

test_bin: token_split.o tests.cpp
	$(CC) $(FLAGS) token_split.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin