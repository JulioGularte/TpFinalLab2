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
    printf("\t -- Laboratorio C --\n");
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
            printf("\t -- Laboratorio C --\n\tLa clave o usuario no existen...\n/tLe quedan %i intentos...",intentos-1);
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
        printf("\n\tIngrese el nuevo usuario: ");
        fflush(stdin);
        gets(nuevo.usuario);
        encontrado=verificar_empleado_duplicado_usuario(archivo,nuevo.usuario);
    }
    while(encontrado!=0);

    printf("\n\tIngrese la clave nueva: ");
    fflush(stdin);
    gets(nuevo.clave);

    printf("\n\tIngrese el nombre: ");
    fflush(stdin);
    gets(nuevo.NyA);
    ///verificando dni
    do
    {
        printf("\n\tIngrese el DNI: ");
        fflush(stdin);
        gets(nuevo.dni);
        encontrado=verificar_empleado_duplicado_DNI(archivo,nuevo.dni);
    }
    while(encontrado!=0);
    ///cargnado perfil
    int perfil=menuPERFIL();
    if(perfil==1)
    {
        strcpy(nuevo.perfil,"administrativo");
    }
    else if(perfil ==2)
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
    printf("\n\tUsuario:....................%s",aux.usuario);
    if(perfil == 0)
    {
        printf("\n\tClave:......................%s",aux.clave);
    }
    else
    {
        printf("\n\tClave:........................********");
    }
    printf("\n\tNyA:........................%s",aux.NyA);
    printf("\n\tDNI:........................%s",aux.dni);
    printf("\n\tPerfil:.....................%s",aux.perfil);
    printf("\n\tEstado:.....................%i",aux.baja);
    if(aux.baja == 0)
    {
        printf("\n\tEstado:.....................Baja\n");
    }
    else
    {
        printf("\n\tEstado:.....................Alta\n");
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
    system("pause");
    printf("\n");
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
void buscar_empleado_en_archivo_DNI(char archivo[],int perfil, nodo_lista* lista) ///solo busca coincidencia con dni y modifica si el usuario lo pide
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
            printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
            mostrar_lista_entera(lista,perfil);
            printf("\n\n\t-Busqueda de empleados-\n");
            printf("\n\tIngrese el DNI buscado: ");
            fflush(stdin);
            gets(dni_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmp(aux.dni,dni_buscado)==0)
                {

                    system("cls");
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    printf("\nDesea modificar el empleado?");
                    modifificar=menuSI_NO();
                    if(modifificar==1)
                    {
                        aux=modificar_empleado(aux,archivo);
                        long int posicion_actual = ftell(arch);
                        fseek(arch, posicion_actual - sizeof(empleados_laboratorio), SEEK_SET);
                        fwrite(&aux, sizeof(empleados_laboratorio), 1, arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                        break;
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
void buscar_empleado_en_archivo_NYA(char archivo[],int perfil, nodo_lista* lista) ///solo busca coincidencia con usuario y modifica si el usuario lo pide
{
    FILE*arch=fopen(archivo,"r+b");
    empleados_laboratorio aux;
    empleados_laboratorio nuevo;
    char nombre_buscado[40];
    char encontrado='n';
    int modifificar;
    if(arch)
    {
        do
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
            mostrar_lista_entera(lista,perfil);
            printf("\n\n\t-Busqueda de empleados-\n");
            printf("\n\tIngrese el nombre buscado: ");
            fflush(stdin);
            gets(nombre_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmpi(aux.NyA,nombre_buscado)==0)
                {
                    system("cls");
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    printf("\nDesea modificar el empleado?");
                    modifificar=menuSI_NO();
                    if(modifificar==1)
                    {
                        aux=modificar_empleado(aux,archivo);
                        long int posicion_actual = ftell(arch);
                        fseek(arch, posicion_actual - sizeof(empleados_laboratorio), SEEK_SET);
                        fwrite(&aux, sizeof(empleados_laboratorio), 1, arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                        break;
                    }
                }
            }
            if(encontrado!='s')
            {
                printf("\nNo se encontro el empleado...\ndesea salir? tipee 's', cualquiera para repetir");
                fflush(stdin);
                encontrado=getch();
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
    empleados_laboratorio aux=dato;
    switch(num)
    {
    case 1:
        printf("\nIngrese el nombre: ");
        fflush(stdin);
        gets(aux.NyA);
        break;
    case 2:
        encontrado=0;
        do
        {
            printf("\nIngrese el DNI: ");
            fflush(stdin);
            gets(aux.dni);
            encontrado=verificar_empleado_duplicado_DNI(archivo,aux.dni);
        }
        while(encontrado!=0);
        break;
    case 3:
        encontrado=0;
        do
        {
            printf("\nIngrese el nuevo usuario: ");
            fflush(stdin);
            gets(aux.usuario);
            encontrado=verificar_empleado_duplicado_usuario(archivo,aux.usuario);
        }
        while(encontrado!=0);
        break;
    case 4:
        printf("\nIngrese la clave nueva: ");
        fflush(stdin);
        gets(aux.clave);
        break;
    case 5:
        num=menuPERFIL();;
        if(num==1)
        {
            strcpy(aux.perfil,"administrativo");
        }
        else if(num ==2)
        {
            strcpy(aux.perfil,"tecnico");
        }
        break;
    case 6:
        if(aux.baja==1)
        {
            aux.baja=0;
        }
        else
        {
            aux.baja=1;
        }
        break;
    case 7:
        aux=crear_empleado(archivo);
    default:
        break;
    }
    return aux;
}

void dar_de_baja_alta_archivo(char archivo[],int perfil,nodo_lista* lista) ///solo busca coincidencia con dni y modifica si el usuario lo pide
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
            printf("\t -- Laboratorio C --\n\t  -Busqueda de empleados-\n");
            mostrar_lista_entera(lista,perfil);
            printf("\n\tIngrese el DNI buscado: ");
            fflush(stdin);
            gets(dni_buscado);
            while(fread(&aux,sizeof(empleados_laboratorio),1,arch)>0 && encontrado!='s')
            {
                if(strcmp(aux.dni,dni_buscado)==0)
                {
                    system("cls");
                    printf("\nEmpleado encontrado: \n");
                    mostrar_empleado(aux,perfil);
                    encontrado='s';
                    printf("\n");
                    system("pause");
                    modifificar=menuSI_NO();
                    if(modifificar==1)
                    {
                        if(aux.baja==0)
                        {
                            aux.baja=1;
                        }
                        else if(aux.baja==1)
                        {
                            aux.baja=0;
                        }
                        aux=modificar_empleado(aux,archivo);
                        long int posicion_actual = ftell(arch);
                        fseek(arch, posicion_actual - sizeof(empleados_laboratorio), SEEK_SET);
                        fwrite(&aux, sizeof(empleados_laboratorio), 1, arch);
                        printf("\nEmpleado modificado con exito\n");
                        system("pause");
                        break;
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
    int opcion;

        do
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Menu MASTER-\n");
            printf("\n\t1)Menu Empleados");
            printf("\n\t2)Menu Pacientes");
            printf("\n\t3)Menu Ingresos");
            printf("\n\t4)Menu Practicas");
            printf("\n\t5)Menu Practicas por ingreso");
            printf("\n\t0)Salir");
            printf("\n\n\tIngrese la opcion que desea ver: ");
            scanf("%i",&opcion);
        }while (opcion<0 && opcion>5);

    return opcion;
}
int menuADMINISTRATIVO() ///menu principal del administrativo
{
    int opcion;

        do
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Menu ADMINISTRATIVO-\n");
            printf("\n\t1)Ver listado general de empleados");
            printf("\n\t2)Menu Pacientes");
            printf("\n\t3)Menu Ingresos");
            printf("\n\t4)Menu Ver Practicas");
            printf("\n\t0)Salir");
            printf("\n\n\tIngrese la opcion que desea ver: ");
            scanf("%i",&opcion);
        }while (opcion<0 && opcion>4);

    return opcion;
}
int menuTECNICO() ///menu principal del administrativo
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu TECNICO-\n");
        printf("\n\t1)Ver listado general de empleados");
        printf("\n\t2)Ver Pacientes");
        printf("\n\t3)Ver Ingresos");
        printf("\n\t4)Menu Practicas");
        printf("\n\t5)Menu Practicas por ingresos");
        printf("\n\t0)Salir");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>5);

    return opcion;
}
int menuEmpleados() ///menu principal de Empleados
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Empleados-\n");
        printf("\n\t1)Ver listado general de empleados");
        printf("\n\t2)Ver listado Altas / Bajas");
        printf("\n\t3)Consultar empleado (DNI)");
        printf("\n\t4)Consultar empleado (Nombre y Apellido)");
        printf("\n\t5)Modificar empleado");
        printf("\n\t6)Dar de Alta un empleado");
        printf("\n\t7)Modificar estado de empleado (Alta/Baja)");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>7);

    return opcion;
}
int menuPacientes() ///menu principal de Empleados
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Pacientes-\n");
        printf("\n\t1)Ver paciente");
        printf("\n\t2)Modificar paciente");
        printf("\n\t3)Alta de paciente");
        printf("\n\t4)Baja de paciente");
        printf("\n\t5)Listado General");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>5);

    return opcion;
}
int menuIngresos() ///menu principal de ingresos
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Ingresos-\n");
        printf("\n\t1)Ver paciente");
        printf("\n\t2)Modificar paciente");
        printf("\n\t3)Alta de paciente");
        printf("\n\t4)Baja de paciente");
        printf("\n\t5)Listado General");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>5);

    return opcion;
}
int menuPracticas() ///menu principal de practicas
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Practicas-\n");
        printf("\n\t1)Ver practicas");
        printf("\n\t2)Alta de Practica");
        printf("\n\t3)Modificacion de Practica");
        printf("\n\t4)Baja de practica");
        printf("\n\t5)Filtrado de practicas por iniciales");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>5);

    return opcion;
}
int menuPracticasXIngresos() ///sub menu de practicas por ingresos (solo para master)
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Practicas por ingresos-\n");
        printf("\n\t1)Ver Practicas en cada ingreso");
        printf("\n\t2)Modificar practicas en cada ingreso");
        printf("\n\t3)Baja de practicas en cada ingreso");
        printf("\n\t4)Alta de practicas en cada ingreso");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>4);

    return opcion;
}
int menuPracticasXIngresosTecnico() ///sub menu de practicas por ingresos (solo para tencicos)
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Practicas por ingresos-\n");
        printf("\n\t1)Ver Practicas en cada ingreso");
        printf("\n\t2)Modificar practicas en cada ingreso");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>2);

    return opcion;
}
int menuPERFIL()  ///menu carga perfil
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Perfil-\n");
        printf("\n\t1)ADMINISTRATIVO");
        printf("\n\t2)TECNICO");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<1 && opcion>2);

    return opcion;
}
int menuMODIFICAR() ///menu modificar
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Modificar-\n");
        printf("\n\t1)Modificar nombre y apellido");
        printf("\n\t2)Modificar DNI");
        printf("\n\t3)Modificar usuario");
        printf("\n\t4)Modificar clave");
        printf("\n\t5)Modificar perfil");
        printf("\n\t6)Modificar estado de Alta/Baja");
        printf("\n\t7)Modificar todos los datos");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>7);

    return opcion;
}
int menuMostrarAltaBaja() ///menu baja/alta
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Alta/Baja-\n");
        printf("\n\t1)Empleados en estado de Baja");
        printf("\n\t2)Empleados en estado de Alta");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>2);

    return opcion;
}
int menuBUSCAR() ///menu de opciones para buscar
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Busqueda-\n");
        printf("\n\t1)Modificar empleado buscando por DNI");
        printf("\n\t2)Modificar empleado buscando por Nombre y Apellido");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>2);

    return opcion;
}
int menuSI_NO() ///menu si/no
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -¿Desea modificar?-\n");
        printf("\n\t1)SI");
        printf("\n\t2)NO");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<1 && opcion>2);

    return opcion;
}
int menuVerPaciente() ///sub menu ver pasiente
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Paciente-\n");
        printf("\n\t1)Consultar paciente por DNI");
        printf("\n\t2)Consultar paciente por nombre y apellido");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>2);

    return opcion;
}
int menuIngresosTecnicos() ///sub menu ingresos tecnicos
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Ingresos-\n");
        printf("\n\t1)Ver por numero de ingesos");
        printf("\n\t2)Ver por numero de DNI");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>2);

    return opcion;
}
int menuPracticasTecnicos() ///sub menu practicas tecnicos
{
    int opcion;

    do
    {
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Menu Practicas-\n");
        printf("\n\t1)Ver Practicas");
        printf("\n\t2)Alta de practicas");
        printf("\n\t3)Baja de practicas");
        printf("\n\t0)Volver al menu");
        printf("\n\n\tIngrese la opcion que desea ver: ");
        scanf("%i",&opcion);
    }while (opcion<0 && opcion>3);

    return opcion;
}

