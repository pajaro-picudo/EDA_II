#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main () {

    Arbol varArbol;
    Arbol varArbol2;

    /* Creación arbol ejemplo de las transparencias de recorridos */
      varArbol = creaNodo(1);
      varArbol->izq=creaNodo(2);
      varArbol->der = creaNodo(3);
      varArbol->izq->izq=creaNodo(1);
      varArbol->izq->der=creaNodo(5);
      varArbol->der->izq=creaNodo(6);
      varArbol->der->der=creaNodo(1);
      varArbol->izq->izq->izq=creaNodo(8);
      varArbol->der->der->der=creaNodo(9);
    
      amplitud(varArbol);
      printf("\n");
      printf("La altura del árbol es: %d\n", altura(varArbol));
      printf("El número de nodos del árbol es: %d\n", numNodos(varArbol));
      varArbol2 = (varArbol);
      printf("El Árbol ha sido anulado: altura = %d \n", numNodos(varArbol)); //No se si está funcionando bien
      printf("Vamos a sustituir los 1 por 3, el número de sustituciones que ha habido es: %d\n", sustituye(varArbol, 1, 3));
      amplitud(varArbol);
      printf("\n");
      printf("El número de nodos hoja del árbol es: %d\n", numNodosHoja(varArbol));
      printf("El número de nodos internos del árbol es: %d\n", numNodosInternos(varArbol));
      printf("El número de nodos con un solo hijo del árbol es: %d\n", numHijoUnico(varArbol));
      printf("El nodo con el valor más alto es: %c\n", buscarMax(varArbol)->info);

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

int numNodosHoja(Arbol raiz) {

if (raiz != NULL) {

    if (raiz->izq == NULL && raiz->der == NULL) {
        return 1;
    } else {
        return numNodosHoja(raiz->izq) + numNodosHoja(raiz->der);
    }

}

}

int numNodosInternos(Arbol raiz) {

    if(raiz != NULL) {

        if (raiz->izq != NULL || raiz->der != NULL) {
            return 1 + numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
        } else {
            return numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
        }

    }
}

int numHijoUnico(Arbol raiz) {
 
    if (raiz != NULL) {

        if ((raiz->izq != NULL && raiz->der == NULL) || (raiz->izq == NULL && raiz->der != NULL)) 
        return 1 + numHijoUnico(raiz->izq) + numHijoUnico(raiz->der);
        else 
        return numHijoUnico(raiz->izq) + numHijoUnico(raiz->der);
        
    }
    else return 0;
}


Arbol buscarMax(Arbol raiz) {

Arbol izqMax, derMax;

if (raiz == NULL) {
    return NULL;
}

if (raiz->izq != NULL) izqMax = buscarMax(raiz->izq);
if (raiz->der != NULL) derMax = buscarMax(raiz->der);



    if ((raiz->info > buscarMax(raiz->izq)->info && raiz->info > buscarMax(raiz->der)->info) && (raiz->izq != NULL && raiz->der != NULL)) {
        return raiz;
    } else if ((buscarMax(raiz->izq)->info > buscarMax(raiz->der)->info) && raiz->izq != NULL) {
        return buscarMax(raiz->izq);
    } else if(raiz->der != NULL) {
        return buscarMax(raiz->der);
    }



}


/*




Arbol buscarMin(Arbol raiz);
int similares(Arbol r1,Arbol r2);
int equivalentes(Arbol r1,Arbol r2);
Arbol especular(Arbol raiz);*/