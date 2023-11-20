#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include "Ingreso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSA system("pause");
#include "registroGeneral.h"



/*int numerosDocumentos[] =
{
    45123987, 20145678, 30321789, 15109988, 40234567, 50123456, 20167890,
    35123456, 10345678, 10456789, 30567890, 30456789, 45234567, 30234567,
    10234567, 45123456, 30435678, 10356789, 10123456, 40167890, 50321789,
    30145678, 50234567, 40123456, 10245678
};

int edades []
{
    11, 65, 42, 70, 22, 5, 68, 29, 68, 67, 41, 42, 17, 46, 70, 13, 43,
    69, 71, 24, 5, 37, 50, 19, 68
}

char * fechaIngreso[]
{
    "01-06-2023", "04-06-2023", "06-06-2023", "09-06-2023", "11-06-2023", "14-06-2023",
    "17-06-2023", "19-06-2023", "22-06-2023", "24-06-2023", "27-06-2023", "30-06-2023",
    "03-07-2023", "06-07-2023", "08-07-2023", "11-07-2023", "13-07-2023", "16-07-2023",
    "19-07-2023", "21-07-2023", "24-07-2023", "26-07-2023", "29-07-2023", "01-08-2023"
}
char * fechaRetiro[]
{
    "15-06-2023", "04-07-2023", "06-07-2023", "09-07-2023", "11-07-2023", "14-07-2023",
    "17-07-2023", "19-07-2023", "22-07-2023", "24-07-2023", "27-07-2023", "30-07-2023",
    "03-08-2023", "06-08-2023", "08-08-2023", "11-08-2023", "13-08-2023", "16-08-2023",
    "19-08-2023", "21-08-2023", "24-08-2023", "26-08-2023", "29-08-2023", "01-09-2023"
}

char * direccion[] =
{
    "San Martin 123", "Rivadavia 456", "Belgrano 789", "9 de Julio 1011", "Sarmiento 1213",
    "Alsina 1415", "Pueyrredon 1617", "Mitre 1819", "Urquiza 2021", "Independencia 2223",
    "San Juan 2425", "Lavalle 2627", "Balcarce 2829", "Santa Fe 3031", "Alem 3233",
    "Sanchez de Bustamante 3435", "Cordoba 3637", "Boedo 3839", "Jujuy 4041", "Paraguay 4243",
    "Corrientes 4445", "Tucuman 4647", "Junin 4849", "Suipacha 5051", "Pellegrini 5253"
};

char * telefono[] =
{
    "154567890", "155789012", "156123456", "154234567", "156456789",
    "155678901", "154789012", "156890123", "155901234", "156123456",
    "155234567", "154345678", "156567890", "154678901", "155789012",
    "156890123", "154901234", "155123456", "156234567", "154345678",
    "155456789", "156567890", "154678901", "155789012"
}

char resultado [40];
int Eliminado; ///ingreso eliminado
int nroPractica;
*/

