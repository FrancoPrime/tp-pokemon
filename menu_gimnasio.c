#include <stdio.h>
#include "menu_gimnasio.h"

#define VER_ENTRENADOR 'E'
#define VER_GIMNASIO_ACTUAL 'G'
#define CAMBIAR_POKEMONES 'C'
#define BATALLAR 'B'

bool imprimir_pokemon_lista(void* pokemon, void* contexto){
  pokemon_t* pkm = (pokemon_t*)pokemon;
  printf("\t%li-%s Vel: %i Def: %i Att: %i\n", *(size_t*)contexto, pkm->nombre, pkm->velocidad, pkm->defensa, pkm->ataque);
  (*(size_t*)contexto)++;
  return true;
}

void mostrar_entrenador(partida_t* partida){
  system("clear");
  printf("|======| Personaje Principal |========|\n\n");
  printf("|*|Información:\n");
  printf("\tNombre: %s\n", partida->personaje.nombre);
  printf("|*|Pokemones de combate:\n");
  size_t id=1;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, (void*)&id);
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
  system("clear");
}

void mostrar_gimnasio(partida_t* partida){
  system("clear");
  gimnasio_t* actual = heap_raiz(partida->gimnasios);
  printf("|======| Gimnasio Actual |========|\n\n");
  printf("|*|Información:\n");
  printf("\tNombre: %s\n", actual->nombre);
  printf("\tDificultad: %i\n", actual->dificultad);
  printf("\tLider: %s\n", actual->lider.nombre);
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
  system("clear");
}

void seleccionar_slot_de_cambio(partida_t* partida, pokemon_t* pokemon){
  system("clear");
  printf("Has seleccionado a %s\n", pokemon->nombre);
  printf("Ahora escribe el numero de slot del pokemon por el cual deseas cambiarlo:\n");
  size_t id=1;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, (void*)&id);
  int slot;
  scanf("%i", &slot);
  if(slot < 0 || slot > MAX_POKEMONES_COMBATE)
    return;
  lista_borrar_de_posicion(partida->personaje.pokemones_combate, (size_t)(slot-1));
  lista_insertar_en_posicion(partida->personaje.pokemones_combate, (void*)pokemon, (size_t)(slot-1));
  system("clear");
  printf("Exito al cambiar pokemones\n");
}

void cambiar_pokemones(partida_t* partida){
  system("clear");
  printf("|======| Pokemones en reserva |========|\n");
  printf("Bienvenido a la pantalla de cambio de pokemones. Aqui abajo se encontrarán los pokemones\n");
  printf("que usted dispone para cambiar. Igrese el nombre del pokemon que desee agregar:\n");
  pokemon_t* pkms_reserva[MAX_POKEMONES];
  size_t cantidad = arbol_recorrido_inorden(partida->personaje.pokemones_reserva, (void**)pkms_reserva, MAX_POKEMONES);
  for(size_t i=0;i<cantidad;i++)
  {
    printf("-%s Vel:%i Def:%i Att:%i\n", pkms_reserva[i]->nombre, pkms_reserva[i]->velocidad, pkms_reserva[i]->defensa, pkms_reserva[i]->ataque);
  }
  printf("\nPokemon solicitado: ");
  char linea_leida[120];
  scanf("%s", linea_leida);

  pokemon_t pkm_cambio;
  strcpy(pkm_cambio.nombre, linea_leida);
  pokemon_t* pokemon_buscado = (pokemon_t*)arbol_buscar(partida->personaje.pokemones_reserva, (void*)&pkm_cambio);
  if(!pokemon_buscado)
  {
    system("clear");
    printf("No se encontró dicho pokemon\n\n");
    return;
  }
  seleccionar_slot_de_cambio(partida, pokemon_buscado);
}

void menu_gimnasio(partida_t* partida){
  printf("|====| Bienvenido al menú de gimnasio |======|\n\n");
  printf("|*| Ingrese alguna de las siguientes opciones:\n");
  printf("\tE: Ver al entrenador principal junto a sus pokemones\n");
  printf("\tG: Ver información del gimnasio actual\n");
  printf("\tC: Cambiar los pokemones de batalla\n");
  printf("\tB: Realizar la proxima batalla planificada\n");
  printf("\tX: Salir\n");
  char caracter;
  do
  {
    caracter = (char)getchar();
    switch(caracter)
    {
      case VER_ENTRENADOR:
        mostrar_entrenador(partida);
        menu_gimnasio(partida);
      break;
      case VER_GIMNASIO_ACTUAL:
        mostrar_gimnasio(partida);
        menu_gimnasio(partida);
      break;
      case CAMBIAR_POKEMONES:
        cambiar_pokemones(partida);
        menu_gimnasio(partida);
      break;
      case BATALLAR:
        int resultado = batallar(partida);
      break;
      case SALIR_PARTIDA:
      caracter = SALIR;
      break;
      default:
      caracter = ENTER;
      break;
    }
  } while(caracter == ENTER);
}
