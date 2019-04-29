ifndef CXX
	COMPILER = g++
else
	COMPILER = ${CXX}
endif

ifndef VERSION
	VERSION = c++14
endif

FSN_PATH = ../include/
COMPILER_FLAGS = -O3 -Wall -Wextra -pedantic -Wfloat-equal -Wconversion
LINKER_FLAGS = -lgtest -lgtest_main

OBJECTS = ./obj/w_int_arithmetic_test.o

all: ${OBJECTS}
	${COMPILER} -o ./run ${LINKER_FLAGS} ${OBJECTS}

./obj/w_int_arithmetic_test.o: ./numeric/w_int_arithmetic_test.cpp
	mkdir -p obj && ${COMPILER} -std=${VERSION} -c -o ./obj/w_int_arithmetic_test.o -I ${FSN_PATH} -I ./ ${COMPILER_FLAGS} ./numeric/w_int_arithmetic_test.cpp

clean:
	rm -rf obj run
	