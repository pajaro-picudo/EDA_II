//-----------------------------------------------//
// Ángel de Lorenzo Jerez - 49368491A - Grupo A2 //
//-----------------------------------------------//

#include "../include/dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Lee el contenido del fichero hash organizado mediante el método de DISPERSIÓN según los criterios
// especificados en la práctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta función permite visualizar el método de DISPERSIÓN
int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  regConfig regC;
  int j,nCubo=0,densidadOcupacion;
  
   if ((f = fopen(fichHash,"rb"))==NULL) return -2;
   fread(&regC,sizeof(regConfig),1,f);
   fread(&cubo,sizeof(cubo),1,f); 
   while (!feof(f)){
	for (j=0;j<C;j++) {
        	if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",nCubo,cubo.numRegAsignados);
        	else 	if ((j==1) && cubo.desbordado) printf("DESBORDADO\t\t");
        		else printf("\t\t\t");
		if (j < cubo.numRegAsignados) 
			mostrarReg(&(cubo.reg[j]));
	    	else printf ("\n");
        	}
		nCubo++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   printf("ORGANIZACIÓN MÉTODO DISPERSIÓN:\n\t %d CUBOS y %d CUBOS DESBORDE con capacidad %d\n",
   		regC.nCubos,regC.nCubosDes, C);   
   printf("Cubo de Desborde Actual: %d\n", regC.nCuboDesAct);  

   printf("\t Contiene %d registros de los cuales se han desbordado %d:\n",regC.numReg,regC.numRegDes);
   	
   densidadOcupacion = 100*regC.numReg/((regC.nCubos+regC.nCubosDes)*C);
   printf("Densidad ACTUAL de ocupación: %d \n\t(MÍNIMA permitida %f  MÁXIMA permitida %f)\n",
   				densidadOcupacion,regC.densidadMin,regC.densidadMax);
   
   
   if (densidadOcupacion>regC.densidadMax) {
   	printf("No se respeta la densidad máxima de ocupacion\n");
   }	

   if (densidadOcupacion<regC.densidadMin) {
   	printf("No se respeta la densidad mínima de ocupacion\n");
   }	
return 0;	
}//Fin función leeHash


int creaHvacio(char *fichHash,regConfig *reg) {
// Verificar parámetros mínimos según el enunciado
if (reg->nCubos < 8 || reg->nCubosDes < 4) {
   return -5; // Parámetros inválidos
}

// Abrir el archivo en modo escritura binaria (crea o trunca el archivo)
FILE *fHash = fopen(fichHash, "wb");
if (fHash == NULL) {
    return -2; // Error al abrir el archivo
}

// Inicializar valores del registro de configuración
reg->numReg = 0;          // Total de registros (inicialmente 0)
reg->numRegDes = 0;       // Registros desbordados (inicialmente 0)
reg->nCuboDesAct = reg->nCubos; // Primer cubo desborde disponible

// Escribir el registro de configuración al inicio del archivo
if (fwrite(reg, sizeof(regConfig), 1, fHash) != 1) {
    fclose(fHash);
    return -2; // Error de escritura
}

// Crear e inicializar cubos primarios
tipoCubo cuboVacio = {
    .numRegAsignados = 0,
    .desbordado = 0
    // Los registros no necesitan inicialización explícita
};

for (int i = 0; i < reg->nCubos; i++) {
    if (fwrite(&cuboVacio, sizeof(tipoCubo), 1, fHash) != 1) {
        fclose(fHash);
        return -2;
    }
}

// Crear e inicializar cubos de desborde
for (int i = 0; i < reg->nCubosDes; i++) {
    if (fwrite(&cuboVacio, sizeof(tipoCubo), 1, fHash) != 1) {
        fclose(fHash);
        return -2;
    }
}

// Cerrar el archivo y retornar éxito
fclose(fHash);
return 0;


}// Fin función creaHvacio



int insertar(FILE *fHash, tipoReg *reg, regConfig *regC) {
// Calcular cubo destino usando la función hash
int cuboDestino = funcionHash(reg, regC->nCubos);
int resultado = 0;
tipoCubo cubo;
    
// Posicionarnos en el cubo primario correspondiente
long posicionCubo = sizeof(regConfig) + cuboDestino * sizeof(tipoCubo);
if (fseek(fHash, posicionCubo, SEEK_SET) != 0) {
    return -2; // Error de posicionamiento
}

// Leer el cubo primario
if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
    return -2; // Error de lectura
}