void generarNuevoArchiPaciente(char archivoPacientes[])
{


    char* nombresApellidos[] =
    {
        "Juan Perez", "Ana Rodriguez", "Pedro Gomez", "Maria Lopez", "Luis Martinez",
        "Laura Sanchez", "Carlos Herrera", "Sofia Castro", "Miguel Ramirez", "Elena Torres",
        "Francisco Diaz", "Isabel Fernandez", "Jose Garcia", "Carmen Jimenez", "Antonio Ruiz",
        "Raquel Vargas", "Javier Moreno", "Patricia Medina", "Roberto Morales", "Lorena Navarro",
        "Alejandro Castro", "Beatriz Ortega", "Manuel Herrera", "Silvia Guzman", "Roberto Carlos"
    };



    int numerosDocumentos[] =
    {
        45123987, 20145678, 30321789, 15109988, 40234567, 50123456, 20167890,
        35123456, 10345678, 10456789, 30567890, 30456789, 45234567, 30234567,
        10234567, 45123456, 30435678, 10356789, 10123456, 40167890, 50321789,
        30145678, 50234567, 40123456, 10245678,
    };

    int edades [] =
    {
        11, 65, 42, 70, 22, 5, 68, 29, 68, 67, 41, 42, 17, 46, 70, 13, 43,
        69, 71, 24, 5, 37, 50, 19, 68
    };

    char * fechaIngreso[] =
    {
        "01-06-2023", "04-06-2023", "06-06-2023", "09-06-2023", "11-06-2023", "14-06-2023",
        "17-06-2023", "19-06-2023", "22-06-2023", "24-06-2023", "27-06-2023", "30-06-2023",
        "03-07-2023", "06-07-2023", "08-07-2023", "11-07-2023", "13-07-2023", "16-07-2023",
        "19-07-2023", "21-07-2023", "24-07-2023", "26-07-2023", "29-07-2023", "01-08-2023", "02-09-2023"
    };
    char * fechaRetiro[] =
    {
        "15-06-2023", "04-07-2023", "06-07-2023", "09-07-2023", "11-07-2023", "14-07-2023",
        "17-07-2023", "19-07-2023", "22-07-2023", "24-07-2023", "27-07-2023", "30-07-2023",
        "03-08-2023", "06-08-2023", "08-08-2023", "11-08-2023", "13-08-2023", "16-08-2023",
        "19-08-2023", "21-08-2023", "24-08-2023", "26-08-2023", "29-08-2023", "01-09-2023", "15-09-2023"
    };

    char * direccion[] =
    {
        "San Martin 123", "Rivadavia 456", "Belgrano 789", "9 de Julio 1011", "Sarmiento 1213",
        "Alsina 1415", "Pueyrredon 1617", "Mitre 1819", "Urquiza 2021", "Independencia 2223",
        "San Juan 2425", "Lavalle 2627", "Balcarce 2829", "Santa Fe 3031", "Alem 3233",
        "Sanchez de Bustamante 3435", "Cordoba 3637", "Boedo 3839", "Jujuy 4041", "Paraguay 4243",
        "Corrientes 4445", "Tucuman 4647", "Junin 4849", "Suipacha 5051", "Pellegrini 5253"
    };

    char * telefonos[] =
    {
        "154567890", "155789012", "156123456", "154234567", "156456789",
        "155678901", "154789012", "156890123", "155901234", "156123456",
        "155234567", "154345678", "156567890", "154678901", "155789012",
        "156890123", "154901234", "155123456", "156234567", "154345678",
        "155456789", "156567890", "154678901", "155789012", "155789012"
    };


    FILE* archi=fopen(archivoPacientes,"wb");

    if(archi!=NULL)
    {


        for (int i=0; i<25; i++)
        {

            Paciente nuevoPaciente;

            nuevoPaciente.DNI=numerosDocumentos[i];///
            nuevoPaciente.eliminado=0;
            strcpy(nuevoPaciente.NyA,nombresApellidos[i]);
            nuevoPaciente.edad=edades[i];///
            strcpy(nuevoPaciente.direccion,direccion[i]);///
            strcpy(nuevoPaciente.telefono,telefonos[i]);
            fwrite(&nuevoPaciente,sizeof(Paciente),1,archi);
        }
    }

    fclose(archi);
}

