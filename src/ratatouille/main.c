#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "restaurant/restaurant.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");


  /* Leemos la cantidad de restaurants y mesas por restaurant*/
  int n_restaurants;
  fscanf(input_file, "%d", &n_restaurants);

  int n_tables;
  int total_mesas = 0;

  Restaurant** restaurants = calloc(n_restaurants, sizeof(Restaurant*));

  for (int s = 0; s < n_restaurants; s++)
  {
    fscanf(input_file, "%d", &n_tables);

    /*  Creamos los restaurants con la cantidad de mesas dada */
    restaurants[s] = restaurant_init(s, n_tables);
    total_mesas += n_tables;
  }


  /* Leemos los eventos para instanciar cada mesa*/
  int id_restaurant, id_mesa, capacidad;

  /* String para guardar la instrucción actual*/
  char command[32];

  for (int i = 0; i < total_mesas; i++)
  {
    fscanf(input_file, "%s %d %d %d", command, &id_restaurant, &id_mesa, &capacidad);
    restaurants[id_restaurant]->mesas[id_mesa] = mesa_init(id_mesa, capacidad);
  }
  
  /* Leemos la cantidad de platos y los instanciamos */
  int n_dishes;
  fscanf(input_file, "%d", &n_dishes);
  Plato** platos = calloc(n_dishes, sizeof(Plato*));
  int id_plato, precio;

  for (int i = 0; i < n_dishes; i++)
  {
    fscanf(input_file, "%s %d %d", command, &id_plato, &precio);
    platos[i] = plato_init(id_plato, precio);
  }

  /* Empezamos a leer instrucciones */ 
  int n_commands;
  fscanf(input_file, "%d", &n_commands);
  
  for (int i = 0; i < n_commands; i++)
  {
    /* Leemos la instrucción */
    fscanf(input_file, "%s", command);

    /* A continuación debes implementar cada evento */
    if (string_equals(command, "CUSTOMER"))
    {
      int location_id, table_id, customer_id;
      fscanf(input_file, "%d %d %d", &location_id, &table_id, &customer_id);
      
      Mesa* mesa = restaurants[location_id]->mesas[table_id];
      sentar_cliente(mesa, customer_id);
    }
    else if (string_equals(command, "TABLE-STATUS"))
    { 
      int location_id, table_id;
      fscanf(input_file, "%d %d", &location_id, &table_id);

      Mesa* mesa = restaurants[location_id]->mesas[table_id];
      estado_mesa(mesa, output_file);
    }
    else if (string_equals(command, "ORDER-CREATE"))
    {
      int location_id, table_id, customer_id, item_id;
      fscanf(input_file, "%d %d %d %d", &location_id, &table_id, &customer_id, &item_id);

      int precio = platos[item_id]->precio;
      Plato* plato = plato_init(item_id, precio);
      Mesa* mesa = restaurants[location_id]->mesas[table_id];
      Cliente* cliente = buscar_cliente(mesa, customer_id);
      crear_pedido(cliente, plato);
    }
    else if (string_equals(command, "ORDER-CANCEL"))
    {
      int location_id, table_id, customer_id;
      fscanf(input_file, "%d %d %d", &location_id, &table_id, &customer_id);

      Mesa* mesa = restaurants[location_id]->mesas[table_id];
      Cliente* cliente = buscar_cliente(mesa, customer_id);
      cancelar_pedido(cliente);
    }
    else if (string_equals(command, "BILL-CREATE"))
    {
      int location_id, table_id;
      fscanf(input_file, "%d %d", &location_id, &table_id);

      Mesa* mesa = restaurants[location_id]->mesas[table_id];
      generar_boleta(mesa, output_file);
    }
  //   else if (string_equals(command, "PASAJERO"))
  //   {
  //      //printf("------------CALLEARON PASAJERO------------ \n");
  //     int station_id, platform_id, destination, category;
  //     fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &destination, &category);

  //     Anden* anden = estaciones[station_id][platform_id];
  //     Pasajero* nuevo_pasajero = pasajero_init(category, pasajeros_totales, destination);
  //     //printf("se creo el pasajero: %i\n", nuevo_pasajero->id);
  //     pasajeros_totales += 1;

  //     //printf("tren %p, anden %p (%i, %i)\n", anden -> tren, anden, station_id, platform_id);

  //     ingresar_anden(anden, nuevo_pasajero);


  //   }
  //   else if (string_equals(command, "REMOVER"))
  //   {
  //     //printf("------------CALLEARON REMOVER----------\n");
  //     int station_id, platform_id, car, seat;
  //     fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &car, &seat);



  //     Anden* anden = estaciones[station_id][platform_id];
  //     Tren* tren = anden -> tren;
  //     Vagon* vagon = tren -> vagones[car];

  //     //printf("Victima: %i\n", seat);

  //     //printf("pasajeros(%i):\n", vagon-> n_asientos);
  //     for (int i = 0; i < vagon-> n_asientos; i++){
  //       //printf("[%i]:%p,", i, (vagon->asientos)[i]);
  //     }
  //     //printf("\n");

  //     remover_pasajero_anden(anden, car, seat, output_file);

  //     //printf("pasajeros(%i):\n", vagon-> n_asientos);
  //     for (int i = 0; i < vagon-> n_asientos; i++){
  //       //printf("[%i]:%p,", i, (vagon->asientos)[i]);
  //     }
  //     //printf("\n");

  //     //printf("\n");
  //     subir_pasajeros_fila(anden, 0);

  //   }
  //   else if (string_equals(command, "SALIR"))
  //   {
  //     //printf("------------CALLEARON SALIR----------\n");
  //     int station_id, platform_id;
  //     fscanf(input_file, "%d %d", &station_id, &platform_id);

  //     Anden* anden = estaciones[station_id][platform_id];
  //     subir_pasajeros_fila(anden, 0); 
  //     subir_pasajeros_fila(anden, 1);//agregado luego
  //     tren_viajando = anden->tren;
  //     anden -> tren = NULL;
  //   }
  //   else if (string_equals(command, "LLEGAR"))
  //   {
  //     //printf("------------CALLEARON LLEGAR----------\n");
  //     int station_id, platform_id;
  //     fscanf(input_file, "%d %d", &station_id, &platform_id);

  //     //printf("LLEGAR ");
  //     fprintf(output_file, "LLEGAR ");

  //     Anden* anden = estaciones[station_id][platform_id];
  //     anden -> tren = tren_viajando;
  //     estado(tren_viajando, output_file);
  //     bajar_pasajeros_tren(anden, station_id);
  //     subir_pasajeros_fila(anden, 0); 
      
  //   }
  //   else if (string_equals(command, "DESAPARECER"))
  //   {
  //     //printf("------------CALLEARON DESAPARECER----------\n");
      
  //     //printf("DESAPARECER ");
  //     fprintf(output_file, "DESAPARECER ");
  //     estado(tren_viajando, output_file);
  //     tren_desaparecer(tren_viajando);

  //   }
  //   else if (string_equals(command, "SEPARAR"))
  //   {
  //     //printf("------------CALLEARON SEPARAR---------\n");
  //     int station_id_1, platform_id_1, station_id_2, platform_id_2;
  //     fscanf(input_file, "%d %d %d %d", &station_id_1, &platform_id_1, &station_id_2, &platform_id_2);

  //     Tren** trenes = separar_tren(tren_viajando, station_id_1, platform_id_1, station_id_2, platform_id_2, trenes_totales);
  //     trenes_totales += 1;

  //     estaciones[station_id_1][platform_id_1] -> tren = trenes[0];
  //     fprintf(output_file, "LLEGAR ");
  //     estado(trenes[0], output_file);
  //     bajar_pasajeros_tren(estaciones[station_id_1][platform_id_1], station_id_1);
  //     estaciones[station_id_2][platform_id_2] -> tren = trenes[1];
  //     fprintf(output_file, "LLEGAR ");
  //     estado(trenes[1], output_file);
  //     bajar_pasajeros_tren(estaciones[station_id_2][platform_id_2], station_id_2);
  //     free(trenes);
  //     subir_pasajeros_fila(estaciones[station_id_1][platform_id_1], 0);
  //     subir_pasajeros_fila(estaciones[station_id_2][platform_id_2], 0);
  //   }
  //   else if (string_equals(command, "ESTACION"))
  //   {
  //     int station_id;
  //     fscanf(input_file, "%d", &station_id);
  //     imprimir_estacion(estaciones, station_id, n_restaurants, output_file);


  //   }

  //   /* Leemos la siguiente instrucción */
  //   fscanf(input_file, "%s", command);
  }

  // for(int id_estacion = 0; id_estacion < n_restaurants; id_estacion++){
  //   imprimir_estacion(estaciones, id_estacion, n_restaurants, output_file);
  // }

  /*  Imprimimos el estado de todas las mesas   */
  for (int i = 0; i < n_restaurants; i++)
  {
    estado_restaurant(restaurants[i], output_file);
  }
  

  /*  Liberamos nuestras estructuras */
  for (int i = 0; i < n_restaurants; i++)
  {
    liberar_restaurant(restaurants[i]);
  }
  free(restaurants);

  for (int i = 0; i < n_dishes; i++)
  {
    liberar_plato(platos[i]);
  }
  free(platos);

  fclose(input_file);
  fclose(output_file);

  return 0;
}