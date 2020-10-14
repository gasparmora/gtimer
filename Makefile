gtimer: main.c
	gcc -Wall -o gtimer main.c -lm -lncurses

clean:
	rm -f gtimer
