#ifndef EMPLEADOSLABORATORIO_H_INCLUDED
#define EMPLEADOSLABORATORIO_H_INCLUDED
typedef struct
{
    int dni;
    char NyA[40];
    char usuario[20];
    char clave[20];
    char perfil[20];
}empleados_laboratorio;


void loguear (char archivo[]);
void opciones_de_logueo (int perfil);
int validar_perfil_empleado (char archivo[],char usuario[],char clave[]);  ///retorna 0-1-2-3 o -1 dendinedo tipo de usuario
empleados_laboratorio buscar_empleado_en_archivo (char archivo[],char usuario[],char clave[]);///recibe el archivo de empleados y devuelve si tiene coincidencia
int comparar_perfil (empleados_laboratorio usuario); ///retorna 1-2-3 segun el perfil del usuario

#endif // EMPLEADOSLABORATORIO_H_INCLUDED
