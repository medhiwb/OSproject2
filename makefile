main: main.o readerwriter.o 
	gcc -std=c99 -o main main.o readerwriter.o -pthread

main.o: main.c
	gcc -c -std=c99 main.c -pthread

readerwriter.o: readerwriter.c
	gcc -c -std=c99 readerwriter.c -pthread

clean:
	rm *.o main