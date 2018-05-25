#To run: `make main.o`

CXX = g++
CXXFLAGS = -std=c++0x

SRCS = main.cpp load_tsp_input.cpp near_greedy.cpp two_opt.cpp

#TXTFILE = tsp_test_4.txt
#TXTFILE = tsp_example_1.txt
#TXTFILE = tsp_example_2.txt
#TXTFILE = tsp_example_3.txt
#TXTFILE = test-input-1.txt
#TXTFILE = test-input-2.txt
TXTFILE = test-input-3.txt
#TXTFILE = test-input-4.txt
#TXTFILE = test-input-5.txt
#TXTFILE = test-input-6.txt
#TXTFILE = test-input-7.txt

HEADERS = load_tsp_input.h near_greedy.h two_opt.h

#Note on main.o:
#
#	The last line of main.o runs `tsp-verifier.py` program
#	which was provided to us.
#
#	It will confirm the input and outmatch match and
#	give the length of the solution.

clean_all:
	rm -f main.o
	rm -f ${TXTFILE}.tour
	rm -f *.out

main.o: clean_all ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o main.o
	
	./main.o ${TXTFILE}
	python tsp-verifier.py ${TXTFILE} ${TXTFILE}.tour


