# Sesión 2 Implementación de las funciones del ejercicio2

all: ejercicio1 ejercicio2 limpiar

# Ejercicio 1: Recorridos en árboles binarios

ejercicio1: ejercicio1.c arbol.o cola.o
	gcc -g ejercicio1.c arbol.o cola.o -o ejercicio1

# Ejercicio 2: Aplicar las funciones recursivas del ejercicio2 a los arboles de los ejercicios 1 y 3

ejercicio2: ejercicio2.c arbol.o cola.o
	gcc -g ejercicio2.c arbol.o cola.o -o ejercicio2

# Sesión 1 	Aplicación de los TAD's pila y cola en la generación y recorrido de árboles binarios

ejercicio3: ejercicio3.c arbol.o genArbol.o pila.o cola.o
	gcc -g ejercicio3.c arbol.o genArbol.o pila.o cola.o -o ejercicio3
arbol.o: arbol.h arbol.c 
	gcc -c -g arbol.c 
genArbol.o: genArbol.c  
	gcc -c genArbol.c 
cola.o: cola.h cola.c 
	gcc -g -c cola.c
pila.o: pila.c pila.h arbol.h
	gcc -c pila.c
limpiar:
	rm -f *.o




