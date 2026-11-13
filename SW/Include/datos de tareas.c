#include <stdio.h>
#include "datos_de_tareas.h"

int total_tareas = 0;

int fecha_valida(struct Fecha f) {
    if (f.dia < 1 || f.dia > 31 || f.mes < 1 || f.mes > 12 || f.anio < 2000) {
        return 0;
    }
    return 1;
}

void imprimir_encabezado(void) {
    printf("\nID | Materia | Tarea | Fecha | Prioridad | Estado\n");
    printf("----------------------------------------------------\n");
}

/* Imprime UNA tarea asi no repetimos*/
void imprimir_tarea(struct Tarea t) {
    printf("%d | %s | %s | %d/%d/%d | ",
           t.id_tarea,
           t.materia,
           t.titulo,
           t.fecha_entrega.dia,
           t.fecha_entrega.mes,
           t.fecha_entrega.anio);

    if (t.prioridad == 1) {
        printf("Alta | ");
    } else if (t.prioridad == 2) {
        printf("Media | ");
    } else {
        printf("Baja | ");
    }

    if (t.estado == 1) {
        printf("Completada\n");
    } else {
        printf("Pendiente\n");
    }
}

int agregar_tarea(struct Tarea agenda[]) {

    // Revisar que haya espacio unu

    //Pedir los datos y guardarlos de forma pro

    printf("Nombre de la tarea (sin espacios, usa _): ");
    scanf("%s", agenda[total_tareas].titulo);

    printf("Materia (sin espacios, usa _): ");
    scanf("%s", agenda[total_tareas].materia);

    printf("Descripcion (sin espacios, usa _): ");
    scanf("%s", agenda[total_tareas].descripcion);

    printf("Dia de entrega (1-31): ");
    scanf("%d", &agenda[total_tareas].fecha_entrega.dia);

    printf("Mes de entrega (1-12): ");
    scanf("%d", &agenda[total_tareas].fecha_entrega.mes);

    printf("Anio de entrega (ejemplo 2026): ");
    scanf("%d", &agenda[total_tareas].fecha_entrega.anio);

    printf("Prioridad (1 = Alta, 2 = Media, 3 = Baja): ");
    scanf("%d", &agenda[total_tareas].prioridad);

    if (fecha_valida(agenda[total_tareas].fecha_entrega) == 0 ||
        agenda[total_tareas].prioridad < 1 ||
        agenda[total_tareas].prioridad > 3) {
        printf("Formato de fecha o prioridad incorrecto. La tarea no se guardo.\n");
        return 0;
    }

    agenda[total_tareas].id_tarea = total_tareas + 1;
    agenda[total_tareas].estado = 0;
    total_tareas++;

    printf("Tarea registrada correctamente en el sistema.\n");
    return 1;
}

void mostrar_tareas(struct Tarea agenda[], int modo) {
    int i;
    int mostradas = 0;

    imprimir_encabezado();

    for (i = 0; i < total_tareas; i++) {

        if (modo == 1 || agenda[i].estado == 0) {
            imprimir_tarea(agenda[i]);
            mostradas++;
        }
    }

    if (mostradas == 0) {
        printf("No hay tareas para mostrar.\n");
    }
}

int marcar_completada(struct Tarea agenda[], int id) {
    int i;

    for (i = 0; i < total_tareas; i++) {
        if (agenda[i].id_tarea == id) {
            agenda[i].estado = 1;
            return 1;
        }
    }
    return 0;
}