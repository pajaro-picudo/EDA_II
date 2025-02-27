#include "monticulo.h"
#include <stdio.h>
#include <stdlib.h>

void iniciaMonticulo (Monticulo *m)
{
  m->tamanno = 0;
}
int vacioMonticulo(Monticulo m) {
    return m.tamanno == 0;
}
