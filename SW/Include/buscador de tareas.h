#ifndef BUSCADOR_DE_TAREAS_H
#define BUSCADOR_DE_TAREAS_H

/* Filtra las tareas del arreglo y las imprimee */

#include "datos_de_tareas.h"

int buscar_por_materia(struct Tarea agenda[], int total, char materia[]);

int buscar_por_prioridad(struct Tarea agenda[], int total, int prioridad);

#endif