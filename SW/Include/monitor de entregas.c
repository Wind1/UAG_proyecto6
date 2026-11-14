#include <stdio.h>
#include "monitor_de_entregas.h"

/* --- Funciones auxiliares internas de fecha --- */

static int es_bisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

static int dias_del_mes(int mes, int anio) {
    int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && es_bisiesto(anio)) {
        return 29;
    }
    if (mes >= 1 && mes <= 12) {
        return dias[mes];
    }
    return 0;
}

static long fecha_a_dias(struct Fecha f) {
    long total = f.dia;
    for (int y = 1; y < f.anio; y++) {
        total += es_bisiesto(y) ? 366 : 365;
    }
    for (int m = 1; m < f.mes; m++) {
        total += dias_del_mes(m, f.anio);
    }
    return total;
}

/* --- Implementacion de monitor_de_entregas.h --- */

int diferencia_dias(struct Fecha desde, struct Fecha hasta) {
    return (int)(fecha_a_dias(hasta) - fecha_a_dias(desde));
}

int esta_por_vencer(struct Tarea t, struct Fecha hoy, int dias_limite) {
    /* En datos_de_tareas.h: 0 = Pendiente, 1 = Completada */
    if (t.estado != 0) {
        return 0;
    }
    int dias = diferencia_dias(hoy, t.fecha_entrega);
    return (dias <= dias_limite) ? 1 : 0;
}

int mostrar_tareas_proximas(struct Tarea agenda[], int total, struct Fecha hoy, int dias_limite) {
    struct Tarea filtradas[MAX_TAREAS];
    int encontrados = 0;

    for (int i = 0; i < total; i++) {
        if (esta_por_vencer(agenda[i], hoy, dias_limite)) {
            filtradas[encontrados++] = agenda[i];
        }
    }

    if (encontrados == 0) {
        return 0;
    }

    /* Ordenar por prioridad: 1 (Alta) va antes que 2 (Media) y 3 (Baja) */
    for (int i = 0; i < encontrados - 1; i++) {
        for (int j = 0; j < encontrados - i - 1; j++) {
            if (filtradas[j].prioridad > filtradas[j + 1].prioridad) {
                struct Tarea temp = filtradas[j];
                filtradas[j] = filtradas[j + 1];
                filtradas[j + 1] = temp;
            }
        }
    }

    printf("\n=== ALERTAS: TAREAS PROXIMAS / POR VENCER ===\n");
    imprimir_encabezado();
    for (int i = 0; i < encontrados; i++) {
        int dias = diferencia_dias(hoy, filtradas[i].fecha_entrega);
        imprimir_tarea(filtradas[i]);
        if (dias < 0) {
            printf("   -> ALERTA: Vencida hace %d dia(s)\n", -dias);
        } else if (dias == 0) {
            printf("   -> ALERTA: Vence HOY\n");
        } else {
            printf("   -> ALERTA: Faltan %d dia(s)\n", dias);
        }
    }

    return encontrados;
}

int mostrar_tareas_vencidas(struct Tarea agenda[], int total, struct Fecha hoy) {
    int encontrados = 0;

    for (int i = 0; i < total; i++) {
        if (agenda[i].estado == 0 && diferencia_dias(hoy, agenda[i].fecha_entrega) < 0) {
            if (encontrados == 0) {
                printf("\n=== TAREAS PENDIENTES VENCIDAS ===\n");
                imprimir_encabezado();
            }
            imprimir_tarea(agenda[i]);
            encontrados++;
        }
    }

    return encontrados;
}

int editar_fecha_entrega(struct Tarea agenda[], int total, int id) {
    int indice = -1;

    for (int i = 0; i < total; i++) {
        if (agenda[i].id_tarea == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        return 0; /* No existe el ID */
    }

    struct Fecha nueva_fecha;
    printf("Ingrese la nueva fecha de entrega para la tarea [ID %d] (DD MM AAAA): ", id);
    if (scanf("%d %d %d", &nueva_fecha.dia, &nueva_fecha.mes, &nueva_fecha.anio) != 3) {
        while (getchar() != '\n');
        return -1;
    }

    /* Validamos tanto con fecha_valida como con los dias exactos del mes */
    if (!fecha_valida(nueva_fecha) || nueva_fecha.dia > dias_del_mes(nueva_fecha.mes, nueva_fecha.anio)) {
        return -1; /* Fecha incorrecta */
    }

    agenda[indice].fecha_entrega = nueva_fecha;
    return 1;
}