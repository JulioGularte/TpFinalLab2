#ifndef PRACTICASXINGRESO_H_INCLUDED
#define PRACTICASXINGRESO_H_INCLUDED
typedef struct
{
    int nroIngreso;
    int nroPractica;
    char resultado [40];
    int eliminado;
}PracticasXIngreso;
PracticasXIngreso crearPxI(int nroIngreso, int nroPractica);


#endif // PRACTICASXINGRESO_H_INCLUDED
