#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED
typedef struct
{
    int nroPractica;
    char NombrePractica [30];
    int eliminado;
}Practica;

Practica crearStPractica ();
int contarPracticasEnArchivo();
void mostrarUnaPractica(Practica practica, int esAdmin);


#endif // PRACTICAS_H_INCLUDED
