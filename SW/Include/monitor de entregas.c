#include <stdio.h>
#include "monitor_de_entregas.h"

/* Devuelve 1 si el anio es bisiesto (febrero con 29 dias), 0 si no */
int es_bisiesto(int anio) {
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
        return 1;
    }
    return 0;
}

/* Convierte una fecha en "numero de dia" contando desde el anio 1.
   Con dos de estos numeros, restar da los dias de diferencia. */
int contar_dias(struct Fecha f) {
    int dias_antes_del_mes[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int anios_completos = f.anio - 1;
    int dias;

    /* 365 por cada anio completo + 1 por cada anio bisiesto que ya paso */
    dias = anios_completos * 365 + anios_completos / 4
           - anios_completos / 100 + anios_completos / 400;

    dias = dias + dias_antes_del_mes[f.mes - 1] + f.dia;

    /* si ya pasamos febrero de un anio bisiesto, falta sumar el 29 */
    if (f.mes > 2 && es_bisiesto(f.anio) == 1) {
        dias = dias + 1;
    }
    return dias;
}

int diferencia_dias(struct Fecha desde, struct Fecha hasta) {
    return contar_dias(hasta) - contar_dias(desde);
}

int esta_por_vencer(struct Tarea t, struct Fecha hoy, int dias_limite) {
    if (t.estado == 0 && diferencia_dias(hoy, t.fecha_entrega) <= dias_limite) {
        return 1;
    }
    return 0;
}

int mostrar_tareas_proximas(struct Tarea agenda[], int total, struct Fecha hoy, int dias_limite) {
    int i;
    int p;
    int dif;
    int encontradas = 0;

    /* Primero contamos cuantas hay */
    for (i = 0; i < total; i++) {
        if (esta_por_vencer(agenda[i], hoy, dias_limite) == 1) {
            encontradas++;
        }
    }

    /* Si no hay ninguna, no molestamos al usuario con una alerta */
    if (encontradas == 0) {
        return 0;
    }

    printf("\n*** ALERTA: tienes %d tarea(s) que vencen en %d dias o menos ***\n",
           encontradas, dias_limite);
    imprimir_encabezado();

    /* Prioridad 1 (Alta), luego 2 (Media), luego 3 (Baja) */
    for (p = 1; p <= 3; p++) {
        for (i = 0; i < total; i++) {
            if (esta_por_vencer(agenda[i], hoy, dias_limite) == 1 &&
                agenda[i].prioridad == p) {

                imprimir_tarea(agenda[i]);
                dif = diferencia_dias(hoy, agenda[i].fecha_entrega);

                if (dif < 0) {
                    printf("   >> VENCIDA hace %d dia(s)\n", -dif);
                } else if (dif == 0) {
                    printf("   >> VENCE HOY\n");
                } else if (dif == 1) {
                    printf("   >> Vence MANANA\n");
                } else {
                    printf("   >> Vence en %d dias\n", dif);
                }
            }
        }
    }
    return encontradas;
}

int mostrar_tareas_vencidas(struct Tarea agenda[], int total, struct Fecha hoy) {
    int i;
    int dif;
    int encontradas = 0;

    imprimir_encabezado();

    for (i = 0; i < total; i++) {
        dif = diferencia_dias(hoy, agenda[i].fecha_entrega);

        if (agenda[i].estado == 0 && dif < 0) {
            imprimir_tarea(agenda[i]);
            printf("   >> VENCIDA hace %d dia(s)\n", -dif);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("No hay tareas vencidas.\n");
    }
    return encontradas;
}

int editar_fecha_entrega(struct Tarea agenda[], int total, int id) {
    int i;
    struct Fecha nueva;

    for (i = 0; i < total; i++) {
        if (agenda[i].id_tarea == id) {

            printf("Nuevo dia (1-31): ");
            scanf("%d", &nueva.dia);
            printf("Nuevo mes (1-12): ");
            scanf("%d", &nueva.mes);
            printf("Nuevo anio (ejemplo 2026): ");
            scanf("%d", &nueva.anio);

            if (fecha_valida(nueva) == 0) {
                printf("Formato de fecha incorrecto. Intente con Dia/Mes/Anio.\n");
                return -1;
            }

            agenda[i].fecha_entrega = nueva;
            printf("La fecha de la tarea %d se actualizo correctamente.\n", id);
            return 1;
        }
    }
    return 0; /* no existe ese ID */
}