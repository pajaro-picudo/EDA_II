#include "monticulo.h"
#include <stdio.h>
#include <stdlib.h>

void iniciaMonticulo (Monticulo *m)
{
  m->tamanno = 0;
  m->elemento[0].clave = -1;
}

int vacioMonticulo(Monticulo m) {
     return (m.tamanno == 0) ?  1 : 0;
}

int insertar(tipoElemento x, Monticulo *m) {

if (m->tamanno >= MAXIMO) {

    printf ("Error: Monticulo ha alcanzado el tamaño máximo\n");
    return -1;

}
m->tamanno++;
m->elemento[m->tamanno] = x;
filtradoAscendente(m, m->tamanno);
return 0;

}

void filtradoAscendente(Monticulo *m, int i) {

  tipoElemento e = m->elemento[i];

  while(e.clave < m->elemento[i/2].clave){
   m->elemento[i] = m->elemento[i/2];
   i/=2;
 }

 m->elemento[i] = e;
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo){
	if(m->tamanno <= 0) return -1;

	*minimo = m->elemento[1];
	m->elemento[1] = m->elemento[m->tamanno];
	
	m->tamanno--;
	filtradoDescendente(m,1);

	return 0;
}

void filtradoDescendente(Monticulo *m, int i){
  int hijo, finFiltrado;
  tipoElemento hueco = m->elemento[i];
  finFiltrado = 0;

  while(2*i <= m->tamanno && !finFiltrado){
    hijo = 2*i;
    if(hijo+1 <= m->tamanno && m->elemento[hijo+1].clave < m->elemento[hijo].clave)
      hijo++;

    if(hueco.clave > m->elemento[hijo].clave){
      m->elemento[i] = m->elemento[hijo];
      i = hijo;
    }else
      finFiltrado = 1;
  }

  m->elemento[i] = hueco;
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m) {
  if (pos <= 0 || pos > m->tamanno) {
    printf("Error: posición fuera de rango\n");
    return;
} // ¡Esta llave cierra el if!
m->elemento[pos].clave -= cantidad;
filtradoAscendente(m, pos);
}


void incrementarClave(int pos, tipoClave cantidad, Monticulo *m) {
  if (pos <= 0 || pos > m->tamanno) {
      printf("Error: posición fuera de rango\n");
      return;
  } // Llave de cierre del if
  m->elemento[pos].clave += cantidad;
  filtradoDescendente(m, pos);
} // Llave de cierre de la función
int esMonticulo(Monticulo m) {

for (int i = m.tamanno ; i > 1 ; i--) {

    if (m.elemento[i].clave < m.elemento[i/2].clave) {
        printf("Error: No es un montículo\n");
        return 0;
    }
  }
  return 1; 

}
void crearMonticulo(Monticulo *m) {

  int i;
  for (i=m->tamanno/2; i >= 1; i--) {
    filtradoDescendente(m, i);
  }

}

void heapsort(Monticulo *m){
  int tam, i;
  tipoElemento e;

  tam = m->tamanno;

  crearMonticulo(m);

  for(i=1; i<=tam; i++){
    if(eliminarMinimo(m, &e)) fprintf(stderr,"ERROR eliminarMinimo");
    m->elemento[m->tamanno+1] = e; 
  }

  m->tamanno = tam;
}