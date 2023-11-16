#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
typedef struct {
    char *titulo;
    int cantidadOpciones;
    int opcionSeleccionada;
    char **opciones;
}Menu;

int gestionarMenu(Menu menu);
int cambiarOpcionSeleccionada(int teclaPulsada, int cantidadOpciones, int opcionSeleccionada);
void pintarPantallaConMenu(Menu menu);
void mostrarPantallaConMenu(Menu menu);
void mostrarOpcion(char *opcion, int numeroDeOpcion, int opcionSeleccionada);



#endif // MENUS_H_INCLUDED
