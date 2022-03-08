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

void liberar_cliente(Cliente* cliente)
{ 
  if (cliente->primer_plato)
  {
    liberar_plato(cliente->primer_plato);
  }
  
  free(cliente);
}