#define _XOPEN_SOURCE 700
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

Ingreso cargarIngresoManual(int * nroUltimoIngreso, int documentoPaciente) ///aca debería enviarme el ultimo numero de ingreso del archivo asi le aumento uno y no se repiten.
{
    Ingreso nuevoIngreso;
    nuevoIngreso.DNI=documentoPaciente;
    int pacienteExiste=0;
    //pacienteExiste=validarDniPaciente(nuevoIngreso.DNI,arbolPacientes);
    if(pacienteExiste==1)
    {

        *nroUltimoIngreso=*nroUltimoIngreso+1;
        nuevoIngreso.NroIngreso=*nroUltimoIngreso;

        ///crea y guarda el tiempo actual como string en el la variable fecha de ingreso
        time_t t=time(NULL);
        char fecha1[11];
        char fechaRetiro[11];
        struct tm tiempoLocal = *localtime(&t);
        char *formato = "%d/%m/%Y";
        int bytesEscritos =strftime(fecha1, sizeof fecha1, formato, &tiempoLocal);
        strcpy(nuevoIngreso.FechaIngreso,fecha1);

        ///inicia la variable eliminado en 0 por defecto
        nuevoIngreso.Eliminado=0;

        ///ahora hacemos el pedido de los datos faltantes

        puts("Ingrese la matricula del profesional que solicita el estudio:"); ///falta validar que solo ingresen numeros enteros y positivos
        scanf("%d",&nuevoIngreso.MatriculaPersonalSolicitante);

        strcpy(nuevoIngreso.FechaRetiro," ");

        while(nuevoIngreso.FechaRetiro!=" ")
        {
            puts("Ingrese la fecha estimada de retiro: (dd/mm/aaaa)");
            scanf("%s",fechaRetiro);
            int formatoFechaValida;
            int fechaValida;
            formatoFechaValida=validarFormatoFecha(fechaRetiro);
            fechaValida=compararFechas(nuevoIngreso.FechaIngreso,fechaRetiro);
            if (fechaValida==1 && formatoFechaValida==1)
            {
                strcpy(nuevoIngreso.FechaRetiro,fechaRetiro);
            }
            else
            {
                if (fechaValida!=1)
                {
                    printf("%d\n",fechaValida);
                    puts("La fecha de retiro no puede ser anterior a la fecha de ingreso");
                    printf("La fecha de ingreso es %s \n",nuevoIngreso.FechaIngreso);
                }
                else
                {
                    puts("La fecha debe tener un formato dd/mm/aaaa y ser una fecha valida");
                }
            }
        }
        return nuevoIngreso;
    }

}

void imprimirFechaActual(time_t t)
{
    // Tiempo actual

    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fecha1[70];

    char *formato = "%d-%m-%Y";
    // Intentar formatear
    int bytesEscritos =
        strftime(fecha1, sizeof fecha1, formato, &tiempoLocal);
    if (bytesEscritos != 0)
    {
        // Si no hay error, los bytesEscritos no son 0
        printf("%s", fecha1);
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


int validarFormatoFecha(char fecha[])  ///si hay tiempo, validar meses que no tienen 31 dias.
{
    int dia, mes, anio;
    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) != 3)
    {
        return 0; // No se pudieron leer los tres componentes de la fecha
    }

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1900)
    {
        return 0; // Fecha no válida
    }

    return 1; // Formato de fecha válido
}


int compararFechas(const char fecha1[],const char fecha2[])
{
    struct tm tmFecha1 = {0}; // es necesario Inicializa la estructura con valores predeterminados sino la fecha se modifica siempre
    struct tm tmFecha2 = {0};

    sscanf(fecha1, "%d/%d/%d", &tmFecha1.tm_mday, &tmFecha1.tm_mon, &tmFecha1.tm_year);
    sscanf(fecha2, "%d/%d/%d", &tmFecha2.tm_mday, &tmFecha2.tm_mon, &tmFecha2.tm_year);


    tmFecha1.tm_mon -= 1;
    tmFecha2.tm_mon -= 1;

    tmFecha1.tm_year -= 1900;
    tmFecha2.tm_year -= 1900;


    time_t timeFecha1 = mktime(&tmFecha1);
    time_t timeFecha2 = mktime(&tmFecha2);

    printf("Fecha 1: %d/%d/%d\n", tmFecha1.tm_mday, tmFecha1.tm_mon + 1, tmFecha1.tm_year + 1900);
    printf("Fecha 2: %d/%d/%d\n", tmFecha2.tm_mday, tmFecha2.tm_mon + 1, tmFecha2.tm_year + 1900);

    return timeFecha1 < timeFecha2 ? 1 : 0; // si la fecha 2 (la de retiro) es mayor a la de ingreso retorna 1 y si no, 0

}
int validarDniPaciente(int nroDni, nodoArbolPaciente * arbolDePacientes)
{
    ///codigo para cuando tengamos el arbol
    /*nodoArbolPaciente * aux=arbolDePacientes;
    int flag=0;

    if(aux->paciente.DNI==nroDni)
    {
        return 1;
    }
    else if(flag==0)
    {
        flag=validarDniPaciente(nroDni,aux->der);
        flag=validarDniPaciente(nroDni,aux->izq);
    }
    return flag;*/

}

int contarIngresosEnArchivo ()
{
    FILE * buff=fopen(archivoIngresos, "rb");
    int ingresos=0;
    if (buff)
    {
        Ingreso rg;
        while (fread(&rg, sizeof(Ingreso), 1, buff)>0)
        {
            ingresos++;
        }
        fclose(buff);
    }
    return ingresos;
}
