#ifndef Paciente_H_INCLUDED
#define Paciente_H_INCLUDED
typedef struct
{
    char NyA [50];
    int edad;
    int DNI;
    char direccion[50];
    char telefono[20];
    int eliminado;
}Paciente;
#endif // Paciente_H_INCLUDED
