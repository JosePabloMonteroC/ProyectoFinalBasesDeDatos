programa.out: main.o funciones.o
	gcc -o programa.out main.o funciones.o -lnsl -lm -lz -lmysqlclient

funciones.o: funciones.c
	gcc -c funciones.c
	
main.o: main.c
	gcc -c main.c