// Verificar si hay espacio en el cubo primario
if (cubo.numRegAsignados < C) {
    // Insertar en cubo primario
    cubo.reg[cubo.numRegAsignados] = *reg;
    cubo.numRegAsignados++;
    
    // Escribir el cubo actualizado
    if (fseek(fHash, posicionCubo, SEEK_SET) != 0 ||
        fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
        return -2;
    }
    
    regC->numReg++; // Actualizar contador total
} else {
    // Manejar desborde
    resultado = desborde(fHash, reg, regC);
    if (resultado != 0) {
        return resultado; // Propagamos el error
    }
    
    // Si el cubo no estaba marcado como desbordado, marcarlo
    if (cubo.desbordado == 0) {
        cubo.desbordado = 1;
        if (fseek(fHash, posicionCubo, SEEK_SET) != 0 ||
            fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
            return -2;
        }
    }
}

// Actualizar el registro de configuración en archivo
if (fseek(fHash, 0, SEEK_SET) != 0 ||
    fwrite(regC, sizeof(regConfig), 1, fHash) != 1) {
    return -2;
}

return 0;

}// Fin función insertar



int creaHash(char *fichEntrada,char *fichHash, regConfig *regC) {

// Crear el archivo hash vacío
int resultado = creaHvacio(fichHash, regC);
if (resultado != 0) {
    return resultado; // Propagamos el error (-2)
}

// Abrir el archivo de entrada
FILE *fEntrada = fopen(fichEntrada, "rb");
if (fEntrada == NULL) {
    return -1; // Error en archivo de entrada
}

// Abrir el archivo hash para lectura/escritura
FILE *fHash = fopen(fichHash, "r+b");
if (fHash == NULL) {
    fclose(fEntrada);
    return -2; // Error en archivo hash
}

// Procesar todos los registros del archivo de entrada
tipoReg registro;
int error = 0;

while (fread(&registro, sizeof(tipoReg), 1, fEntrada) == 1) {
    resultado = insertar(fHash, &registro, regC);
    
    if (resultado != 0) {
        error = resultado;
        break;
    }

    // Verificar densidad durante el proceso (opcional)
    float densidadActual = (float)regC->numReg / (regC->nCubos * C);
    if (densidadActual > regC->densidadMax) {
        error = -3;
        break;
    }
}

// Verificación final de densidad
if (error == 0) {
    float densidadFinal = (float)regC->numReg / (regC->nCubos * C);
    if (densidadFinal > regC->densidadMax) {
        error = -3;
    } else if (densidadFinal < regC->densidadMin) {
        error = -4;
    }
}

// Escribir configuración final (incluso si hubo error)
fseek(fHash, 0, SEEK_SET);
fwrite(regC, sizeof(regConfig), 1, fHash);

// Cerrar archivos y retornar
fclose(fEntrada);
fclose(fHash);

return error;

}// Fin función creaHash



int desborde(FILE *fHash,tipoReg *reg, regConfig *regC) {

// Posicionarnos en el cubo de desborde actual
long posDesborde = sizeof(regConfig) + (regC->nCubos + regC->nCuboDesAct - regC->nCubos) * sizeof(tipoCubo);
tipoCubo cuboDes;

if (fseek(fHash, posDesborde, SEEK_SET) != 0) {
    return -2; // Error de posicionamiento
}

// Leer el cubo de desborde actual
if (fread(&cuboDes, sizeof(tipoCubo), 1, fHash) != 1) {
    return -2; // Error de lectura
}

// Insertar el registro en el cubo de desborde
if (cuboDes.numRegAsignados >= C) {
    // Esto no debería ocurrir porque nCuboDesAct apunta a cubo con espacio
    return -5; // Error interno
}

cuboDes.reg[cuboDes.numRegAsignados] = *reg;
cuboDes.numRegAsignados++;

// Escribir el cubo de desborde actualizado
if (fseek(fHash, posDesborde, SEEK_SET) != 0 ||
    fwrite(&cuboDes, sizeof(tipoCubo), 1, fHash) != 1) {
    return -2;
}

// Actualizar contadores globales
regC->numReg++;
regC->numRegDes++;

// Verificar si hemos llenado este cubo de desborde
if (cuboDes.numRegAsignados == C) {
    regC->nCuboDesAct++;

    // Comprobar si necesitamos añadir nuevo cubo de desborde
    if (regC->nCuboDesAct >= regC->nCubos + regC->nCubosDes) {
        // Crear nuevo cubo de desborde
        tipoCubo nuevoCubo = {0}; // Inicializado vacío
        
        if (fseek(fHash, 0, SEEK_END) != 0 ||
            fwrite(&nuevoCubo, sizeof(tipoCubo), 1, fHash) != 1) {
            return -2;
        }
        
        regC->nCubosDes++; // Incrementar contador de cubos de desborde
    }
}

return 0;


}// Fin función desborde


