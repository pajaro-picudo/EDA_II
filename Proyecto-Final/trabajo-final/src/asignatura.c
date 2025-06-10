//-----------------------------------------------//
// Ángel de Lorenzo Jerez - 49368491A - Grupo A2 //
//-----------------------------------------------//

#define ASIG 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dispersion.h"
#ifdef ASIG
    #include "../include/asignatura.h"
    typedef tAsignatura tipoReg;
#endif



int funcionHash(tAsignatura *reg, int nCubos) {
    return reg->codigo % nCubos; // Aplicamos módulo
}// Fin función hash


int cmpClave(tAsignatura *reg1, tAsignatura *reg2) {
    return reg1->codigo - reg2->codigo; // Comparar enteros
}// Fin función cmpClave

void mostrarReg(tAsignatura *reg) {
    printf(
        "Código: %-6d | Nombre: %-50s\n"
        "Créditos: T(%.1f) P(%.1f) | Tipo: %c | Cuatrimestre: %c\n"
        "Grupos: T(%d) P(%d)\n",
        reg->codigo, reg->nombre,
        reg->creditosT, reg->creditosP, reg->tipo, reg->cuatrimestre,
        reg->numGrT, reg->numGrP
    );
}// Fin función mostrarReg

int buscar(char *fichero, int codigo) {
    int resultado;
    tPosicion pos;
    FILE *fHash = fopen(fichero, "rb");

    if (!fHash) return -2; // Error de archivo
    
    tAsignatura asignaturaBusqueda = { .codigo = codigo }; // Clave de búsqueda
    
    resultado = busquedaHash(fHash, &asignaturaBusqueda, &pos);
    
    if (resultado == 0) {
        printf("\n--> Asignatura encontrada:\n");
        mostrarReg(&asignaturaBusqueda);
    } else if (resultado == -1) {
        printf("\n--> Asignatura con código %d no encontrada\n", codigo);
    }
    
    fclose(fHash);
    return resultado;
}// Fin función buscar

int modificar(char *fichero, int codigo, float creditosT, float creditosP) {
    tPosicion pos;
    int resultado;
    FILE *fHash = fopen(fichero, "r+b"); // Lectura/escritura

    if (!fHash) return -2;
    
    tAsignatura asignaturaMod = { .codigo = codigo }; // Clave de búsqueda
    
    resultado = busquedaHash(fHash, &asignaturaMod, &pos);
    
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
}// Fin función modificar

int insertarReg(char *fichero, tAsignatura *nuevaAsig) {

    int resultado;
    regConfig regC;
    FILE *fHash = fopen(fichero, "r+b"); // lectura/escritura binaria

    if (!fHash) return -2;

    // Leer la cabecera de configuración
    if (fread(&regC, sizeof(regConfig), 1, fHash) != 1) {
        fclose(fHash);
        return -2;
    }

    resultado = insertar(fHash, nuevaAsig, &regC);

    // Si fue exitosa, actualizar cabecera
    if (resultado == 0) {
        fseek(fHash, 0, SEEK_SET);
        fwrite(&regC, sizeof(regConfig), 1, fHash);
        printf("\n--> Registro añadido correctamente\n");
    }

    fclose(fHash);
    return resultado;
}// Fin función insertarReg
