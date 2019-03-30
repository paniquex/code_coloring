all: main

main: main.o analysing.o coloring.o input.o output.o
	gcc main.o analysing.o coloring.o input.o output.o -luuid -o main.out

debug: main.o analysing.o coloring.o input.o output.o
	gcc main.o analysing.o coloring.o input.o output.o -luuid -o main.out -g

main.o: main.c
	gcc main.c -c

input.o: input.c
	gcc input.c -c

analysing.o: analysing.c
	gcc analysing.c -c

coloring.o: coloring.c
	gcc coloring.c -c

output.o: output.c
	gcc output.c -c

clean:
	-rm *.o main.out