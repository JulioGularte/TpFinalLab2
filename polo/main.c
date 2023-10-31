#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
    char Apellido_Y_Nombre[40];
    int edad;
    int dni;
    char Direccion[30];
    char telefono[15];
    int Eliminado;
} paciente;

typedef struct
{
    int nro_Ingreso;
    char fecha_ingreso;
    char fecha_retiro;
    int dni;
    int matricula_profecional_solicitante;
    int Eliminado;
} ingreso;

typedef struct
{
    int nro_de_ingreso;
    int nro_practica;
    char Resultado[40];

} pracXingreso;

typedef struct nodo_lista_prac_ingreso
{
    pracXingreso practica;
    struct nodo_prac_ingreso *sig;
} nodo_lista_prac_ingreso;


typedef struct nodo_lista_ingresos
{
    ingreso ingre;
    struct nodo_lista_ingresos *siging;
    struct nodo_prac_ingreso *sigprac;
} nodo_lista_ingresos;

typedef struct nodoArbol
{
    paciente pasi;
    struct nodoArbol *izq;
    struct nodoArbol *der;
    struct nodo_lista_ingresos *sig;
} nodoArbol;



//************************
int main()
{
    printf("Hello world!\n");
    return 0;
}
//******************************

nodoArbol *inicArbol()
{
    return NULL;
}
nodo_lista_ingresos *iniclista_ingreso()
{
    return NULL;
}

nodo_lista_prac_ingreso *iniclista_prac_ingreso()
{
    return NULL;
}
nodoArbol *crear_nodo_arbol(paciente dati)
{
    nodoArbol *nuevo=(nodoArbol *)(sizeof(nodoArbol));
    nuevo->pasi=dati;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    nuevo->sig=NULL;//cabecera lista
    return nuevo;
}
nodoArbol *busca_Paciente(nodoArbol *arbol, paciente dati)
{
    nodoArbol *rta=inicArbol();
    if(arbol)
    {
        if(dati.dni==arbol->pasi.dni)
        {
            rta=arbol;
        }
        else
        {
            if(dati.dni > arbol->pasi.dni)
            {
                rta=busca_Paciente(arbol->der,dati);
            }
            else
            {
                rta=busca_Paciente(arbol->izq,dati);
            }
        }
    }
    return rta;
}

nodoArbol *insertar_paciente(nodoArbol *arbol, paciente dati)
{
    if(arbol==NULL)
    {
        nodoArbol *nuevo=crear_nodo_arbol(dati);
        nuevo->sig=iniclista_ingreso();
    }
    else
    {
        if(dati.dni>arbol->pasi.dni)
        {
            arbol=insertar_paciente(arbol->der,dati);
        }
        else
        {
            arbol=insertar_paciente(arbol->izq,dati);
        }
    }
    return arbol;
}
nodo_lista_ingresos *busca_ingreso_desde_Arbol(nodoArbol *arbol,int nroIngreso_Buscado)
{
    if(arbol)

    {
        nodo_lista_ingresos *seg;
        while(seg)
        {
            if(nroIngreso_Buscado>arbol->sig->ingre.nro_Ingreso)
            {
                arbol=busca_ingreso_desde_Arbol(arbol->der,nroIngreso_Buscado);
            }
            else
            {
                arbol=busca_ingreso_desde_Arbol(arbol->izq,nroIngreso_Buscado);
            }
            seg=seg->siging;
        }
    }
    return arbol ;
}
//*****************************************************

nodo_lista_ingresos *crear_nodo_lista_ingreso(ingreso dati)
{
    nodo_lista_ingresos *nuevo=(nodo_lista_ingresos *)malloc(sizeof(nodo_lista_ingresos));
    nuevo->ingre=dati;
    nuevo->siging= NULL;
    nuevo->sigprac=NULL;
    return nuevo;
}

nodo_lista_ingresos *agregar_ppio(nodo_lista_ingresos *lista_Ingresos, nodo_lista_ingresos *nuevo)
{
    if(lista_Ingresos==NULL)
    {
        lista_Ingresos=nuevo;
    }
    else
    {
        nuevo->siging=lista_Ingresos;
        lista_Ingresos=nuevo;
    }
    return lista_Ingresos;
}

nodo_lista_ingresos *busca_Ingreso(nodo_lista_ingresos *lista_Ingresos,int nroIngresoBuscado)
{
    nodo_lista_ingresos *seg;
    nodo_lista_ingresos *buscada;
    seg=lista_Ingresos;
    while(seg)
    {
        if(seg->ingre.nro_Ingreso==nroIngresoBuscado)
        {
            buscada=seg;
        }
        seg=seg->siging;
    }
    return buscada;
}
