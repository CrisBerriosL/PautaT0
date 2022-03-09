#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct plato
{
  int id;
  int precio;
  struct plato* prev;
  struct plato* next;

} Plato;

Plato* plato_init(int id, int precio);
void imprimir_plato(Plato* plato, FILE* output_file);
void liberar_plato(Plato* plato);