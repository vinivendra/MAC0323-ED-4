execName = ep4
execOptions =  -g -o $(execName) -lm -lc
objOptions = -g -pedantic -Wall -lm -lc -c
objects = main.o Hash1.o Item.o

.PHONY:default
default: $(objects)
	gcc $(objects) $(execOptions)

main.o: main.c
	gcc -g -pedantic -Wall -lm -lc -c main.c

Hash1.o: Hash1.c Item.c
	gcc -g -pedantic -Wall -lm -lc -c Hash1.c

Item.o: Item.c
	gcc -g -pedantic -Wall -lm -lc -c Item.c

clean:
	rm -f *.o $(execName)