int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion) {

// Obtener registro de configuración
regConfig regC;
int cuboPrimario;
long posCuboPrimario;
tipoCubo cubo;

if (fseek(fHash, 0, SEEK_SET) != 0 || 
    fread(&regC, sizeof(regConfig), 1, fHash) != 1) {
    return -2; // Error de lectura de cabecera
}

// Calcular cubo primario con función hash
cuboPrimario = funcionHash(reg, regC.nCubos);
posicion->cubo = cuboPrimario;
posicion->cuboDes = -1; // Por defecto, no en desborde

// Posicionarnos y leer el cubo primario
posCuboPrimario = sizeof(regConfig) + cuboPrimario * sizeof(tipoCubo);
if (fseek(fHash, posCuboPrimario, SEEK_SET) != 0) {
    return -2;
}

if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
    return -2;
}

// Buscar en cubo primario
for (int i = 0; i < cubo.numRegAsignados; i++) {
    if (cmpClave(&cubo.reg[i], reg) == 0) {
        posicion->posReg = i;
        *reg = cubo.reg[i]; // Devolver registro completo
        return 0; // Encontrado en cubo primario
    }
}// Fin búsqueda en cubo primario

// Si no está y el cubo tiene desbordes, buscar en área de desborde
if (cubo.desbordado == 1) {
    // Buscar en todos los cubos de desborde
    for (int cuboDesNum = 0; cuboDesNum < regC.nCubosDes; cuboDesNum++) {
        long posCuboDes = sizeof(regConfig) + (regC.nCubos + cuboDesNum) * sizeof(tipoCubo);
        
        if (fseek(fHash, posCuboDes, SEEK_SET) != 0) {
            return -2;
        }

        if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
            return -2;
        }

        // Buscar en el cubo de desborde actual
        for (int i = 0; i < cubo.numRegAsignados; i++) {
            if (cmpClave(&cubo.reg[i], reg) == 0) {
                posicion->posReg = i;
                posicion->cuboDes = cuboDesNum;
                *reg = cubo.reg[i]; // Devolver registro completo
                return 0; // Encontrado en desborde
            }
        }
    }
}

//Registro no encontrado
return -1;


}// Fin función busquedaHash


int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion) {

 long posicionRegistro;
    regConfig regC;

    // Leer configuración para saber nCubos
    if (fseek(fHash, 0, SEEK_SET) != 0 || 
        fread(&regC, sizeof(regConfig), 1, fHash) != 1) {
        return -2;
    }

    // Calcular posición exacta del registro
    if (posicion->cuboDes == -1) {
        // Registro está en cubo primario
        posicionRegistro = sizeof(regConfig) + 
                           posicion->cubo * sizeof(tipoCubo) + 
                           posicion->posReg * sizeof(tipoReg);
    } else {
        // Registro está en cubo de desborde
        posicionRegistro = sizeof(regConfig) + 
                        regC.nCubos * sizeof(tipoCubo) + 
                        posicion->cuboDes * sizeof(tipoCubo) + 
                        posicion->posReg * sizeof(tipoReg);
    }

    // 3. Posicionarse y sobrescribir el registro
    if (fseek(fHash, posicionRegistro, SEEK_SET) != 0 ||
        fwrite(reg, sizeof(tipoReg), 1, fHash) != 1) {
        return -2;
    }

    return 0; // Modificación exitosa
}// Fin función modificarReg