///=================================================================================================================swichs menus

void menu_opciones_gerarquia (int perfil,char archivo[]) ///swich para mostrar los distintos menues dependiendo la gerarquia
{
    ///carga de arbol de pacientes
    nodoArbolPaciente * arbol=inicArbol();
    arbol=cargarArbolDesdeArchi("archivo_pacientes.bin", arbol);
    ///carga de ingresos
    cargarTodasListasIngresoDesdeArchi("archivoIngresos.bin",arbol);
    ///carga de lista de practicas
    NodoPractica * listaPracticas=inicListaPractica();
    listaPracticas=cargarListaPracticaDesdeArchivo(listaPracticas);
    ///carga de listaPxI
    NodoPxI * listaPxI=inicListaPxI();
    ///carga de empleados
    nodo_lista* lista=pasar_archivo_to_lista(archivo);
    int opcion;
    int opcionInterna;
    int nroUltimoIngreso=contarIngresosEnArchivo();
    switch(perfil)
    {

    case 0:              ///<---- master
        do
        {
            opcion=menuADMIN();
            if(opcion==1)
            {
                do ///empleados
                {
                    opcionInterna=menuEmpleados();
                    swicherAdmin(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=0);
            }
            else if(opcion==2)
            {
                do ///pacientes
                {
                    opcionInterna=menuPacientes();
                    swicherPacientes(opcionInterna,perfil,archivo, &arbol);
                }
                while(opcionInterna!=0);
            }
            else if(opcion==3)
            {
                do ///ingresos
                {
                    opcionInterna=menuIngresos();
                    swicherIngresos(opcionInterna,perfil, &arbol ,&listaPracticas, &listaPxI, &nroUltimoIngreso); ///sirve para master y administrativo
                }
                while(opcionInterna!=0);
            }
            else if(opcion==4)
            {
                do ///practicas
                {
                    opcionInterna=menuPracticas();
                    swicherPracticasMaster(opcionInterna,perfil, &listaPracticas, &listaPxI);
                }
                while(opcionInterna!=0);
            }
            else if(opcion==5)
            {
                do ///practica x ingreso
                {
                    opcionInterna=menuPracticasXIngresos();
                    swicherPracticasXIngresosMaster(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=0);
            }
        }
        while(opcion!=0);
        break;
    case 1:              ///<---- administrador
        do
        {
            opcion=menuADMINISTRATIVO();
            if(opcion==1)
            {
                system("cls");
                printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
                mostrar_lista_entera(lista,perfil);
                printf("\n");
                system("pause");
            }
            else if(opcion==2)
            {
                do ///pacientes
                {
                    opcionInterna=menuPacientes();
                    swicherPacientes(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=0);
            }
            else if(opcion==3)
            {
                do ///ingresos
                {
                    opcionInterna=menuIngresos();
                    swicherIngresos(opcionInterna,perfil,archivo);
                }
                while(opcionInterna!=0);
            }
            else if(opcion==4)
            {
                mostrarListaPracticas(listaPracticas, 0);
                system("pause");
            }
            else if(opcion==5)
            {
                opcionInterna=menuPracticasXIngresos();
                swicherPracticasXIngresosAdministrativo(opcionInterna,perfil,archivo);
            }
        }
        while(opcion!=0);
        break;
    case 2:              ///<---- tecnico
        do
        {
            opcion=menuTECNICO(); ///se utiliza el mismo menu dado que cumple con los mismos parametros
            if(opcion==1)
            {
                system("cls");
                printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
                mostrar_lista_entera(lista,perfil);
                printf("\n");
                system("pause");
            }
            else if(opcion==2)
            {
                ///ver pacientes funcion sola
            }
            else if(opcion==3)
            {
                opcionInterna=menuIngresosTecnicos();
                swicherIngresosTecnicos(opcion,perfil, &arbol, &listaPracticas, &listaPxI, &nroUltimoIngreso);
            }
            else if(opcion==4)
            {
                do ///practicas
                {
                    opcionInterna=menuPracticas();
                    swicherPracticasMaster(opcionInterna,perfil, &listaPracticas, &listaPxI);
                }while(opcionInterna!=0);
            }
            else if(opcion==5)
            {
                do{
                    opcionInterna=menuPracticasXIngresosTecnico();
                    swicherPracticasXIngresosTecnicos(opcionInterna,perfil,archivo);
                }while(opcionInterna!=0);
            }
        }
        while(opcion!=0);
        break;
    default:
        system("cls");
        printf("\n*ERROR: INTENTOS MAXIMOS ALCANZADOS... \nCERRANDO PROGRAMA...");
    }
    actualizarArchivoPracticas(listaPracticas);
    actualizarPacientesEnArchivo (arbol);
    actualizarArchivoPxI(listaPxI);
}


void swicherAdmin (int opcion,int perfil,char archivo[]) ///swich menu que ve el master
{
    int aux;
    int duplicado=opcion;
    nodo_lista* lista;
    lista=pasar_archivo_to_lista(archivo);
    switch(duplicado)
    {
    case 1:
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
        mostrar_lista_entera(lista,perfil);
        printf("\n");
        system("pause");
        break;
    case 2:
        aux=menuMostrarAltaBaja();
        if(aux==1)
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Lista estado de Baja- \n");
        }
        else if(aux==2)
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Lista estado de Alta- \n");
        }
        if(aux!=0)
        {
            mostrar_lista_baja_alta(lista,perfil,aux);
        }
        break;
    case 3:
        buscar_empleado_en_archivo_DNI(archivo,perfil,lista);
        break;
    case 4:
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
        mostrar_lista_entera(lista,perfil);

        buscar_empleado_en_archivo_NYA(archivo,perfil,lista);
        break;
    case 5:
        aux=menuBUSCAR();
        if(aux==1)
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
            mostrar_lista_entera(lista,perfil);

            buscar_empleado_en_archivo_DNI(archivo,perfil,lista);
        }
        else if(aux ==2)
        {
            system("cls");
            printf("\t -- Laboratorio C --\n\t   -Lista de empleados-\n");
            mostrar_lista_entera(lista,perfil);

            buscar_empleado_en_archivo_NYA(archivo,perfil,lista);
        }
        break;
    case 6:
        system("cls");
        printf("\t -- Laboratorio C --\n\t   -Alta de empleado-\n");
        cargar_empleado_to_archivo(archivo);
        system("cls");
        printf("\nEmpleado cargado con exito\n");
        system("pause");
        break;
    case 7:
        dar_de_baja_alta_archivo(archivo,perfil,lista);
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
    case 1:
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
    case 2:
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
    case 3:
        *arbol=cargarArbolOrdenadoDNI(*arbol, crearNodoArbol(cargaManualPaciente()));
        break;
    case 4:
        buscado=NULL;
        mostrarArbolPacientes(*arbol);
        printf ("Ingrese un dni del paciente a eliminar :");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbol, dni);
        if (buscado)
        {
///            *arbol=bajaNodoArbol (*arbol, dni);
        }
        else
        {
            printf ("No existe un paciente con el dni %d en el sistema \n", dni);
        }
        system("pause");
        break;
    case 5:
        mostrarArbolPacientes(*arbol);
        system("pause");
    default:
        break;
    }
}

