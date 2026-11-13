#ifndef DATOS_DE_TAREAS_H
#define DATOS_DE_TAREAS_H


#define MAX_TAREAS 100

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Tarea {
    int id_tarea;
    char titulo[50];
    char materia[30];
    char descripcion[150];
    struct Fecha fecha_entrega;
    int prioridad; /* 1 = Alta, 2 = Media, 3 = Baja */
    int estado;    /* 0 = Pendiente, 1 = Completada */
};

extern int total_tareas;

int agregar_tarea(struct Tarea agenda[]);

void mostrar_tareas(struct Tarea agenda[], int modo);

int marcar_completada(struct Tarea agenda[], int id);

int fecha_valida(struct Fecha f);

void imprimir_encabezado(void);

void imprimir_tarea(struct Tarea t);

#endif