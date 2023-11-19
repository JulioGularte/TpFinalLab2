#ifndef REGISTROGENERAL_H_INCLUDED
#define REGISTROGENERAL_H_INCLUDED

typedef struct
{
    int nroIngreso;
    char FechaIngreso [25];
    char FechaRetiro [25];
    int DNI;
    int MatriculaPersonalSolicitante;
    int EliminadoIng; ///ingreso eliminado
    char NyA [40];
    int edad;
    char direccion[30];
    char telefono[15];
    int eliminadoPac; ///paciente eliminado
    int nroPractica;
    char resultado [40];

}registro;


#endif // REGISTROGENERAL_H_INCLUDED
