all: main.c
	gcc -Wall -o terminal main.c util/util.c
