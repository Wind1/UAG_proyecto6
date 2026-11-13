#include <stdio.h>
#include <string.h>
#include "buscador_de_tareas.h"

int buscar_por_materia(struct Tarea agenda[], int total, char materia[]) {
    int i;
    int encontradas = 0;

    imprimir_encabezado();

    for (i = 0; i < total; i++) {
        if (strcmp(agenda[i].materia, materia) == 0) {
            imprimir_tarea(agenda[i]);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No se encontraron tareas de la materia %s.\n", materia);
    }
    return encontradas;
}

int buscar_por_prioridad(struct Tarea agenda[], int total, int prioridad) {
    int i;
    int encontradas = 0;

    imprimir_encabezado();

    for (i = 0; i < total; i++) {
        if (agenda[i].prioridad == prioridad) {
            imprimir_tarea(agenda[i]);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No se encontraron tareas con esa prioridad.\n");
    }
    return encontradas;
}