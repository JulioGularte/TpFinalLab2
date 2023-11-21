#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "EmpleadosLaboratorio.h"
#include "NodoPractica.h"
#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
/// define usuario maestro "admin"
#define USUARIO_ADMIN "ADMIN"
#define CLAVE_ADMIN "admin2023"
///===============================================================================================================funciones-logueo
int loguear (char archivo[])///pide usuario y clave con 3 intentos y manda al swich. (distingue mayusculas)
{
    int perfil;
    int intentos=4;
    char usuario[20];
    char clave[20];
    printf("\t -- Hospital HP --\n");
    do
    {
        printf("\n\tUsuario: ");
        fflush(stdin);
        gets(usuario);
        printf("\tClave: ");
        fflush(stdin);
        gets(clave);
        intentos--;
        perfil=validar_perfil_empleado(archivo,usuario,clave);
        if(perfil==-1)
        {
            system("cls");
            printf("\t -- Hospital HP --\n\tLa clave o usuario no existen...\n/tLe quedan %i intentos...",intentos-1);
        }
    }
    while(intentos!=0 && perfil==-1);
    menu_opciones_gerarquia(perfil,archivo);
    return perfil;/// retorna el int correspondiente a la gerarquia para los distintos menues
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
        aux= comprobar_coincidencia(archivo,usuario,clave);
        encontrado=comparar_perfil(aux); ///retorna 1-2-3 si no encuentra
    }
    return encontrado;
}
empleados_laboratorio comprobar_coincidencia (char archivo[],char usuario[],char clave[])///recibe el archivo de empleados y devuelve si tiene coincidencia
{
    FILE*arch=fopen(archivo,"rb");
    empleados_laboratorio aux;
    empleados_laboratorio encontrado;

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
int comparar_perfil (empleados_laboratorio usuario) ///retorna 3-no se encontro / 1-administrativo /2-tecnico / -1-dado de baja.
{
    if(usuario.baja==1)
    {
        if(strstr(usuario.perfil,"administrativo"))
        {
            return 1;
        }
        else if(strstr(usuario.perfil,"tecnico"))
        {
            return 2;
        }
        else
        {
            return 3;/// no se encontro empleado
        }
    }
    else
    {
        return-1;  /// dado de baja
    }
}
///===============================================================================================================funciones-crear
///crear usuario (solo el admin supremo puede cargarlo)
empleados_laboratorio crear_empleado (char archivo[])
{
    empleados_laboratorio nuevo;

    nuevo.baja=1; ///alta
    int encontrado;
    ///verificando usuario
    do
    {
        printf("\nIngrese el nuevo usuario: ");
        fflush(stdin);
        gets(nuevo.usuario);
        encontrado=verificar_empleado_duplicado_usuario(archivo,nuevo.usuario);
    }
    while(encontrado!=0);

    printf("\nIngrese la clave nueva: ");
    fflush(stdin);
    gets(nuevo.clave);

    printf("\nIngrese el nombre: ");
    fflush(stdin);
    gets(nuevo.NyA);
    ///verificando dni
    do
    {
        printf("\nIngrese el DNI: ");
        fflush(stdin);
        gets(nuevo.dni);
        encontrado=verificar_empleado_duplicado_DNI(archivo,nuevo.dni);
    }
    while(encontrado!=0);
    ///cargnado perfil
    int perfil=menuPERFIL();
    if(perfil==0)
    {
        strcpy(nuevo.perfil,"administrativo");
    }
    else if(perfil ==1)
    {
        strcpy(nuevo.perfil,"tecnico");
    }
    return nuevo;
}

int verificar_empleado_duplicado_usuario (char archivo[],char usuario[]) /// 1o0 si encuentra duplicado o no
{
    FILE*arch= fopen(archivo,"rb");
    empleados_laboratorio aux;
    int encontrado=0;
    if(arch)
    {
        while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(strcmp(aux.usuario,usuario)==0)
            {
                encontrado=1;
                printf("\nUSUARIO EN USO, ELIJA OTRO...\n");
                system("pause");
                system("cls");
            }
        }
        fclose(arch);
        return encontrado;
    }
}
int verificar_empleado_duplicado_DNI (char archivo[],char dni[]) /// 1o0 si encuentra duplicado o no
{
    FILE*arch= fopen(archivo,"rb");
    empleados_laboratorio aux;
    int encontrado=0;
    if(arch)
    {
        while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(strcmp(aux.dni,dni)==0)
            {
                encontrado=1;
                printf("\nDNI EN USO, ELIJA OTRO...\n");
                system("pause");
                system("cls");
            }
        }
        fclose(arch);
        return encontrado;
    }
}
void cargar_empleado_to_archivo (char archivo[]) ///carga un empleado en el archivo
{
    FILE* arch =fopen(archivo,"ab");
    empleados_laboratorio aux;
    if (arch)
    {
        aux=crear_empleado(archivo);
        fwrite(&aux,sizeof(empleados_laboratorio),1,arch);
    }
    fclose(arch);
}
///===============================================================================================================funciones-mostrar
///mostrar empleado
void mostrar_empleado (empleados_laboratorio aux,int perfil)
{
    printf("\n=============================================");
    printf("\nUsuario: %s",aux.usuario);
    if(perfil == 0)
    {
        printf("\nClave: %s",aux.clave);
    }
    else
    {
        printf("\nClave: ********");
    }
    printf("\nNyA: %s",aux.NyA);
    printf("\nDNI: %s",aux.dni);
    printf("\nPerfil: %s",aux.perfil);
    printf("\nEstado: %i",aux.baja);
    if(aux.baja == 0)
    {
        printf("\nEstado: baja");
    }
    else
    {
        printf("\nEstado: alta");
    }
}
void mostrar_empleados_en_archivo (char archivo[],int perfil)  ///muestra todos los empleados
{
    FILE*arch= fopen(archivo,"rb");
    empleados_laboratorio aux;
    if(arch)
    {
        while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0)
        {
            mostrar_empleado(aux,perfil);
        }
        fclose(arch);
    }
}
nodo_lista* pasar_archivo_to_lista(char archivo[]) ///pasa todos los datos a una lista
{
    FILE*arch= fopen(archivo,"rb");
    empleados_laboratorio aux;
    nodo_lista*lista=NULL;
    if(arch)
    {
        while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0)
        {
            lista=agregar_al_final(lista,aux);
            //lista=agregar_al_final_ordenado_nya(lista,aux);
        }
        fclose(arch);
    }
    return lista;
}
nodo_lista* agregar_al_final (nodo_lista* lista, empleados_laboratorio dato) ///agrega dato al final en la lista
{
    if (lista==NULL)
    {
        return crear_nodo_lista(dato);
    }
    else
    {
        nodo_lista* seguir =lista;
        while(seguir->sig!=NULL)
        {
            seguir=seguir->sig;
        }
        seguir->sig=crear_nodo_lista(dato);
        return lista;
    }
}
nodo_lista* crear_nodo_lista (empleados_laboratorio dato) /// crea el nodo lista
{
    nodo_lista* nuevo =(nodo_lista*)malloc(sizeof(nodo_lista));
    nuevo->empleado=dato;
    nuevo->sig=NULL;
    return nuevo;
}
void mostrar_lista_entera(nodo_lista* lista,int perfil) ///muestra toda la lista
{
    nodo_lista* aux=lista;
    while(aux!=NULL)
    {
        mostrar_empleado(aux->empleado,perfil);
        aux=aux->sig;
    }
}
void mostrar_lista_baja_alta(nodo_lista* lista,int perfil,int alta_baja) ///muestra bajas o altas
{
    nodo_lista* aux=lista;
    while(aux!=NULL)
    {
        if(aux->empleado.baja==alta_baja)
        {
            mostrar_empleado(aux->empleado,perfil);
        }
        aux=aux->sig;
    }
    printf("\n");
    system("pause");
}

