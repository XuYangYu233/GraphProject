search-cli: main.o search.o stats.o queue.o
	gcc -o search-cli main.o search.o stats.o queue.o

main.o: main.c stats.h search.h
	gcc -c main.c stats.h search.h

stats.o: stats.c stats.h queue.c queue.h
	gcc -c stats.c stats.h queue.c queue.h

search.o: search.c search.h queue.c queue.h
	gcc -c search.c search.h queue.c queue.h

queue.o : queue.c queue.h
	gcc -c queue.c queue.h

clean:
	rm -f *.o *.gch
