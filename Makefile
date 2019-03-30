all: main

main: main.o analysing.o coloring.o input.o
	gcc main.o analysing.o coloring.o input.o -luuid -o main.out

main.o: main.c
	gcc main.c -c

input.o: input.c
	gcc input.c -c

analysing.o: analysing.c
	gcc analysing.c -c

coloring.o: coloring.c
	gcc coloring.c -c

clean:
	-rm *.o main.out