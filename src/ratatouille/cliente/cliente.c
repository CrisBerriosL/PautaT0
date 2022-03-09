#include "cliente.h"

Cliente* cliente_init(int id)
{
  Cliente* cliente = malloc(sizeof(Cliente));

  *cliente = (Cliente) {
    .id = id,
    .primer_plato = NULL,
    .ultimo_plato = NULL
  };
  return cliente;
}

void crear_pedido(Cliente* cliente, Plato* plato)
{
  printf("Creando pedido...\n");
  if (cliente->primer_plato)
  {
    printf("Ya hay platos\n");
    cliente->ultimo_plato->next = plato;
    plato->prev = cliente->ultimo_plato;
    cliente->ultimo_plato = plato;
  }
  else
  { 
    printf("Primer plato\n");
    cliente->primer_plato = plato;
    cliente->ultimo_plato = plato;
  }
  printf("Pedido creado!\n");
}


void cancelar_pedido(Cliente* cliente)
{
  Plato* plato_eliminado = cliente->ultimo_plato;
  if (plato_eliminado->prev)
  {
    cliente->ultimo_plato = plato_eliminado->prev;
    cliente->ultimo_plato->next = NULL;
  }
  else
  {
    cliente->ultimo_plato = NULL;
    cliente->primer_plato = NULL;
  }
  liberar_plato(plato_eliminado);
}

void liberar_cliente(Cliente* cliente)
{ 
  if (cliente->primer_plato)
  {
    liberar_plato(cliente->primer_plato);
  }
  
  free(cliente);
}