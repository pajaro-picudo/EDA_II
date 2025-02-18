#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c)
{
    
    c = (Cola*)malloc(sizeof(Cola));

    
    c->frente = c->fondo = NULL;
    
    return 0;
    
}

int colaVacia(Cola *c)
{

    if ((c->frente == NULL) && (c->fondo == NULL)) {
    
    return 0;
    
    }
    
    return 1;
    
    
}

int colaInserta(Cola *c,tipoElemento elemento)
{

        tipoCelda *nuevaCelda = (tipoCelda*)malloc(sizeof(tipoCelda));

        nuevaCelda->elemento = elemento;
        nuevaCelda->sig = NULL;
        
        if (colaVacia(c)) {
        
            c->frente = nuevaCelda;
            c->fondo = nuevaCelda;
        
        }
        else if (c->fondo != NULL) {
        
            c->frente = c->fondo = nuevaCelda;
            return 0; 
        
        }
        
        c->fondo->sig = nuevaCelda;
        c->fondo = nuevaCelda;
        
        return 0;
        
}

tipoElemento colaSuprime(Cola *c)
{
    
    if (colaVacia(c)) {
    
     printf ("Error: Cola vacia");
     return -1;

    }
    
    tipoCelda *celdaEliminada = c->frente;
    tipoElemento elementoEliminado = c->frente->elemento;
    
    
    c->frente = c->frente->sig;
    if (c->frente == NULL) {
    
    	c->fondo = NULL;
    
    }
    free(celdaEliminada);
    return elementoEliminado;
    
}
