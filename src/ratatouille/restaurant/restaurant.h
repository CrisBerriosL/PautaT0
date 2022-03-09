#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../mesa/mesa.h"

typedef struct restaurant
{
  int id;
  int cant_mesas;
  Mesa** mesas;
} Restaurant;


Restaurant* restaurant_init(int id_restaurant, int cant_mesa);
void estado_restaurant(Restaurant* restaurant, FILE* output_file);
void liberar_restaurant(Restaurant* restaurant);

// void imprimir_estacion(Anden*** estaciones, int id_estacion, int n_estaciones, FILE *output_file);