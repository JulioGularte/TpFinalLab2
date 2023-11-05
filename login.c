#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EmpleadosLaboratorio.h"
/// define usuario maestro "admin"
#define USUARIO_ADMIN "ADMIN"
#define CLAVE_ADMIN "admin2023"

void loguear (char archivo[])///pide usuario y clave con 3 intentos y manda al swich. (distingue mayusculas)
{
    int perfil;
    int intentos=4;
    char usuario[20];
    char clave[20];
    do{
        printf("\nUsuario: ");
        fflush(stdin);
        gets(usuario);
        printf("Clave: ");
        fflush(stdin);
        gets(clave);
        intentos--;
        perfil=validar_perfil_empleado(archivo,usuario,clave);
        if(perfil==-1)
        {
            system("cls");
            printf("\*La clave o usuario no existen...\nLe quedan %i intentos...",intentos-1);
        }
        printf("\nperfil= %i",perfil);
    }while(intentos!=0 && perfil==-1);
    opciones_de_logueo(perfil);
}
void opciones_de_logueo (int perfil) ///swich para mostrar los distintos menues dependiendo la gerarquia
{
    switch(perfil)
    {
    case 0:
        printf("\n\n\n----opciones usuario maestro----\n\tEn construcion...");
        break;
    case 1:
        break;
    case 2:
        printf("\n\n\n----opciones usuario tecnico----\n\tEn construcion...");
        break;
    case 3:
        break;
    default:
        system("cls");
        printf("\n*ERROR: INTENTOS MAXIMOS ALCANZADOS... \nCERRANDO PROGRAMA...");
    }
}
int validar_perfil_empleado (char archivo[],char usuario[],char clave[])  ///retorna 0-1-2-3 o -1 dendinedo tipo de usuario
{
    empleados_laboratorio aux;
    int encontrado=-1;
    if((0 == strcmp(usuario,USUARIO_ADMIN)) && (0 == strcmp(clave,CLAVE_ADMIN)))
    {
        encontrado=0;///retorna 0 usuario maestro
    }
    else
    {
        aux= buscar_empleado_en_archivo(archivo,usuario,clave);
        encontrado=comparar_perfil(aux); ///retorna 1-2-3 o -1 si no lo encuentra
    }
    return encontrado;
}
empleados_laboratorio buscar_empleado_en_archivo (char archivo[],char usuario[],char clave[])///recibe el archivo de empleados y devuelve si tiene coincidencia
{
    FILE*arch=fopen(archivo,"rb");
    empleados_laboratorio aux;
    empleados_laboratorio encontrado;
    int buscar=-1;
    if (arch)
    {
        while (fread(&aux,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if ((0 == strcmp(usuario,aux.usuario)) && (0 == strcmp(clave,aux.clave)))
            {
                encontrado=aux;
            }
        }
        fclose(arch);
    }
    return encontrado;
}
int comparar_perfil (empleados_laboratorio usuario) ///retorna 1-2-3 segun el perfil del usuario
{
    if(strstr(usuario.perfil,"administrativo"))
    {
        return 1;
    }
    else if(strstr(usuario.perfil,"tecnico"))
    {
        return 2;
    }
    else if(strstr(usuario.perfil,"bioquimico"))
    {
        return 3;
    }
    else
    {
        return -1;/// no se encontro empleado
    }
}

///crear usuario (solo el admin supremo puede cargarlo)
