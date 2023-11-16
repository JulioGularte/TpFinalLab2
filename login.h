#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

typedef struct{
    int dni;
    char apellido_nombre[40];
    char usuario[20];
    char clave[20];
    char perfil [20];
}Empleado;

#endif // LOGIN_H_INCLUDED
