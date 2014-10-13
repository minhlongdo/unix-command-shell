all: main.c
	gcc -g -I `pkg-config --cflags --libs gtk+-2.0` -o terminal main.c util/util.c