void swicherIngresos (int opcion,int perfil, nodoArbolPaciente ** arbolPaciente, NodoPractica ** listaDePracticas, NodoPxI ** listaPxI, int * nroUltimoIngreso)  ///sirve para master y administrativo
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    nodoArbolPaciente * buscado=NULL;
    int dni;
    switch(duplicado)
    {
    case 1:
        mostrarArbolPacientes(*arbolPaciente);
        printf("Ingrese el DNI del paciente del cual desea ver sus ingresos: ");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbolPaciente, dni);
        if (buscado)
        {
            mostrarListaIngresos((*arbolPaciente)->listaIngresos);
        }
        else
        {
            printf("El DNI %d no es valido  \n");
            system("pause");
        }
        system("pause");
        break;
    case 2:
        mostrarArbolPacientes(*arbolPaciente);
        printf("Ingrese el DNI del paciente al cual desea modificar el ingreso \n el mismo debe estar en estado activo:");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbolPaciente, dni);
        if (buscado && buscado->paciente.eliminado==0)
        {
            altaDeIngresoPaciente(buscado, nroUltimoIngreso, listaDePracticas, listaPxI);
            actualizarArchivoIngreso(*buscado->listaIngresos);
        }
        else
        {
            printf("El DNI %d no es valido para realizar una modificacion de ingreso \n");
            system("pause");
        }
        break;
    case 3:
        mostrarArbolPacientes(*arbolPaciente);
        printf("Ingrese el DNI del paciente al cual desea realizar el ingreso \n el mismo debe estar en estado activo:");
        scanf("%d",&dni);
        buscado=buscarXDni(*arbolPaciente, dni);
        if (buscado && buscado->paciente.eliminado==0)
        {
            altaDeIngresoPaciente(buscado, nroUltimoIngreso, *listaDePracticas, *listaPxI);
            actualizarArchivoIngreso(*buscado->listaIngresos);
        }
        else
        {
            printf("El DNI %d no es valido para realizar un alta de ingreso \n");
            system("pause");
        }
        break;
    case 4:
        BajaDeIngresos (*arbolPaciente, *listaPxI);
        system("pause");
        break;
    default:
        break;
    }
}
void swicherPracticasMaster (int opcion, int perfil, NodoPractica ** listaPracticas, NodoPxI ** listaPxI)  ///sirve para solo para master master
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    switch(duplicado)
    {
    case 1:
    {
        system("cls");
        mostrarListaPracticas(*listaPracticas, 1);
        system("pause");
    }
    break;
    case 2:
    {
        system("cls");
        Practica nueva=crearStPractica();
        (*listaPracticas)=altaDePractica(*listaPracticas, crearNodoPractica(nueva));
        system("pause");
    }
    break;
    case 3:
        mostrarListaPracticas(*listaPracticas, 1);
        printf("\n Ingrese el id de la practica a modificar:");
        int idEditar;
        scanf("%d",&idEditar);
        printf("\n Ingrese el nuevo nombre de practica: ");
        char nuevoNombre [30];
        fflush(stdin);
        gets(nuevoNombre);
        editarPractica((*listaPracticas), idEditar,nuevoNombre);
        system("pause");
        break;
    case 4:
        mostrarListaPracticas(*listaPracticas, 1);
        printf("\n Ingrese el id de la practica a eliminar:");
        int idEliminar;
        scanf("%d",&idEliminar);
        BajaNodoPractica(idEliminar, (*listaPracticas), (*listaPxI));
        break;
    case 5:
        printf ("Ingrese la practica a buscar \n");
        char busqueda[30];
        gets(busqueda);
        NodoPractica * listaFiltrada=filtrarPracticasPorIniciales(*listaPracticas, busqueda);
        mostrarListaPracticas(listaFiltrada, 1);
        system("pause");
        break;
    default:
        break;
    }
}
void swicherPracticasXIngresosMaster (int opcion, int perfil, NodoPractica ** listaPracticas, NodoPxI ** listaPxI, nodoArbolPaciente ** pacientes)  ///sirve para solo para master master
{
    int duplicado=opcion; ///por alguna razon el switch no toma la variable opcion y es necesario duplicarla.
    nodoArbolPaciente * buscado=NULL;
    int dni;
    switch(duplicado)
    {
    case 1:
        ///ver practicas x ingreso
        break;
    case 2:
        ///modificar practicas
        break;
    case 3:
        ///baja practicas
        break;
    case 4:
        mostrarArbolPacientes(*pacientes);
        printf("Ingrese el DNI del paciente al cual desea dar de alta una practica \n el mismo debe estar en estado activo:");
        scanf("%d",&dni);
        buscado=buscarXDni(*pacientes, dni);
        if (buscado && buscado->paciente.eliminado==0)
        {
            AltaDePracticaPxI (*listaPxI, buscado, *listaPracticas);
            actualizarArchivoIngreso(buscado->listaIngresos);
        }
        else
        {
            printf("El DNI %d no es valido para realizar un alta de practica \n");
            system("pause");
        }
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
    case 1:
        ///ver practicas x ingreso
        break;
    case 2:
        ///modificar practicas
        break;
    case 3:
        ///baja practicas
        break;
    case 4:
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
    case 1:
        ///ver ingreso por numero
        break;
    case 2:
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
    case 1:
        ///ver practicas
        break;
    case 2:
        ///alta practicas
        break;
    case 3:
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
    case 1:
        ///ver practicas en cada ingreso
        break;
    case 2:
        ///modificar practicas en cada ingreso
        break;
    default:
        break;
    }
}
