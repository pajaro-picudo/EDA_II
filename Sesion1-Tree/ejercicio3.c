#include <stdio.h>
#include <string.h>
#include "arbol.h"
#include "genArbol.h"

int main(void)
{ Arbol arbol; 
  char ex_postfija[10];

/* Generaci�n del �rbol algebraico */
  strcpy(ex_postfija,"AB+CDE+**\0");

  arbol = genArbol(ex_postfija);

/* Recorrido en amplitud o por niveles */
   amplitud(arbol);

/* Aplicaci�n de algunas operaciones y recorridos al �rbol ejemplo */


  printf("Recorrido en PRE_ORDEN: ");
  preOrden(arbol);
  printf("\n");

  printf("Recorrido en ORDEN: ");
  enOrden(arbol);
  printf("\n");
  printf("Recorrido en POST_ORDEN: ");
  postOrden(arbol);
  printf("\n");
  printf("Debe coinicidir con la expresi�n postfija inicial\n");

  printf("El �rbol tiene %d nodos \n", numNodos(arbol));
  printf("y altura: %d\n",altura(arbol));

  printf("El �rbol tiene %d nodos\n", numNodos(arbol));
  arbol = Anula(arbol);
  printf("Despu�s de anula el arbol queda vacio, por tanto la altura ser� 0.\n");
  if (altura(arbol)!=-1)		// Cuidado con definici�n de altura
     printf("El �rbol no se ha anulado correctamente\n");
  else
     printf("O.K. Parece que la operaci�n anula funciona!!!\n");


/* Evaluaci�n de un �rbol algebraico: operandos entre '0' y '9'*/

  strcpy(ex_postfija,"23+713+**\0");
  arbol = genArbol(ex_postfija);
  printf("evalua: %d\n", evaluar(arbol));
  printf("Recorrido en PRE_ORDEN (prefija): ");
  preOrden(arbol);
  printf("\n");
  printf("Recorrido en ORDEN(infija): ");
  enOrden(arbol);
  printf("\n");
  printf("Recorrido en POST_ORDEN(postfija): ");
  postOrden(arbol);
  printf("\n");

/* Aplicar a este arbol las funciones del ejercicio 2 */

  return 1;
}
