all: main

main: main.o analysing.o coloring.o input_file.o input_stdin_type.o counting.o token.o
	g++ -Wall main.o analysing.o coloring.o counting.o input_file.o input_stdin_type.o token.o -luuid -o main.out

debug: main.o analysing.o coloring.o counting.o
	g++ main.o analysing.o coloring.o counting.o  input_file.o input_stdin_type.o token.o -luuid -o main.out -g

gcov: main_gcov.o analysing_gcov.o coloring_gcov.o counting_gcov.o input_file_gcov.o input_stdin_type_gcov.o token_gcov.o
	g++ -coverage -fprofile-arcs -ftest-coverage -lgcov main.o analysing.o coloring.o counting.o input_file.o input_stdin_type.o token.o -luuid -o main.out

main.o: main.cpp
	g++ -Wall  main.cpp -c

input_file.o: input_file.cpp
	g++ -Wall input_file.cpp -c

input_stdin_type.o: input_stdin_type.cpp
	g++ -Wall input_stdin_type.cpp -c

analysing.o: analysing.cpp
	g++ -Wall  analysing.cpp -c

coloring.o: coloring.cpp
	g++ -Wall  coloring.cpp -c

counting.o: counting.cpp
	g++ -Wall counting.cpp -c

token.o: token.cpp
	g++ -Wall token.cpp -c

main_gcov.o: main.cpp
	g++ -Wall  main.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_file_gcov.o: input_file.cpp
	g++ -Wall input_file.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_stdin_type_gcov.o: input_stdin_type.cpp
	g++ -Wall input_stdin_type.cpp -c

analysing_gcov.o: analysing.cpp
	g++ -Wall  analysing.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

coloring_gcov.o: coloring.cpp
	g++ -Wall  coloring.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

counting_gcov.o: counting.cpp
	g++ -Wall counting.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

token_gcov.o: token.cpp
	g++ -Wall token.cpp  -coverage -fprofile-arcs -ftest-coverage -lgcov -c

clean:
	-rm *.o *.gcno *.gcda *.info main.out