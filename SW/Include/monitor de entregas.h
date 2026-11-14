#ifndef MONITOR_DE_ENTREGAS_H
#define MONITOR_DE_ENTREGAS_H

/* Modulo: monitor_de_entregas
   Calcula cuanto falta para cada entrega, lanza alertas y cambia fechas.
   La fecha de hoy se recibe como parametro (el main la pide al usuario). */

#include "datos_de_tareas.h"

/* Cuantos dias hay de la fecha "desde" a la fecha "hasta".
   Positivo = falta tiempo, 0 = es el mismo dia, negativo = ya paso. */
int diferencia_dias(struct Fecha desde, struct Fecha hasta);

/* Devuelve 1 si la tarea esta pendiente y vence en "dias_limite" dias o menos
   (las ya vencidas tambien cuentan), 0 si no. */
int esta_por_vencer(struct Tarea t, struct Fecha hoy, int dias_limite);

/* RF 006: imprime con alerta las tareas pendientes que vencen pronto,
   ordenadas por prioridad (primero las Altas). No imprime nada si no hay.
   Devuelve cuantas encontro. */
int mostrar_tareas_proximas(struct Tarea agenda[], int total, struct Fecha hoy, int dias_limite);

/* Imprime las tareas pendientes cuya fecha ya paso.
   Devuelve cuantas encontro; 0 significa que no hay ninguna. */
int mostrar_tareas_vencidas(struct Tarea agenda[], int total, struct Fecha hoy);

/* RF 003: pide una fecha nueva y se la pone a la tarea con ese ID.
   Devuelve 1 si la cambio, 0 si no existe el ID, -1 si la fecha era incorrecta. */
int editar_fecha_entrega(struct Tarea agenda[], int total, int id);

#endif /* MONITOR_DE_ENTREGAS_H */