void generarNuevoArchiIngreso(char archivoIngreso[])
{


    char* nombresApellidos[] =
    {
        "Juan Perez", "Ana Rodriguez", "Pedro Gomez", "Maria Lopez", "Luis Martinez",
        "Laura Sanchez", "Carlos Herrera", "Sofia Castro", "Miguel Ramirez", "Elena Torres",
        "Francisco Diaz", "Isabel Fernandez", "Jose Garcia", "Carmen Jimenez", "Antonio Ruiz",
        "Raquel Vargas", "Javier Moreno", "Patricia Medina", "Roberto Morales", "Lorena Navarro",
        "Alejandro Castro", "Beatriz Ortega", "Manuel Herrera", "Silvia Guzman", "Roberto Carlos"
    };



    int numerosDocumentos[] =
    {
        45123987, 20145678, 30321789, 15109988, 40234567, 50123456, 20167890,
        35123456, 10345678, 10456789, 30567890, 30456789, 45234567, 30234567,
        10234567, 45123456, 30435678, 10356789, 10123456, 40167890, 50321789,
        30145678, 50234567, 40123456, 10245678,
    };

    int edades [] =
    {
        11, 65, 42, 70, 22, 5, 68, 29, 68, 67, 41, 42, 17, 46, 70, 13, 43,
        69, 71, 24, 5, 37, 50, 19, 68
    };

    char * fechaIngreso[] =
    {
        "01-06-2023", "04-06-2023", "06-06-2023", "09-06-2023", "11-06-2023", "14-06-2023",
        "17-06-2023", "19-06-2023", "22-06-2023", "24-06-2023", "27-06-2023", "30-06-2023",
        "03-07-2023", "06-07-2023", "08-07-2023", "11-07-2023", "13-07-2023", "16-07-2023",
        "19-07-2023", "21-07-2023", "24-07-2023", "26-07-2023", "29-07-2023", "01-08-2023", "02-09-2023"
    };
    char * fechaRetiro[] =
    {
        "15-06-2023", "04-07-2023", "06-07-2023", "09-07-2023", "11-07-2023", "14-07-2023",
        "17-07-2023", "19-07-2023", "22-07-2023", "24-07-2023", "27-07-2023", "30-07-2023",
        "03-08-2023", "06-08-2023", "08-08-2023", "11-08-2023", "13-08-2023", "16-08-2023",
        "19-08-2023", "21-08-2023", "24-08-2023", "26-08-2023", "29-08-2023", "01-09-2023", "15-09-2023"
    };

    char * direccion[] =
    {
        "San Martin 123", "Rivadavia 456", "Belgrano 789", "9 de Julio 1011", "Sarmiento 1213",
        "Alsina 1415", "Pueyrredon 1617", "Mitre 1819", "Urquiza 2021", "Independencia 2223",
        "San Juan 2425", "Lavalle 2627", "Balcarce 2829", "Santa Fe 3031", "Alem 3233",
        "Sanchez de Bustamante 3435", "Cordoba 3637", "Boedo 3839", "Jujuy 4041", "Paraguay 4243",
        "Corrientes 4445", "Tucuman 4647", "Junin 4849", "Suipacha 5051", "Pellegrini 5253"
    };

    char * telefonos[] =
    {
        "154567890", "155789012", "156123456", "154234567", "156456789",
        "155678901", "154789012", "156890123", "155901234", "156123456",
        "155234567", "154345678", "156567890", "154678901", "155789012",
        "156890123", "154901234", "155123456", "156234567", "154345678",
        "155456789", "156567890", "154678901", "155789012", "155789012"
    };


    FILE* archi=fopen(archivoIngreso,"wb");

    if(archi!=NULL)
    {


        for (int i=0; i<100; i++)
        {
            int random1= rand () % 25;
            int random2= rand () % 25;

            Ingreso nuevoIngreso;
            nuevoIngreso.MatriculaPersonalSolicitante=111;
            nuevoIngreso.NroIngreso=i;
            nuevoIngreso.DNI=numerosDocumentos[random1];///
            nuevoIngreso.Eliminado=0;
            strcpy(nuevoIngreso.FechaIngreso,fechaIngreso[random2]);
            strcpy(nuevoIngreso.FechaRetiro,fechaRetiro[random2]);
            ///nuevoIngreso.edad=edades[i];///
            ///strcpy(nuevoIngreso.direccion,direccion[i]);///
            ///strcpy(nuevoIngreso.telefono,telefonos[i]);
            fwrite(&nuevoIngreso,sizeof(Ingreso),1,archi);
        }
    }

    fclose(archi);
}

void generarNuevoArchiPxI(char archivoPxI[])
{
    FILE* archi=fopen(archivoPxI,"wb");

    if(archi!=NULL)
    {


        for (int i=0; i<300; i++)
        {
            int random1= rand () % 100;
            int random2= rand () % 100;

            PracticasXIngreso nuevoPxI;
            nuevoPxI.nroIngreso=random1;
            nuevoPxI.eliminado=0;
            nuevoPxI.nroPractica=random2;
            strcpy(nuevoPxI.resultado,"A completar");
            fwrite(&nuevoPxI,sizeof(PracticasXIngreso),1,archi);
        }
    }

    fclose(archi);
}

