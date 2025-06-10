//-----------------------------------------------//
// Ángel de Lorenzo Jerez - 49368491A - Grupo A2 //
//-----------------------------------------------//

#define ALUM 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dispersion.h"
#ifdef ALUM
    #include "../include/alumno.h"
    typedef tAlumno tipoReg;
#endif

int funcionHash(tAlumno *reg, int nCubos) {
    return atoi(reg->dni) % nCubos; // Convertir DNI a entero y aplicar módulo
}// Fin función hash


int cmpClave(tAlumno *reg1, tAlumno *reg2) {
    return strcmp(reg1->dni, reg2->dni); // Comparar como strings
}// Fin función cmpClave


void mostrarReg(tAlumno *reg) {
    printf("DNI: %-9s | Nombre: %-19s | Apellidos: %-19s %-19s | Provincia: %-11s\n",
           reg->dni, reg->nombre, reg->ape1, reg->ape2, reg->provincia);
}// Fin función mostrarReg

int buscar(char *fichero, char *dni) {
    tPosicion pos;
    tAlumno alumnoBusqueda;
    int resultado;
    
    FILE *fHash = fopen(fichero, "rb");
    
    if (!fHash) return -2; // Error de archivo
    
    
    strcpy(alumnoBusqueda.dni, dni); // Clave de búsqueda
    
    
    resultado = busquedaHash(fHash, &alumnoBusqueda, &pos);
    
    if (resultado == 0) {
        printf("\n--> Alumno encontrado:\n");
        mostrarReg(&alumnoBusqueda);
    } else if (resultado == -1) {
        printf("\n--> Alumno con DNI %s no encontrado\n", dni);
    }
    
    fclose(fHash);
    return resultado;
}

int modificar(char *fichero, char *dni, char *provincia) {
    tAlumno alumnoMod;
    int resultado;
    tPosicion pos;
    
    FILE *fHash = fopen(fichero, "r+b"); // Lectura/escritura
    
    if (!fHash) return -2;
    
    strcpy(alumnoMod.dni, dni); // Clave de búsqueda
    
    
    resultado = busquedaHash(fHash, &alumnoMod, &pos);
    
    if (resultado == 0) {
        
        strncpy(alumnoMod.provincia, provincia, 10); // Actualizar provincia
        alumnoMod.provincia[10] = '\0'; // Asegurar terminación
        
        resultado = modificarReg(fHash, &alumnoMod, &pos);
        if (resultado == 0) {
            printf("\n--> Provincia actualizada correctamente\n");
        }
    }
    
    fclose(fHash);
    return resultado;
}

int insertarReg(char *fichero, tAlumno *nuevoAlumno) {
    regConfig regC;
    
    FILE *fHash = fopen(fichero, "r+b"); // Abrimos para lectura/escritura binaria
    
    if (!fHash) return -2;

    // Leer configuración
    if (fread(&regC, sizeof(regConfig), 1, fHash) != 1) {
        fclose(fHash);
        return -2;
    }

    int resultado = insertar(fHash, nuevoAlumno, &regC); 

    // Si fue exitosa, escribir config actualizada
    if (resultado == 0) {
        fseek(fHash, 0, SEEK_SET);
        fwrite(&regC, sizeof(regConfig), 1, fHash);
        printf("\n--> Registro añadido correctamente\n");
    }

    fclose(fHash);
    return resultado;
}