nodo_lista* agregar_al_final_ordenado_nya(nodo_lista*lista, empleados_laboratorio dato)///agrega de forma ordenada a la lista
{
    if (lista==NULL)
    {
        return crear_nodo_lista(dato);
    }
    else
    {
        if(strcmp(dato.NyA,lista->empleado.NyA)<0)
        {
            nodo_lista* seguir=lista;
            lista=crear_nodo_lista(dato);
            lista->sig=seguir;
        }
        else
        {
            nodo_lista*nuevo =crear_nodo_lista(dato);
            nodo_lista* ante =lista;
            nodo_lista* prox =lista->sig;
            while(prox!=NULL && strcmp(dato.NyA,prox->empleado.NyA)>0)
            {
                ante=prox;
                prox=prox->sig;
            }
            nuevo->sig=prox;
            ante->sig=nuevo;
            return lista;
        }
    }
}
///======================================================================================================funciones-buscar y modificar
void buscar_empleado_en_archivo_DNI(char archivo[],int perfil) ///solo busca coincidencia con dni y modifica si el usuario lo pide
{
    FILE*arch=fopen(archivo,"r+b");
    empleados_laboratorio aux;
    empleados_laboratorio nuevo;
    char dni_buscado[40];
    char encontrado='n';
    int modifificar;
    if(arch)
    {
        do
        {
            system("cls");
            printf("\t -- Hospital HP --\n\t  -Busqueda de empleados-\n");
            printf("\nIngrese el DNI buscado: ");
            fflush(stdin);
            gets(dni_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmp(aux.dni,dni_buscado)==0)
                {
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    printf("\nDesea modificar el empleado?");
                    modifificar=menuSI_NO();
                    if(modifificar==0)
                    {
                        aux=modificar_empleado(aux,archivo);
                        fseek(arch,(-1)*sizeof(empleados_laboratorio),SEEK_CUR);
                        fwrite(&aux,sizeof(empleados_laboratorio),1,arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                    }
                }
            }
            if(encontrado!='s')
            {
                printf("\nNo se encontro el empleado...\ndesea salir? tipee 's', cualquiera para repetir\n");
                fflush(stdin);
                encontrado=getch();
                fseek(arch,0,SEEK_SET);
            }
        }
        while(encontrado!='s');
        fclose(arch);
    }
}
void buscar_empleado_en_archivo_NYA(char archivo[],int perfil) ///solo busca coincidencia con usuario y modifica si el usuario lo pide
{
    FILE*arch=fopen(archivo,"r+b");
    empleados_laboratorio aux;
    empleados_laboratorio nuevo;
    char usuario_buscado[40];
    char encontrado='n';
    int modifificar;
    if(arch)
    {
        do
        {
            system("cls");
            printf("\t -- Hospital HP --\n\t  -Busqueda de empleados-\n");
            printf("\nIngrese el usuario buscado: ");
            fflush(stdin);
            gets(usuario_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmpi(aux.NyA,usuario_buscado)==0)
                {
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    printf("\nDesea modificar el empleado?");
                    modifificar=menuSI_NO();
                    if(modifificar==0)
                    {

                        aux=modificar_empleado(aux,archivo);
                        fseek(arch,(-1)*sizeof(empleados_laboratorio),SEEK_CUR);
                        fwrite(&aux,sizeof(empleados_laboratorio),1,arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                    }
                }
            }
            if(encontrado!='s')
            {
                printf("\nNo se encontro el empleado...\ndesea salir? tipee 's', cualquiera para repetir");
                fflush(stdin);
                scanf("%c",&encontrado);
                fseek(arch,0,SEEK_SET);
            }
        }
        while(encontrado!='s');
        fclose(arch);
    }
}
empleados_laboratorio modificar_empleado (empleados_laboratorio dato,char archivo[])
{
    int num=menuMODIFICAR();
    int perfil;
    int encontrado;
    switch(num)
    {
    case 0:
        printf("\nIngrese el nombre: ");
        fflush(stdin);
        gets(dato.NyA);
        break;
    case 1:
        encontrado=0;
        do
        {
            printf("\nIngrese el DNI: ");
            fflush(stdin);
            gets(dato.dni);
            encontrado=verificar_empleado_duplicado_DNI(archivo,dato.dni);
        }
        while(encontrado!=0);
        break;
    case 2:
        encontrado=0;
        do
        {
            printf("\nIngrese el nuevo usuario: ");
            fflush(stdin);
            gets(dato.usuario);
            encontrado=verificar_empleado_duplicado_usuario(archivo,dato.usuario);
        }
        while(encontrado!=0);
        break;
    case 3:
        printf("\nIngrese la clave nueva: ");
        fflush(stdin);
        gets(dato.clave);
        break;
    case 4:
        num=menuPERFIL();;
        if(num==0)
        {
            strcpy(dato.perfil,"administrativo");
        }
        else if(num ==1)
        {
            strcpy(dato.perfil,"tecnico");
        }
    case 5:
        if(dato.baja==1)
        {
            dato.baja=0;
        }
        else
        {
            dato.baja=1;
        }
        break;
    case 6:
        dato=crear_empleado(archivo);
    default:
        break;
    }
    return dato;
}

