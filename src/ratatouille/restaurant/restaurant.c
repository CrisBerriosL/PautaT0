#include "restaurant.h"

Restaurant* restaurant_init(int id_restaurant, int cant_mesas)
{
    Restaurant* restaurant = malloc(sizeof(Restaurant));

    *restaurant = (Restaurant) {
        .id = id_restaurant,
        .cant_mesas = cant_mesas,
        .mesas = calloc(cant_mesas, sizeof(Mesa*))
    };
    return restaurant;
}


// void imprimir_estacion(Anden*** estaciones, int id_estacion, int n_estaciones, FILE *output_file){

//     Anden* anden = estaciones[id_estacion][0];
//     Pasajero* pasajero;
//     bool continuar = true;
    
//     //printf("ESTACION %i\n", id_estacion);
//     fprintf(output_file, "ESTACION %i\n", id_estacion);
//     for(int id_anden = 0; continuar; id_anden += 1){
//         anden = estaciones[id_estacion][id_anden];
//         //printf("A%i", id_anden);
//         fprintf(output_file, "A%i", id_anden);
//         //printf("largo fila premium:%i, largo fila normal: %i", anden->fila_premium_l, anden->fila_normal_l);
//         for (int id_pasajero = 0 ; id_pasajero < (anden->fila_premium_l); id_pasajero++){
//             pasajero = (anden->fila_premium)[id_pasajero];
//             //printf(" %i-%i-%i", pasajero->id, pasajero->destino, pasajero->ticket);
//             fprintf(output_file, " %i-%i-%i", pasajero->id, pasajero->destino, pasajero->ticket);
            
//         }
//         for (int id_pasajero = 0; id_pasajero < (anden->fila_normal_l); id_pasajero++){
//             pasajero = (anden->fila_normal)[id_pasajero];
//             //printf(" %i-%i-%i", pasajero->id, pasajero->destino, pasajero->ticket);
//             fprintf(output_file, " %i-%i-%i", pasajero->id, pasajero->destino, pasajero->ticket);
//         }
//         //printf("\n");
//         fprintf(output_file, "\n");
//         if(anden->tren){
//             estado(anden->tren, output_file);
//         }
//         if (anden->ultimo){
//             continuar = 0;
//         }
        
//     }
// }

void liberar_restaurant(Restaurant* restaurant){

    for (int i = 0; i < restaurant->cant_mesas; i++)
    {
        liberar_mesa(restaurant->mesas[i]);
    }
    
    free(restaurant->mesas);
    free(restaurant);
}