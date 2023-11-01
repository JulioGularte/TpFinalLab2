#ifndef Paciente_H_INCLUDED
#define Paciente_H_INCLUDED
typedef struct
{
    int nroIngreso;
    char NyA [40];
    int edad;
    int DNI;
    char direccion[30];
    char telefono[15];
    int eliminado;
}Paciente;

#endif // Paciente_H_INCLUDED
