#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "../include/dispersion.h"
#ifdef ALUM
    tAlumno nuevo;
#endif

#ifdef ASIG
    tAsignatura nueva;
#endif


int main()
{ int nCubo,nCuboDes, posReg, error,bytesDesp;
  tipoReg *reg;
  char dni[9],provincia[11];
  int salir=1,i;

	#ifdef ALUM 
		error = buscar("../datos/alumnosC.hash","8663873");
		if (error)  printf("Error %d en la función bucar\n", error);
		error = modificar("../datos/alumnosC.hash","8663873","Sevilla");
		if (error)  printf("Error %d en la función modificar\n", error);	
		error = buscar("../datos/alumnosC.hash","8663873");

		strcpy(nuevo.dni, "99999999");
		strcpy(nuevo.nombre, "PRUEBA");
		strcpy(nuevo.ape1, "APELLIDO1");
		strcpy(nuevo.ape2, "APELLIDO2");
		strcpy(nuevo.provincia, "BADAJOZ");

		error = insertarReg("../datos/alumnosC.hash", &nuevo);
		if (error) printf("Alumno insertado con éxito\n");
		error = buscar("../datos/alumnosC.hash","99999999");
		if (error)  printf("Error %d en la función bucar\n", error);

		
	#endif  	
	#ifdef ASIG
		error = buscar("../datos/asignaturasC.hash", 101116);
		if (error)  printf("Error %d en la función bucar\n", error);
		error= modificar("../datos/asignaturasC.hash", 101116,4.5, 1.5);
		if (error)  printf("Error %d en la función modificar\n", error);
		error = buscar("../datos/asignaturasC.hash", 101116);
		nueva.codigo = 999999;
        strcpy(nueva.nombre, "Asignatura nueva");
        nueva.curso = '3';
        nueva.creditosT = 1.5;
        nueva.creditosP = 1.5;
        nueva.tipo = 'O';         
        nueva.cuatrimestre = 'P';  
        nueva.numGrT = 1;
        nueva.numGrP = 1;

		error = insertarReg("../datos/asignaturasC.hash", &nueva);
		if (error) printf("Asignatura insertada correctamente\n");
		error = buscar("../datos/asignaturasC.hash", 999999);
		if (error)  printf("Error %d en la función bucar\n", error);



	#endif

}


