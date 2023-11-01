#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
typedef struct _Pacientes
{
    char NyA [40];
    int edad;
    int DNI;
    char direccion[30];
    char telefono[15];
    int eliminado;
    _Pacientes *sig;
}Pacientes;


#endif // PACIENTES_H_INCLUDED
