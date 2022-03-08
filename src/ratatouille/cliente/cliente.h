#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../plato/plato.h"

typedef struct cliente
{
  int id;
  Plato* primer_plato;
  Plato* ultimo_plato;

} Cliente;

Cliente* cliente_init(int id);
void liberar_cliente(Cliente* cliente);