void mostrarArchivoPaciente(char archivoPacientes[])
{
    FILE * archi=fopen(archivoPacientes, "rb");
    if (archi)
    {
        Paciente nuevoRegistro;
        while(fread(&nuevoRegistro,sizeof(Paciente),1,archi)>0)
        {
            ///printf("Numero de ingreso:.................................. %d\n", nuevoRegistro.nroIngreso);
            ///printf("Fecha de Ingreso:................................... %s\n",nuevoRegistro.FechaIngreso);
            ///printf("Fecha de Retiro:.................................... %s\n",nuevoRegistro.FechaRetiro);
            printf("Numero de DNI:...................................... %d\n", nuevoRegistro.DNI);
            ///printf("Numero de Matricula del Personal Solicitante:....... %d\n", nuevoRegistro.MatriculaPersonalSolicitante);
            ///printf("Ingreso eliminado:.................................. %d\n", nuevoRegistro.EliminadoIng);
            printf("Nombre y apellido:.................................. %s\n",nuevoRegistro.NyA);
            printf("Edad:............................................... %d\n", nuevoRegistro.edad);
            printf("Direccion:.......................................... %s\n",nuevoRegistro.direccion);
            printf("Telefono:........................................... %s\n",nuevoRegistro.telefono);
            printf("Paciente eliminado:................................. %d\n", nuevoRegistro.eliminado);
            ///printf("Numero de practica:................................. %d\n", nuevoRegistro.nroPractica);
            ///printf("Resultado:.......................................... %s\n",nuevoRegistro.resultado);
            puts("===========================================================================");

        }

    }
    fclose(archi);
}


void mostrarArchivoIngreso(char archivoIngreso[])
{
    FILE * archi=fopen(archivoIngreso, "rb");
    if (archi)
    {
        Ingreso nuevoRegistro;
        while(fread(&nuevoRegistro,sizeof(Ingreso),1,archi)>0)
        {
            printf("Numero de ingreso:.................................. %d\n", nuevoRegistro.NroIngreso);
            printf("Fecha de Ingreso:................................... %s\n",nuevoRegistro.FechaIngreso);
            printf("Fecha de Retiro:.................................... %s\n",nuevoRegistro.FechaRetiro);
            printf("Numero de DNI:...................................... %d\n", nuevoRegistro.DNI);
            printf("Numero de Matricula del Personal Solicitante:....... %d\n", nuevoRegistro.MatriculaPersonalSolicitante);
            printf("Ingreso eliminado:.................................. %d\n", nuevoRegistro.Eliminado);
            ///printf("Nombre y apellido:.................................. %s\n",nuevoRegistro.NyA);
            ///printf("Edad:............................................... %d\n", nuevoRegistro.edad);
            ///printf("Direccion:.......................................... %s\n",nuevoRegistro.direccion);
            ///printf("Telefono:........................................... %s\n",nuevoRegistro.telefono);
            ///printf("Paciente eliminado:................................. %d\n", nuevoRegistro.eliminado);
            ///printf("Numero de practica:................................. %d\n", nuevoRegistro.nroPractica);
            ///printf("Resultado:.......................................... %s\n",nuevoRegistro.resultado);
            puts("===========================================================================");

        }

    }
    fclose(archi);
}

void mostrarArchivoPxI(char archivoPxI[])
{
    FILE * archi=fopen(archivoPxI, "rb");
    if (archi)
    {
        PracticasXIngreso nuevoRegistro;
        while(fread(&nuevoRegistro,sizeof(PracticasXIngreso),1,archi)>0)
        {
            printf("Numero de ingreso:.................................. %d\n", nuevoRegistro.nroIngreso);
            ///printf("Fecha de Ingreso:................................... %s\n",nuevoRegistro.FechaIngreso);
            ///printf("Fecha de Retiro:.................................... %s\n",nuevoRegistro.FechaRetiro);
            ///printf("Numero de DNI:...................................... %d\n", nuevoRegistro.DNI);
            ///printf("Numero de Matricula del Personal Solicitante:....... %d\n", nuevoRegistro.MatriculaPersonalSolicitante);
            printf("Practica eliminada:................................. %d\n", nuevoRegistro.eliminado);
            ///printf("Nombre y apellido:.................................. %s\n",nuevoRegistro.NyA);
            ///printf("Edad:............................................... %d\n", nuevoRegistro.edad);
            ///printf("Direccion:.......................................... %s\n",nuevoRegistro.direccion);
            ///printf("Telefono:........................................... %s\n",nuevoRegistro.telefono);
            ///printf("Paciente eliminado:................................. %d\n", nuevoRegistro.eliminado);
            printf("Numero de practica:................................. %d\n", nuevoRegistro.nroPractica);
            printf("Resultado:.......................................... %s\n",nuevoRegistro.resultado);
            puts("===========================================================================");

        }

    }
    fclose(archi);
}
