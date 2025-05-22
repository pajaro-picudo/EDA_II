/* alumno.c */
#define ALUM // Para activar las definiciones específicas de alumnos
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dispersion.h"
#ifdef ALUM
    #include "../include/alumno.h"
    typedef tAlumno tipoReg;
#endif



/* Función hash para alumnos (clave: DNI) */
int funcionHash(tAlumno *reg, int nCubos) {
    return atoi(reg->dni) % nCubos; // Convertir DNI a entero y aplicar módulo
}

/* Comparador de claves (DNI) */
int cmpClave(tAlumno *reg1, tAlumno *reg2) {
    return strcmp(reg1->dni, reg2->dni); // Comparar como strings
}

/* Muestra un registro de alumno */
void mostrarReg(tAlumno *reg) {
    printf("DNI: %-9s | Nombre: %-19s | Apellidos: %-19s %-19s | Provincia: %-11s\n",
           reg->dni, reg->nombre, reg->ape1, reg->ape2, reg->provincia);
}

/* Busca un alumno por DNI */
int buscar(char *fichero, char *dni) {
    FILE *fHash = fopen(fichero, "rb");
    if (!fHash) return -2; // Error de archivo
    
    tAlumno alumnoBusqueda;
    strcpy(alumnoBusqueda.dni, dni); // Clave de búsqueda
    
    tPosicion pos;
    int resultado = busquedaHash(fHash, &alumnoBusqueda, &pos);
    
    if (resultado == 0) {
        printf("\n--> Alumno encontrado:\n");
        mostrarReg(&alumnoBusqueda);
    } else if (resultado == -1) {
        printf("\n--> Alumno con DNI %s no encontrado\n", dni);
    }
    
    fclose(fHash);
    return resultado;
}

/* Modifica la provincia de un alumno */
int modificar(char *fichero, char *dni, char *provincia) {
    FILE *fHash = fopen(fichero, "r+b"); // Lectura/escritura
    if (!fHash) return -2;
    
    tAlumno alumnoMod;
    strcpy(alumnoMod.dni, dni); // Clave de búsqueda
    
    tPosicion pos;
    int resultado = busquedaHash(fHash, &alumnoMod, &pos);
    
    if (resultado == 0) {
        // Actualizar provincia
        strncpy(alumnoMod.provincia, provincia, 10);
        alumnoMod.provincia[10] = '\0'; // Asegurar terminación
        
        resultado = modificarReg(fHash, &alumnoMod, &pos);
        if (resultado == 0) {
            printf("\n--> Provincia actualizada correctamente\n");
        }
    }
    
    fclose(fHash);
    return resultado;
}