CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: ser test_bin

ser: ser.cpp ser.hpp
	$(CC) $(FLAGS) -c ser.cpp

test_bin: ser.o test.cpp
	$(CC) $(FLAGS) ser.o test.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin