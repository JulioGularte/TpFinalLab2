#ifndef EMPLEADOSLABORATORIO_H_INCLUDED
#define EMPLEADOSLABORATORIO_H_INCLUDED
typedef struct
{
    char dni[30];
    int baja;
    char NyA[40];
    char usuario[20];
    char clave[20];
    char perfil[20];
}empleados_laboratorio;

typedef struct{
    empleados_laboratorio empleado;
    struct nodo_lista* sig;
}nodo_lista;

int loguear (char archivo[]);
void menu_opciones_gerarquia (int perfil,char archivo[]);
int validar_perfil_empleado (char archivo[],char usuario[],char clave[]);  ///retorna 0-1-2-3 o -1 dendinedo tipo de usuario
empleados_laboratorio comprobar_coincidencia (char archivo[],char usuario[],char clave[]);///recibe el archivo de empleados y devuelve si tiene coincidencia
int comparar_perfil (empleados_laboratorio usuario); ///retorna 1-2-3 segun el perfil del usuario
empleados_laboratorio crear_empleado (char archivo[]); ///crear usuario (solo el admin supremo puede cargarlo)
int verificar_empleado_duplicado_usuario (char archivo[],char usuario[]); /// 1o0 si encuentra duplicado o no
int verificar_empleado_duplicado_DNI (char archivo[],char dni[]); /// 1o0 si encuentra duplicado o no

void mostrar_empleado (empleados_laboratorio aux,int perfil);  ///mostrar empleado
void mostrar_empleados_en_archivo (char archivo[],int perfil);  ///muestra todos los empleados

void cargar_empleado_to_archivo (char archivo[]);
nodo_lista* agregar_al_final_ordenado_nya(nodo_lista*lista, empleados_laboratorio dato);
nodo_lista* pasar_archivo_to_lista(char archivo[]); ///pasa todos los datos a una lista

void buscar_empleado_en_archivo_DNI(char archivo[],int perfil, nodo_lista* lista);///solo busca coincidencia con dni
empleados_laboratorio modificar_empleado (empleados_laboratorio dato,char archivo[]);

nodo_lista* agregar_al_final (nodo_lista* lista, empleados_laboratorio dato);
nodo_lista* crear_nodo_lista (empleados_laboratorio dato);
void swicherAdmin (int opcion,int perfil,char archivo[]);
#endif // EMPLEADOSLABORATORIO_H_INCLUDED
