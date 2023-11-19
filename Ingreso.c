#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include "Ingreso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSA system("pause");
time_t devuelveFechaActual()
{
    // Tiempo actual
    time_t t = time(NULL);
    return t;

}

Ingreso cargarIngresoManual(int * nroUltimoIngreso) ///aca debería enviarme el ultimo numero de ingreso del archivo asi le aumento uno y no se repiten.
{
    Ingreso nuevoIngreso;
    *nroUltimoIngreso=*nroUltimoIngreso+1;
    nuevoIngreso.NroIngreso=*nroUltimoIngreso;

    ///crea y guarda el tiempo actual como string en el la variable fecha de ingreso
    time_t t=time(NULL);
    char fechaHora[25];
    struct tm tiempoLocal = *localtime(&t);
    char *formato = "%d-%m-%Y";
    int bytesEscritos =strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    strcpy(nuevoIngreso.FechaIngreso,fechaHora);

    ///inicia la variable eliminado en 0 por defecto
    nuevoIngreso.Eliminado=0;

    ///ahora hacemos el pedido de los datos faltantes

    puts("Ingrese el DNI del paciente:"); ///falta validar que solo ingresen numeros enteros y positivos
    scanf("%d",&nuevoIngreso.DNI);

    puts("Ingrese la matricula del profesional que solicita el estudio:"); ///falta validar que solo ingresen numeros enteros y positivos
    scanf("%d",&nuevoIngreso.MatriculaPersonalSolicitante);


    puts("Ingrese la fecha estimada de retiro: (dd-mm-aaaa)");///falta validar que la fecha de retiro sea valida
    scanf("%s",nuevoIngreso.FechaRetiro);



    return nuevoIngreso;
}

void imprimirFechaActual(time_t t)
{
    // Tiempo actual

    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];

    char *formato = "%d-%m-%Y";
    // Intentar formatear
    int bytesEscritos =
        strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0)
    {
        // Si no hay error, los bytesEscritos no son 0
        printf("%s", fechaHora);
    }
    else
    {
        printf("Error formateando fecha");
    }

}

void mostrarIngreso(Ingreso ingresoAMostrar)
{
    printf("El numero de ingreso es:..................... %d \n",ingresoAMostrar.NroIngreso);
    printf("El DNI asociado al ingreso es:............... %d \n",ingresoAMostrar.DNI);
    printf("El ingreso tiene valor de eliminado de:...... %d \n",ingresoAMostrar.Eliminado);
    printf("La matricula del personal solicitante es:.... %d \n",ingresoAMostrar.MatriculaPersonalSolicitante);
    printf("La fecha de ingreso es:...................... %s \n",ingresoAMostrar.FechaIngreso);
    printf("La fecha de retiro es:....................... %s \n",ingresoAMostrar.FechaRetiro);
    printf("============================================================== \n");

}

