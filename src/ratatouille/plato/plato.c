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

void liberar_plato(Plato* plato)
{
  if (plato->next)
  {
    liberar_plato(plato->next);
  }
  
  free(plato);
}