#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main () {

    Arbol varArbol;

    /* Creación arbol ejemplo de las transparencias de recorridos */
      varArbol = creaNodo('A');
      varArbol->izq=creaNodo('B');
      varArbol->der = creaNodo('C');
      varArbol->izq->izq=creaNodo('D');
      varArbol->izq->der=creaNodo('E');
      varArbol->der->izq=creaNodo('F');
      varArbol->der->der=creaNodo('G');
    
      printf("La altura del árbol es: %d\n", altura(varArbol));
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