#ifndef PRACTICASXINGRESO_H_INCLUDED
#define PRACTICASXINGRESO_H_INCLUDED
typedef struct _PracticasXIngresos
{
    int nroIngreso;
    int nroPractica;
    char resultado [40];
    _PracticasXIngresos * siguiente;
    _PracticasXIngresos * anterior;
}PracticasXIngreso;


#endif // PRACTICASXINGRESO_H_INCLUDED
