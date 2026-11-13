#include <stdio.h>
#include "menu.h"

void mostrar_menu(void) {
    printf("\n========================================\n");
    printf("      GESTOR DE TAREAS ACADEMICAS\n");
    printf("========================================\n");
    printf("1. Registrar nueva tarea\n");
    printf("2. Ver lista de tareas\n");
    printf("3. Buscar / Filtrar tareas\n");
    printf("4. Marcar tarea como completada\n");
    printf("5. Editar fecha de entrega\n");
    printf("6. Salir\n");
    printf("========================================\n");
    printf("Elija una opcion: ");
}

void mostrar_submenu_visualizacion(void) {
    printf("\n--- VISUALIZACION DE TAREAS ---\n");
    printf("1. Ver todas (Pendientes y Completadas)\n");
    printf("2. Ver solo tareas Pendientes\n");
    printf("3. Ver tareas Vencidas\n");
    printf("4. Regresar al menu principal\n");
    printf("Elija una opcion: ");
}

void mostrar_submenu_busqueda(void) {
    printf("\n--- BUSCAR / FILTRAR TAREAS ---\n");
    printf("1. Buscar por materia\n");
    printf("2. Buscar por prioridad\n");
    printf("3. Regresar al menu principal\n");
    printf("Elija una opcion: ");
}