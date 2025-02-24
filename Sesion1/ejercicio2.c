#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main () {

    Arbol varArbol;
    Arbol varArbol2;

    /* Creación arbol ejemplo de las transparencias de recorridos */
      varArbol = creaNodo('A');
      varArbol->izq=creaNodo('B');
      varArbol->der = creaNodo('C');
      varArbol->izq->izq=creaNodo('D');
      varArbol->izq->der=creaNodo('B');
      varArbol->der->izq=creaNodo('F');
      varArbol->der->der=creaNodo('G');
    
      amplitud(varArbol);
      printf("\n");
      printf("La altura del árbol es: %d\n", altura(varArbol));
      printf("El número de nodos del árbol es: %d\n", numNodos(varArbol));
      varArbol2 = (varArbol);
      printf("El Árbol ha sido anulado: altura = %d \n", numNodos(varArbol)); //No se si está funcionando bien
      printf("Vamos a sustituir las B por A, el número de sustituciones que ha habido es: %d\n", sustituye(varArbol, 'B', 'A'));
      amplitud(varArbol);
      printf("\n");
    }

int altura(Arbol raiz) {

    if (raiz == NULL) {
        return 0;
    } else {
        int alturaIzq = altura(raiz->izq);
        int alturaDer = altura(raiz->der);

        if (alturaIzq > alturaDer) {
            return alturaIzq + 1;
        } else {
            return alturaDer + 1;
        }
    }

}

int numNodos(Arbol raiz) {

    if (raiz == NULL) {
        return 0;
    } else {
        return 1 + numNodos(raiz->izq) + numNodos(raiz->der);
    }
}

Arbol anula(Arbol raiz) {

    if (raiz != NULL) {
        anula(raiz->izq);
        anula(raiz->der);
        free(raiz);
    }
    return raiz;

}

int sustituye(Arbol raiz, tipoInfo x, tipoInfo y) {

    int sustituciones = 0;
    if (raiz != NULL) {
        if (raiz->info == x) {
            raiz->info = y;
            sustituciones++;
        }
        sustituciones += sustituye(raiz->izq, x, y);
        sustituciones += sustituye(raiz->der, x, y);
    }
    return sustituciones;
}

/*

int numNodosHoja(Arbol raiz);
int numNodosInternos(Arbol raiz);
int numHijoUnico(Arbol raiz);
Arbol buscarMax(Arbol raiz);
Arbol buscarMin(Arbol raiz);
int similares(Arbol r1,Arbol r2);
int equivalentes(Arbol r1,Arbol r2);
Arbol especular(Arbol raiz);*/