void dar_de_baja_alta_archivo(char archivo[],int perfil) ///solo busca coincidencia con dni y modifica si el usuario lo pide
{
    FILE*arch=fopen(archivo,"r+b");
    empleados_laboratorio aux;
    empleados_laboratorio nuevo;
    char dni_buscado[40];
    char encontrado='n';
    int modifificar;
    if(arch)
    {
        do
        {
            system("cls");
            printf("\t -- Hospital HP --\n\t  -Busqueda de empleados-\n");
            printf("\nIngrese el DNI buscado: ");
            fflush(stdin);
            gets(dni_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmp(aux.dni,dni_buscado)==0)
                {
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    modifificar=menuSI_NO();
                    if(modifificar==0)
                    {
                        if(aux.baja==0)
                        {
                            aux.baja=1;
                        }
                        else if(aux.baja==1)
                        {
                            aux.baja=0;
                        }
                        fseek(arch,(-1)*sizeof(empleados_laboratorio),SEEK_CUR);
                        fwrite(&aux,sizeof(empleados_laboratorio),1,arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                    }
                }
            }
            if(encontrado!='s')
            {
                printf("\nNo se encontro el empleado...\ndesea salir? tipee 's', cualquiera para repetir\n");
                fflush(stdin);
                encontrado=getch();
                fseek(arch,0,SEEK_SET);
            }
        }
        while(encontrado!='s');
        fclose(arch);
    }
}
///========================================================================================================================menus
int menuADMIN() ///menu principal del admin
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 6;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Menu Empleados";
    nuevoMenu.opciones[1] = "Menu Pacientes";
    nuevoMenu.opciones[2] = "Menu Ingresos";
    nuevoMenu.opciones[3] = "Menu Practicas";
    nuevoMenu.opciones[4] = "Menu Practicas por ingresos";
    nuevoMenu.opciones[5] = "Salir";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuADMINISTRATIVO() ///menu principal del administrativo
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 5;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Menu Pacientes";
    nuevoMenu.opciones[1] = "Menu Ingresos";
    nuevoMenu.opciones[2] = "Menu Practicas";
    nuevoMenu.opciones[3] = "Menu Practicas por ingresos";
    nuevoMenu.opciones[4] = "Salir";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuEmpleados() ///menu principal de Empleados
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 8;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Listado general de empleados";
    nuevoMenu.opciones[1] = "Listado Altas / Bajas";
    nuevoMenu.opciones[2] = "Consultar empleado (DNI)";
    nuevoMenu.opciones[3] = "Consultar empleado (Nombre y Apellido)";
    nuevoMenu.opciones[4] = "Modificar empleado";
    nuevoMenu.opciones[5] = "Dar de Alta un empleado";
    nuevoMenu.opciones[6] = "Modificar estado de empleado (Alta/Baja)";
    nuevoMenu.opciones[7] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPacientes() ///menu principal de Empleados
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 6;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver paciente";
    nuevoMenu.opciones[1] = "Modificar paciente";
    nuevoMenu.opciones[2] = "Alta de paciente";
    nuevoMenu.opciones[3] = "Baja de paciente";
    nuevoMenu.opciones[4] = "Listado General";
    nuevoMenu.opciones[5] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuIngresos() ///menu principal de ingresos
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 5;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver ingresos";
    nuevoMenu.opciones[1] = "Modificar ingreso";
    nuevoMenu.opciones[2] = "Alta de ingreso";
    nuevoMenu.opciones[3] = "Baja de ingreso";
    nuevoMenu.opciones[4] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPracticas() ///menu principal de practicas
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 5;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver practicas";
    nuevoMenu.opciones[1] = "Alta de Practica";
    nuevoMenu.opciones[2] = "Modificacion de Practica";
    nuevoMenu.opciones[3] = "Baja de practica";
    nuevoMenu.opciones[4] = "Volver al menu";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPracticasXIngresos() ///sub menu de practicas por ingresos (solo para master)
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 5;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver Practicas en cada ingreso";
    nuevoMenu.opciones[1] = "Modificar practicas en cada ingreso";
    nuevoMenu.opciones[2] = "Baja de practicas en cada ingreso";
    nuevoMenu.opciones[3] = "Alta de practicas en cada ingreso";
    nuevoMenu.opciones[4] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPracticasXIngresosTecnico() ///sub menu de practicas por ingresos (solo para tencicos)
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver Practicas en cada ingreso";
    nuevoMenu.opciones[1] = "Modificar practicas en cada ingreso";
    nuevoMenu.opciones[2] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPERFIL()  ///menu carga perfil
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 2;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "ADMINISTRATIVO";
    nuevoMenu.opciones[1] = "TECNICO";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuMODIFICAR() ///menu modificar
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 8;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Modificar nombre y apellido";
    nuevoMenu.opciones[1] = "Modificar DNI";
    nuevoMenu.opciones[2] = "Modificar usuario";
    nuevoMenu.opciones[3] = "Modificar clave";
    nuevoMenu.opciones[4] = "Modificar perfil";
    nuevoMenu.opciones[5] = "Modificar estado de Alta/Baja";
    nuevoMenu.opciones[6] = "Modificar todos los datos";
    nuevoMenu.opciones[7] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuMostrarAltaBaja() ///menu baja/alta
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Empleados en estado de Baja";
    nuevoMenu.opciones[1] = "Empleados en estado de Alta";
    nuevoMenu.opciones[2] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuBUSCAR() ///menu de opciones para buscar
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Modificar empleado buscando por DNI";
    nuevoMenu.opciones[1] = "Modificar empleado buscando por Nombre y Apellido";
    nuevoMenu.opciones[2] = "Salir";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuSI_NO() ///menu si/no
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP --\n\t-- Desea modificar los datos?";
    nuevoMenu.cantidadOpciones = 2;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "SI";
    nuevoMenu.opciones[1] = "NO";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuVerPaciente() ///sub menu ver pasiente
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Consultar paciente por DNI";
    nuevoMenu.opciones[1] = "Consultar paciente por nombre y apellido";
    nuevoMenu.opciones[2] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuIngresosTecnicos() ///sub menu ingresos tecnicos
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver por numero de ingesos";
    nuevoMenu.opciones[1] = "Ver por numero de DNI";
    nuevoMenu.opciones[2] = "Volver";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}
