#ifndef Ingreso_H_INCLUDED
#define Ingreso_H_INCLUDED
typedef struct _Ingreso
{
    int NroIngreso;
    char FechaIngreso [25];
    char FechaRetiro [25];
    int DNI;
    int MatriculaPersonalSolicitante;
    int Eliminado;
}Ingreso;

Ingreso cargarIngresoManual(int * nroUltimoIngreso);



#endif // Ingreso_H_INCLUDED
