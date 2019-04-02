all: main

main: main.o analysing.o coloring.o input.o output.o
	gcc -Wall main.o analysing.o coloring.o input.o output.o -luuid -o main.out

debug: main.o analysing.o coloring.o input.o output.o
	gcc main.o analysing.o coloring.o input.o output.o -luuid -o main.out -g

main.o: main.c
	gcc -Wall  main.c -c

input.o: input.c
	gcc -Wall  input.c -c

analysing.o: analysing.c
	gcc -Wall  analysing.c -c

coloring.o: coloring.c
	gcc -Wall  coloring.c -c

output.o: output.c
	gcc -Wall  output.c -c

clean:
	-rm *.o main.out