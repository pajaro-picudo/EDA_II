/* asignatura.c */
#define ASIG // Para activar definiciones específicas de asignaturas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dispersion.h"
#ifdef ASIG
    #include "../include/asignatura.h"
    typedef tAsignatura tipoReg;
#endif



/* Función hash para asignaturas (clave: código numérico) */
int funcionHash(tAsignatura *reg, int nCubos) {
    return reg->codigo % nCubos; // Código es entero: aplicar módulo directamente
}

/* Comparador de claves (código) */
int cmpClave(tAsignatura *reg1, tAsignatura *reg2) {
    return reg1->codigo - reg2->codigo; // Comparar enteros
}

/* Muestra una asignatura en formato legible */
void mostrarReg(tAsignatura *reg) {
    printf(
        "Código: %-6d | Nombre: %-50s\n"
        "Créditos: T(%.1f) P(%.1f) | Tipo: %c | Cuatrimestre: %c\n"
        "Grupos: T(%d) P(%d)\n",
        reg->codigo, reg->nombre,
        reg->creditosT, reg->creditosP, reg->tipo, reg->cuatrimestre,
        reg->numGrT, reg->numGrP
    );
}

/* Busca una asignatura por código */
int buscar(char *fichero, int codigo) {
    FILE *fHash = fopen(fichero, "rb");
    if (!fHash) return -2; // Error de archivo
    
    tAsignatura asignaturaBusqueda = { .codigo = codigo }; // Clave de búsqueda
    
    tPosicion pos;
    int resultado = busquedaHash(fHash, &asignaturaBusqueda, &pos);
    
    if (resultado == 0) {
        printf("\n--> Asignatura encontrada:\n");
        mostrarReg(&asignaturaBusqueda);
    } else if (resultado == -1) {
        printf("\n--> Asignatura con código %d no encontrada\n", codigo);
    }
    
    fclose(fHash);
    return resultado;
}

/* Modifica los créditos de una asignatura */
int modificar(char *fichero, int codigo, float creditosT, float creditosP) {
    FILE *fHash = fopen(fichero, "r+b"); // Lectura/escritura
    if (!fHash) return -2;
    
    tAsignatura asignaturaMod = { .codigo = codigo }; // Clave de búsqueda
    
    tPosicion pos;
    int resultado = busquedaHash(fHash, &asignaturaMod, &pos);
    
    if (resultado == 0) {
        // Actualizar créditos
        asignaturaMod.creditosT = creditosT;
        asignaturaMod.creditosP = creditosP;
        
        resultado = modificarReg(fHash, &asignaturaMod, &pos);
        if (resultado == 0) {
            printf("\n--> Créditos actualizados correctamente\n");
        }
    }
    
    fclose(fHash);
    return resultado;
}