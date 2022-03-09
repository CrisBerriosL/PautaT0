#include "plato.h"

Plato* plato_init(int id, int precio)
{
  Plato* plato = malloc(sizeof(Plato));
  
  *plato = (Plato) {
    .id = id,
    .precio = precio,
    .prev = NULL,
    .next = NULL
  };
  return plato;
}

void imprimir_plato(Plato* plato, FILE* output_file)
{
  fprintf(output_file, "\t\t\t%d %d\n", plato->id, plato->precio);
  if (plato->next)
  {
    imprimir_plato(plato->next, output_file);
  }
}

void liberar_plato(Plato* plato)
{
  if (plato->next)
  {
    liberar_plato(plato->next);
  }
  
  free(plato);
}