int menuPracticasTecnicos() ///sub menu practicas tecnicos
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Hospital HP";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ver Practicas";
    nuevoMenu.opciones[1] = "Alta de practicas";
    nuevoMenu.opciones[2] = "Baja de practicas";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}

///=================================================================================================================swichs menus
void menu_opciones_gerarquia (int perfil,char archivo[]) ///swich para mostrar los distintos menues dependiendo la gerarquia
{
    ///carga de arbol de pacientes
    nodoArbolPaciente * arbol=inicArbol();
    arbol=cargarArbolDesdeArchi("archivo_pacientes.bin", arbol);
    ///carga de lista de practicas
    NodoPractica * listaPracticas=inicListaPractica();
    listaPracticas=cargarListaPracticaDesdeArchivo(listaPracticas);
    ///carga de listaPxI
    NodoPxI * listaPxI=inicListaPxI();
    int opcion;
    int opcionInterna;
    switch(perfil)
    {

    case 0:              ///<---- master
        do
        {
            opcion=menuADMIN();

            if(opcion==0)
            {
                do ///empleados
                {
                    opcionInterna=menuEmpleados();
                    swicherAdmin(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=7);
            }
            else if(opcion==1)
            {
                do ///pacientes
                {
                    opcionInterna=menuPacientes();
                    swicherPacientes(opcionInterna,perfil,archivo, &arbol);
                }
                while(opcionInterna!=5);
            }
            else if(opcion==2)
            {
                do ///ingresos
                {
                    opcionInterna=menuIngresos();
                    swicherIngresos(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=4);
            }
            else if(opcion==3)
            {
                do ///practicas
                {
                    opcionInterna=menuPracticas();
                    swicherPracticasMaster(opcionInterna,perfil, &listaPracticas, &listaPxI);
                }
                while(opcionInterna!=4);
            }
            else if(opcion==4)
            {
                do ///practica x ingreso
                {
                    opcionInterna=menuPracticasXIngresos();
                    swicherPracticasXIngresosMaster(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=4);
            }
        }
        while(opcion!=5);
        break;
    case 1:              ///<---- administrador
        do
        {
            opcion=menuADMINISTRATIVO();
            if(opcion==0)
            {
                do ///pacientes
                {
                    opcionInterna=menuPacientes();
                    swicherPacientes(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=5);
            }
            else if(opcion==1)
            {
                do ///ingresos
                {
                    opcionInterna=menuIngresos();
                    swicherIngresos(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=4);
            }
            else if(opcion==2)
            {
                mostrarListaPracticas(listaPracticas, 0);
            }
            else if(opcion==3)
            {
                opcionInterna=menuPracticasXIngresos();
                swicherPracticasXIngresosAdministrativo(opcionInterna,perfil,archivo);
            }
        }
        while(opcion!=4);
        break;
    case 2:              ///<---- tecnico
        do
        {
            opcion=menuADMINISTRATIVO(); ///se utiliza el mismo menu dado que cumple con los mismos parametros
            if(opcion==0)
            {
                ///ver pacientes funcion sola
            }
            else if(opcion==1)
            {
                opcionInterna=menuIngresosTecnicos();
                swicherIngresosTecnicos(opcionInterna,perfil,archivo);
            }
            else if(opcion==2)
            {
                do ///practicas
                {
                    opcionInterna=menuPracticas();
                    swicherPracticasMaster(opcionInterna,perfil, &listaPracticas, &listaPxI);
                }
                while(opcionInterna!=5);
            }
            else if(opcion==3)
            {
                opcionInterna=menuPracticasXIngresosTecnico();
                swicherPracticasXIngresosTecnicos(opcionInterna,perfil,archivo);
            }
        }
        while(opcion!=4);
        break;
    default:
        system("cls");
        printf("\n*ERROR: INTENTOS MAXIMOS ALCANZADOS... \nCERRANDO PROGRAMA...");
    }
    actualizarArchivoPracticas(listaPracticas);
    actualizarPacientesEnArchivo (arbol);
}


void swicherAdmin (int opcion,int perfil,char archivo[]) ///swich menu que ve el master
{
    int aux;
    int duplicado=opcion;
    nodo_lista* lista;
    lista=pasar_archivo_to_lista(archivo);
    switch(duplicado)
    {
    case 0:
        system("cls");
        printf("\t -- Hospital HP --\n\t   -Lista de empleados-\n");
        mostrar_lista_entera(lista,perfil);
        printf("\n");
        system("pause");
        break;
    case 1:
        aux=menuMostrarAltaBaja();
        if(aux==0)
        {
            printf("\t -- Hospital HP --\n\t   -Lista estado de Baja- \n");
        }
        else if(aux==1)
        {
            printf("\t -- Hospital HP --\n\t   -Lista estado de Alta- \n");
        }
        if(aux!=2)
        {
            mostrar_lista_baja_alta(lista,perfil,aux);
        }
        break;
    case 2:

        buscar_empleado_en_archivo_DNI(archivo,perfil);
        break;
    case 3:
        buscar_empleado_en_archivo_NYA(archivo,perfil);
        break;
    case 4:
        aux=menuBUSCAR();
        if(aux==0)
        {
            buscar_empleado_en_archivo_DNI(archivo,perfil);
        }
        else if(aux ==1)
        {
            buscar_empleado_en_archivo_NYA(archivo,perfil);
        }
        break;
    case 5:
        system("cls");
        printf("\t -- Hospital HP --\n\t   -Alta de empleado-\n");
        cargar_empleado_to_archivo(archivo);
        system("cls");
        printf("\nEmpleado cargado con exito\n");
        system("pause");
        break;
    case 6:
        dar_de_baja_alta_archivo(archivo,perfil);
        break;
    case 7:
        printf("\nDeslogueando...\n");
        break;
    default:
        break;
    }
}

void swicherPacientes (int opcion,int perfil,char archivo[], nodoArbolPaciente ** arbol)  ///sirve para master y administrativo
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    int dni;
    nodoArbolPaciente * buscado=NULL;
    switch(duplicado)
    {
    case 0:
        buscado=NULL;
        printf ("Ingrese un dni para buscar :");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbol, dni);
        if (buscado)
        {
            mostrarNodoArbol(buscado);
        }
        else
        {
            printf ("No existe un paciente con el dni %d en el sistema \n", dni);
        }
        system("pause");
        break;
    case 1:
        buscado=NULL;
        mostrarArbolPacientes(*arbol);
        printf ("Ingrese un dni del paciente a modificar :");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbol, dni);
        if (buscado)
        {
            *arbol=actualizarNodoArbol (*arbol, dni);
        }
        else
        {
            printf ("No existe un paciente con el dni %d en el sistema \n", dni);
        }
        system("pause");
        break;
    case 2:
        *arbol=cargarArbolOrdenadoDNI(*arbol, crearNodoArbol(cargaManualPaciente()));
        break;
    case 3:
        buscado=NULL;
        mostrarArbolPacientes(*arbol);
        printf ("Ingrese un dni del paciente a eliminar :");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbol, dni);
        if (buscado)
        {
            *arbol=bajaNodoArbol (*arbol, dni);
        }
        else
        {
            printf ("No existe un paciente con el dni %d en el sistema \n", dni);
        }
        system("pause");
        break;
    case 4:
        mostrarArbolPacientes(*arbol);
        system("pause");
    default:
        break;
    }
}
void swicherIngresos (int opcion,int perfil,char archivo[])  ///sirve para master y administrativo
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    switch(duplicado)
    {
    case 0:
        ///ver Ingresos
        break;
    case 1:
        ///modificar Ingresos
        break;
    case 2:
        ///alta Ingresos
        break;
    case 3:
        ///baja Ingresos
        break;
    default:
        break;
    }
}
void swicherPracticasMaster (int opcion, int perfil, NodoPractica ** listaPracticas, NodoPxI ** listaPxI)  ///sirve para solo para master master
{
    /*
    nuevoMenu.opciones[0] = "Ver practicas";
    nuevoMenu.opciones[1] = "Alta de Practica";
    nuevoMenu.opciones[2] = "Modificacion de Practica";
    nuevoMenu.opciones[3] = "Baja de practica";
    */
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    switch(duplicado)
    {
    case 0:
    {
        mostrarListaPracticas(*listaPracticas, 1);
        system("pause");
    }
    break;
    case 1:
    {
        Practica nueva=crearStPractica();
        *listaPracticas=altaDePractica(*listaPracticas, crearNodoPractica(nueva));
        system("pause");
    }
    break;
    case 2:
        mostrarListaPracticas(*listaPracticas, 1);
        printf("\n Ingrese el id de la practica a modificar:");
        int idEditar;
        scanf("%d",&idEditar);
        printf("\n Ingrese el nuevo nombre de practica: ");
        char nuevoNombre [30];
        fflush(stdin);
        gets(nuevoNombre);
        editarPractica(*listaPracticas, idEditar,nuevoNombre);
        system("pause");
        break;
    case 3:
        mostrarListaPracticas(*listaPracticas, 1);
        printf("\n Ingrese el id de la practica a eliminar:");
        int idEliminar;
        scanf("%d",&idEliminar);
        BajaNodoPractica(idEliminar, *listaPracticas, *listaPxI);
        break;
    case 4:
        break;
    default:
        break;
    }
}
void swicherPracticasXIngresosMaster (int opcion, int perfil, NodoPractica * listaPracticas, NodoIngresos * listaIngresos, NodoPxI * listaPxI)  ///sirve para solo para master master
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.

    switch(duplicado)
    {
    case 0:
        ///ver practicas x ingreso
        break;
    case 1:
        ///modificar practicas
        break;
    case 2:
        ///baja practicas
        break;
    case 3:
        ///alta practicas
        break;
    default:
        break;
    }
}
void swicherPracticasXIngresosAdministrativo (int opcion,int perfil,char archivo[])  ///sirve para solo para ADMINISTRATIVO
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.

    switch(duplicado)
    {
    case 0:
        ///ver practicas x ingreso
        break;
    case 1:
        ///modificar practicas
        break;
    case 2:
        ///baja practicas
        break;
    case 3:
        ///alta practicas
        break;
    default:
        break;
    }
}
void swicherIngresosTecnicos(int opcion,int perfil,char archivo[])  ///sirve para solo para tercnico
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.

    switch(duplicado)
    {
    case 0:
        ///ver ingreso por numero
        break;
    case 1:
        ///ver ingreso por dni
        break;
    default:
        break;
    }
}
void swicherPracticasTecnicos(int opcion,int perfil,char archivo[])  ///sirve para solo para tercnico
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.

    switch(duplicado)
    {
    case 0:
        ///ver practicas
        break;
    case 1:
        ///alta practicas
        break;
    case 2:
        ///baja practicas
        break;
    default:
        break;
    }
}
void swicherPracticasXIngresosTecnicos(int opcion,int perfil,char archivo[])  ///sirve para solo para tercnico
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.

    switch(duplicado)
    {
    case 0:
        ///ver practicas en cada ingreso
        break;
    case 1:
        ///modificar practicas en cada ingreso
        break;
    default:
        break;
    }
}
