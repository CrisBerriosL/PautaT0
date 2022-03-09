#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../plato/plato.h"

typedef struct cliente
{
  int id;
  int cuenta;
  int cant_platos;
  Plato* primer_plato;
  Plato* ultimo_plato;

} Cliente;

Cliente* cliente_init(int id);
void crear_pedido(Cliente* cliente, Plato* plato);
void cancelar_pedido(Cliente* cliente);
void imprimir_cliente(Cliente* cliente, FILE* output_file);
void liberar_cliente(Cliente* cliente);