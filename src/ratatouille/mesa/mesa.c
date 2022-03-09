#include "mesa.h"

Mesa* mesa_init(int id_mesa, int capacidad)
{
    Mesa* mesa = malloc(sizeof(Mesa));
    Cliente** clientes = calloc(capacidad, sizeof(Cliente*));

    *mesa = (Mesa) {
        .id = id_mesa,
        .capacidad = capacidad,
        .cant_clientes = 0,
        .clientes = clientes,
        .llena = false
    };
    return mesa;

}

void sentar_cliente(Mesa* mesa, int id_cliente)
{
    if (mesa->llena)
    {
        return;
    }
    
    Cliente* cliente = cliente_init(id_cliente);
    for (int i = 0; i < mesa->capacidad; i++)
    {
        if (!mesa->clientes[i])
        {
            mesa->clientes[i] = cliente;
            mesa->cant_clientes += 1;
            return;
        }   
    }
}

Cliente* buscar_cliente(Mesa* mesa, int id_cliente)
{
    for (int i = 0; i < mesa->cant_clientes; i++)
    {
        if (mesa->clientes[i])
        {   
            Cliente* cliente = mesa->clientes[i];
            if (cliente->id == id_cliente)
            {
                return cliente;
            }
        }
    }
}

void estado_mesa(Mesa* mesa, FILE* output_file)
{
    fprintf(output_file, "ESTADO MESA %d\n", mesa->id);
    fprintf(output_file, "\t%d\n", mesa->capacidad);
    fprintf(output_file, "\t%d\n", (mesa->capacidad - mesa->cant_clientes));
    fprintf(output_file, "\tCLIENTES\n");
    
    for (int i = 0; i < mesa->capacidad; i++)
    {
        if (mesa->clientes[i])
        {
            fprintf(output_file, "\t\t%d\n", mesa->clientes[i]->id);
        }
        else
        {
            fprintf(output_file, "\t\t_\n");
        }
    }
    fprintf(output_file, "FIN ESTADO\n");
}

// void ingresar_anden(Anden* anden, Pasajero* pasajero)
// {
//     int largo;
//     Pasajero** fila_vieja;

//     //printf("meter pasajero al anden, ticket %i\n", pasajero-> ticket);

//     if (pasajero->ticket == 0){
//         fila_vieja = anden -> fila_premium;
//         largo = anden -> fila_premium_l;
//         if (puede_ingresar(anden -> tren) == true){
//             ingresar_pasajero_tren(anden -> tren, pasajero);
//             return;
//         }
//     }
//     else{
//         largo = anden -> fila_normal_l;
//         fila_vieja = anden -> fila_normal;
//     }
//     //printf("largo fila: %i, tipo: %i\n", largo, pasajero->ticket);
//     Pasajero** fila = calloc(largo + 1, sizeof(Pasajero*));
//     for(int i = 0; i < largo; i++){
//         fila[i] = fila_vieja[i];
//     }
//     fila[largo] = pasajero;

//     //printf("fila vieja: %p, fila nueva: %p \n", fila_vieja, fila);
//     free(fila_vieja);

//     if (pasajero->ticket == 0){
//         anden -> fila_premium = fila;
//         anden -> fila_premium_l +=1;
//         //printf("largo fila: %i, tipo: %i\n", anden -> fila_premium_l, pasajero->ticket);
//     }
//     else{
//         anden -> fila_normal = fila;
//         anden -> fila_normal_l += 1;
//         //printf("largo fila: %i, tipo: %i\n", anden -> fila_normal_l, pasajero->ticket);
//     }
// }

// void remover_pasajero_anden(Anden* anden, int n_vagon, int asiento, FILE *output_file){
//     Tren* tren = anden -> tren;
//     Vagon* vagon = (tren -> vagones)[n_vagon];
//     remover_pasajero_vagon(vagon, asiento, output_file);
//     tren->asiento_libre = true;
//     //liberar_asiento(tren);
// }

// void subir_pasajeros_fila(Anden* anden, int tipo){
//     Tren* tren = anden -> tren;
//     Pasajero* pasajero;
//     int* largo;
//     Pasajero*** fila;
//     if (tipo == 0){
//         largo = &(anden->fila_premium_l);
//         fila = &(anden->fila_premium);
//         //printf("\nlargo de la fila premium: %i\n", anden->fila_premium_l);
//     }
//     else{
//         largo = &(anden->fila_normal_l);
//         fila = &(anden->fila_normal);
//         //printf("\nlargo de la fila normal: %i\n", anden->fila_premium_l);
//     }
//     int pasajeros_desplazados = 0;
//     //printf("el largo de la fila es: %i\n", *largo);
//     while ((puede_ingresar(tren)) && ((*largo) > 0)) {
//         pasajero = (*fila)[pasajeros_desplazados];
//         //printf("\ningresado pasajero%i, pos: %i\n", pasajero->id, pasajeros_desplazados);
//         ingresar_pasajero_tren(tren, pasajero);
//         (*fila)[pasajeros_desplazados] = NULL;
//         pasajeros_desplazados += 1;
//         *largo -= 1;
//         //printf("\nlargo de la fila: %i\n", *largo);
//         }
//     if ((*largo) > 0){
//         for (int i = 0; i < (*largo); i++){
//             pasajero = (*fila)[pasajeros_desplazados + i];
//             //printf("relocando pasajero%i, pos%i a %i", pasajero->id, pasajeros_desplazados+i, i);
//             (*fila)[i] = pasajero;
//             (*fila)[pasajeros_desplazados + i] = NULL;
//         }

//     }
// }

// void bajar_pasajeros_tren(Anden* anden, int id_estacion){
//     Tren* tren = anden ->tren;
//     Pasajero* pasajero;
//     Vagon* vagon;

//     for (int id_vagon = 0; id_vagon < (tren ->n_vagones); id_vagon++){
//         vagon = (tren -> vagones)[id_vagon];
//         for (int id_asiento = 0; id_asiento < (vagon->n_asientos); id_asiento++){
//             pasajero = ((vagon ->asientos)[id_asiento]);
//             if (pasajero){
//                 if ((pasajero->destino) == id_estacion){
//                     free(pasajero);
//                     vagon ->asientos[id_asiento] = NULL;
//                 }
//             }
//         }
//     }
// }


void liberar_mesa(Mesa* mesa){

    for (int i = 0; i < mesa->capacidad; i++)
    {
        if (mesa->clientes[i])
        {
            liberar_cliente(mesa->clientes[i]);
        }
    }

    free(mesa->clientes);
    free(mesa);
}