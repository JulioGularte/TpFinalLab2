#ifndef NODOARBOLPACIENTE_H_INCLUDED
#define NODOARBOLPACIENTE_H_INCLUDED
#include "Pacientes.h"
#include "NodoPractica.h"
#include "NodoPxI.h"
typedef struct _nodoArbolPaciente
{
Paciente paciente;
struct _nodoArbolPaciente * izq;
struct _nodoArbolPaciente * der;
struct _nodoIngresos * listaIngresos;
}nodoArbolPaciente;

nodoArbolPaciente * inicArbol();
nodoArbolPaciente * crearNodoArbol(Paciente nuevoPaciente);
nodoArbolPaciente * cargarArbolOrdenadoDNI(nodoArbolPaciente * arbolPacientes, nodoArbolPaciente * nodoACargar);
nodoArbolPaciente * cargarArbolDesdeArchi(char archivoPacientes[], nodoArbolPaciente * arbolPacientes);
void mostrarNodoArbol(nodoArbolPaciente * nodoAMostrar);
void mostrarArbolPacientes(nodoArbolPaciente * arbolPacientes);
nodoArbolPaciente * buscarXDni (nodoArbolPaciente * arbol, int dni);
nodoArbolPaciente * bajaNodoArbol (nodoArbolPaciente * arbol, int dni);
void actualizarPacientesEnArchivo (nodoArbolPaciente * arbol);
void altaDeIngresoPaciente(nodoArbolPaciente * paciente, int * numeroUltimoIngreso, NodoPractica * listaDePracticas, NodoPxI * listaPxI);
#endif // NODOARBOLPACIENTE_H_INCLUDED
