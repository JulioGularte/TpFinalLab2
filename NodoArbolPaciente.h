#ifndef NODOARBOLPACIENTE_H_INCLUDED
#define NODOARBOLPACIENTE_H_INCLUDED
#include "NodoIngreso.h"
#include "Pacientes.h"
#include "NodoPxI.h"
#include "NodoPractica.h"
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
void mostrarNodoArbol(nodoArbolPaciente * nodoAMostrar);
void mostrarArbolPacientes(nodoArbolPaciente * arbolPacientes);
nodoArbolPaciente * buscarXDni (nodoArbolPaciente * arbol, int dni);
void bajaNodoArbol (nodoArbolPaciente * arbol, int dni);
void altaDeIngresoPaciente(nodoArbolPaciente * paciente, int numeroUltimoIngreso, NodoPractica * listaDePracticas);
nodoArbolPaciente * cargarArbolDesdeArchi(nodoArbolPaciente * arbolPacientes);


#endif // NODOARBOLPACIENTE_H_INCLUDED
