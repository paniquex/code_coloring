all: main

main: main.o analysing.o coloring.o input.o output.o
	gcc -Wall main.o analysing.o coloring.o input.o output.o -luuid -o main.out

debug: main.o analysing.o coloring.o input.o output.o
	gcc main.o analysing.o coloring.o input.o output.o -luuid -o main.out -g

gcov: main_gcov.o analysing_gcov.o coloring_gcov.o input_gcov.o output_gcov.o
	gcc -coverage -fprofile-arcs -ftest-coverage -lgcov main.o analysing.o coloring.o input.o output.o -luuid -o main.out

main.o: main.c
	gcc -Wall  main.c -c

input.o: input.c
	gcc -Wall  input.c -c

analysing.o: analysing.c
	gcc -Wall  analysing.c -c

coloring.o: coloring.c
	gcc -Wall  coloring.c -c

output.o: output.c
	gcc -Wall  output.c  -c

main_gcov.o: main.c
	gcc -Wall  main.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_gcov.o: input.c
	gcc -Wall  input.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

analysing_gcov.o: analysing.c
	gcc -Wall  analysing.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

coloring_gcov.o: coloring.c
	gcc -Wall  coloring.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

output_gcov.o: output.c
	gcc -Wall  output.c -coverage -fprofile-arcs -ftest-coverage -lgcov -c

clean:
	-rm *.o *.gcno *.gcda *.info main.out