#include <stdio.h>
#include "menu_gimnasio.h"

#define VER_ENTRENADOR 'E'
#define VER_GIMNASIO_ACTUAL 'G'
#define CAMBIAR_POKEMONES 'C'
#define BATALLAR 'B'

bool imprimir_pokemon_lista(void* pokemon, void* contexto){
  pokemon_t* pkm = (pokemon_t*)pokemon;
  printf("\t-%s Vel: %i Def: %i Att: %i\n", pkm->nombre, pkm->velocidad, pkm->defensa, pkm->ataque);
  return true;
}

void mostrar_entrenador(partida_t* partida){
  system("clear");
  printf("|======| Personaje Principal |========|\n\n");
  printf("|*|Información:\n");
  printf("\tNombre: %s\n", partida->personaje.nombre);
  printf("|*|Pokemones de combate:\n");
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, NULL);
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
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
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
}

void menu_gimnasio(partida_t* partida){
  printf("|====| Bienvenido al menú de gimnasio |======|\n\n");
  printf("|*| Ingrese alguna de las siguientes opciones:\n");
  printf("\tE: Ver al entrenador principal junto a sus pokemones\n");
  printf("\tG: Ver información del gimnasio actual\n");
  printf("\tC: Cambiar los pokemones de batalla\n");
  printf("\tB: Realizar la proxima batalla planificada\n");
  char caracter = (char)getchar();
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
      //
    break;
    default:
      system("clear");
      menu_gimnasio(partida);
    break;
  }
}
