#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED
typedef struct _Ingresos
{
    int NroIngreso;
    char FechaIngreso [10];
    char FechaRetiro [10];
    int DNI;
    int MatriculaPersonalSolicitante;
    int Eliminado;
    _Ingresos * siguiente;
    _Ingresos * anterior;
    _PracticasXIngresos * practicasIngreso;
}Ingresos;


#endif // INGRESOS_H_INCLUDED
