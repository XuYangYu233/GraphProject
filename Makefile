search-cli: main.o search.o stats.o
	gcc -o search-cli main.o search.o stats.o

main.o: main.c stats.h search.h
	gcc -c main.c

search.o: search.c search.h
	gcc -c search.c search.h

stats.o: stats.c stats.h
	gcc -c stats.c stats.h

clean:
	del *.o *.gch