LDFLAGS=-I headers -I token_headers

main: main.o analysing.o  input_file.o input_stdin_type.o counting.o token.o
	g++ -Wall $(LDFLAGS) main.o analysing.o  counting.o input_file.o input_stdin_type.o token.o -luuid -o main.out

debug: main.o analysing.o  counting.o
	g++ -Wall $(LDFLAGS) main.o analysing.o  counting.o  input_file.o input_stdin_type.o token.o -luuid -o main.out -g

gcov: main_gcov.o analysing_gcov.o counting_gcov.o input_file_gcov.o input_stdin_type_gcov.o token_gcov.o
	g++ -coverage -fprofile-arcs -ftest-coverage -lgcov $(LDFLAGS) main.o analysing.o  counting.o input_file.o input_stdin_type.o token.o -luuid -o main.out

main.o: main.cpp
	g++ -Wall $(LDFLAGS)  main.cpp -c

input_file.o:
	g++ -Wall $(LDFLAGS) source/input_file.cpp -c

input_stdin_type.o:
	g++ -Wall $(LDFLAGS) source/input_stdin_type.cpp -c

analysing.o: analysing.cpp
	g++ -Wall $(LDFLAGS) analysing.cpp -c

counting.o:
	g++ -Wall $(LDFLAGS) token_sources/counting.cpp -c

token.o:
	g++ -Wall $(LDFLAGS) token_sources/token.cpp -c

main_gcov.o:
	g++ -Wall $(LDFLAGS)  main.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_file_gcov.o:
	g++ -Wall $(LDFLAGS) source/input_file.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

input_stdin_type_gcov.o:
	g++ -Wall $(LDFLAGS) source/input_stdin_type.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

analysing_gcov.o:
	g++ -Wall $(LDFLAGS) analysing.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c


counting_gcov.o:
	g++ -Wall $(LDFLAGS) token_sources/counting.cpp -coverage -fprofile-arcs -ftest-coverage -lgcov -c

token_gcov.o:
	g++ -Wall $(LDFLAGS) token_sources/token.cpp  -coverage -fprofile-arcs -ftest-coverage -lgcov -c

clean:
	rm *.gcda *.gcno *.o main.out