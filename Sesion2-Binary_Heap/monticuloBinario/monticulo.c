#include "monticulo.h"
#include <stdio.h>
#include <stdlib.h>

void iniciaMonticulo (Monticulo *m)
{
  m->tamanno = 0;
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
filtradoAscendente(&m, x.clave);
    


}

void filtradoAscendente(Monticulo *m, int i) {

int hueco = m->tamanno;

while (m->elemento[hueco/2].clave > i)
{
    m->elemento[hueco] = m->elemento[hueco/2];
    hueco = hueco/2;
}
m->elemento[hueco] = i;
}