#include <stdio.h>
#include "menu.h"
#include "datos_de_tareas.h"
#include "buscador_de_tareas.h"
#include "monitor_de_entregas.h"

#define DIAS_ALERTA 3

int main(void) {
    struct Tarea agenda[MAX_TAREAS];
    struct Fecha hoy;
    int opcion = 0;

    printf("========================================\n");
    printf("   BIENVENIDO AL SISTEMA DE ENTREGAS\n");
    printf("========================================\n");

    /* Pedir la fecha de hoy al iniciar */
    do {
        printf("Ingrese la fecha de hoy (DD MM AAAA): ");
        if (scanf("%d %d %d", &hoy.dia, &hoy.mes, &hoy.anio) != 3) {
            while (getchar() != '\n'); /* Limpiar buffer si ingresan letras */
            hoy.dia = 0;
        }
        if (!fecha_valida(hoy)) {
            printf("Fecha invalida. Intente de nuevo (anio >= 2000).\n\n");
        }
    } while (!fecha_valida(hoy));

    do {
        /* Mostrar alertas automaticas de tareas que vencen en 3 dias o menos */
        if (total_tareas > 0) {
            mostrar_tareas_proximas(agenda, total_tareas, hoy, DIAS_ALERTA);
        }

        mostrar_menu();
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1: /* Registrar nueva tarea */
                if (total_tareas < MAX_TAREAS) {
                    agregar_tarea(agenda);
                } else {
                    printf("La agenda esta llena (maximo %d tareas).\n", MAX_TAREAS);
                }
                break;

            case 2: { /* Submenu de visualizacion */
                int sub_op = 0;
                do {
                    mostrar_submenu_visualizacion();
                    if (scanf("%d", &sub_op) != 1) {
                        while (getchar() != '\n');
                        sub_op = 0;
                    }

                    switch (sub_op) {
                        case 1:
                            /* modo 1 = Ver todas (Pendientes y Completadas) */
                            mostrar_tareas(agenda, 1);
                            break;
                        case 2:
                            /* modo 0 = Ver solo Pendientes */
                            mostrar_tareas(agenda, 0);
                            break;
                        case 3:
                            if (mostrar_tareas_vencidas(agenda, total_tareas, hoy) == 0) {
                                printf("\nNo hay tareas pendientes vencidas.\n");
                            }
                            break;
                        case 4:
                            printf("Regresando al menu principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                            break;
                    }
                } while (sub_op != 4);
                break;
            }

            case 3: { /* Submenu de busqueda / filtrado */
                int sub_op = 0;
                do {
                    mostrar_submenu_busqueda();
                    if (scanf("%d", &sub_op) != 1) {
                        while (getchar() != '\n');
                        sub_op = 0;
                    }

                    if (sub_op == 1) {
                        char materia[30];
                        printf("Ingrese la materia a buscar (sin espacios, usa _): ");
                        scanf("%29s", materia);
                        buscar_por_materia(agenda, total_tareas, materia);
                    } else if (sub_op == 2) {
                        int prio;
                        printf("Ingrese la prioridad a buscar (1 = Alta, 2 = Media, 3 = Baja): ");
                        scanf("%d", &prio);
                        buscar_por_prioridad(agenda, total_tareas, prio);
                    } else if (sub_op != 3) {
                        printf("Opcion no valida.\n");
                    }
                } while (sub_op != 3);
                break;
            }

            case 4: { /* Marcar tarea como completada */
                int id;
                printf("Ingrese el ID de la tarea a marcar como completada: ");
                scanf("%d", &id);
                if (marcar_completada(agenda, id)) {
                    printf("Tarea [ID %d] marcada como completada.\n", id);
                } else {
                    printf("No se encontro ninguna tarea con el ID %d.\n", id);
                }
                break;
            }

            case 5: { /* Editar fecha de entrega */
                int id;
                printf("Ingrese el ID de la tarea cuya fecha desea editar: ");
                scanf("%d", &id);
                int res = editar_fecha_entrega(agenda, total_tareas, id);
                if (res == 1) {
                    printf("Fecha de entrega actualizada correctamente.\n");
                } else if (res == 0) {
                    printf("No existe ninguna tarea con el ID %d.\n", id);
                } else if (res == -1) {
                    printf("Error: La fecha ingresada es invalida.\n");
                }
                break;
            }

            case 6:
                printf("Saliendo del gestor de tareas...\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 6);

    return 0;
}