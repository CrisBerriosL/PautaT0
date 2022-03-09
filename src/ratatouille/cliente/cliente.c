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
  cliente->cuenta += plato->precio;
  cliente->cant_platos += 1;

  if (cliente->primer_plato)
  {
    cliente->ultimo_plato->next = plato;
    plato->prev = cliente->ultimo_plato;
    cliente->ultimo_plato = plato;
  }
  else
  { 
    cliente->primer_plato = plato;
    cliente->ultimo_plato = plato;
  }
}


void cancelar_pedido(Cliente* cliente)
{
  Plato* plato_eliminado = cliente->ultimo_plato;
  cliente->cuenta -= plato_eliminado->precio;
  cliente->cant_platos -= 1;

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


void imprimir_cliente(Cliente* cliente, FILE* output_file)
{
  fprintf(output_file, "\t\tPERSONA %d\n", cliente->id);
  if (cliente->primer_plato)
  {
    imprimir_plato(cliente->primer_plato, output_file);
  }
  fprintf(output_file, "\t\t%d\n", cliente->cuenta);
  fprintf(output_file, "\t\tFIN PERSONA\n");
}


void liberar_cliente(Cliente* cliente)
{ 
  if (cliente->primer_plato)
  {
    liberar_plato(cliente->primer_plato);
  }
  
  free(cliente);
}