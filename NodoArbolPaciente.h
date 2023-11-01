#ifndef NODOARBOLPACIENTE_H_INCLUDED
#define NODOARBOLPACIENTE_H_INCLUDED
#include "Pacientes.h"
typedef struct _nodoArbolPaciente {
Paciente paciente;
struct _nodoArbolPaciente * izq;
struct _nodoArbolPaciente * der;
struct _nodoIngresos * listaIngresos;
}nodoArbolPaciente;


#endif // NODOARBOLPACIENTE_H_INCLUDED
