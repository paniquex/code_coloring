all: main

main: main.o analysing.o coloring.o input.o input_file.o input_stdin_type.o counting.o
	gcc -Wall main.o analysing.o coloring.o counting.o input.o input_file.o input_stdin_type.o -luuid -o main.out

debug: main.o analysing.o coloring.o input.o counting.o
	gcc main.o analysing.o coloring.o counting.o input.o input_file.o input_stdin_type.o -luuid -o main.out -g

gcov: main_gcov.o analysing_gcov.o coloring_gcov.o counting_gcov.o input_gcov.o input_file.o input_stdin_type.o
	gcc -coverage -fprofile-arcs -ftest-coverage -lgcov main.o analysing.o coloring.o counting.o input.o input_file.o input_stdin_type.o -luuid -o main.out

main.o: main.c
	gcc -Wall  main.c -c

input.o: input.c
	gcc -Wall  input.c -c

input_file.o: input_file.c
	gcc -Wall input_file.c -c

input_stdin_type.o: input_stdin_type.c
	gcc -Wall input_stdin_type.c -c

analysing.o: analysing.c
	gcc -Wall  analysing.c -c

coloring.o: coloring.c
	gcc -Wall  coloring.c -c

counting.o: counting.c
	gcc -Wall counting.c -c

main_gcov.o: main.c
	gcc -Wall  main.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_gcov.o: input.c
	gcc -Wall  input.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_file_gcov.o: input_file.c
	gcc -Wall input_file.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_stdin_type_gcov.o: input_stdin_type_gcov.c
	gcc -Wall input_stdin_type.c -c

analysing_gcov.o: analysing.c
	gcc -Wall  analysing.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

coloring_gcov.o: coloring.c
	gcc -Wall  coloring.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

counting_gcov.o: counting.c
	gcc -Wall counting.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

clean:
	-rm *.o *.gcno *.gcda *.info main.out