#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../cliente/cliente.h"

typedef struct mesa
{
  int id;
  int capacidad;
  int cant_clientes;
  Cliente** clientes;
  bool llena;

} Mesa;


Mesa* mesa_init(int id_mesa, int capacidad);
void sentar_cliente(Mesa* mesa, int id_cliente);
Cliente* buscar_cliente(Mesa* mesa, int id_cliente);
void estado_mesa(Mesa* mesa, FILE* output_file);
void generar_boleta(Mesa* mesa, FILE* output_file);
void liberar_mesa(Mesa* mesa);

// void ingresar_anden(Anden* anden, Pasajero* pasajero);
// void remover_pasajero_anden(Anden* anden, int n_vagon, int asiento, FILE *output_file);
// void subir_pasajeros_fila(Anden* anden, int tipo);
// void bajar_pasajeros_tren(Anden* anden, int id_estacion);
