#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "menu_inicio.h"

#define JUGAR 1
#define SIMULAR 2

#define EXITO 0
#define ERROR -1

bool destructor_pokemon_lista(void* pokemon, void* contexto){
  contexto = NULL;
  if(pokemon)
    free(pokemon);
  return true;
}

bool destructor_entrenador_lista(void* entrenador, void* contexto){
  contexto = NULL;
  if(entrenador)
    lista_con_cada_elemento(((entrenador_t*)(entrenador))->pokemones, destructor_pokemon_lista, NULL);
  free(entrenador);
  return true;
}

void destruir_pokemon(void* pokemon){
  if(pokemon)
    free(pokemon);
}

int comparar_pokemones(void* primero, void* segundo){
  if(!primero || !segundo)
    return 0;
  return(strcmp(((pokemon_t*)(primero))->nombre, ((pokemon_t*)(segundo))->nombre));
}

int comparar_gimnasios(void* primero, void* segundo){
  gimnasio_t* gim_1 = (gimnasio_t*)primero;
  gimnasio_t* gim_2 = (gimnasio_t*)segundo;
  return (int)(gim_2->dificultad - gim_1->dificultad);
}

void destruir_gimnasio(void* gimnasio){
  gimnasio_t* gim = (gimnasio_t*)gimnasio;

  if(gimnasio){
    lista_con_cada_elemento(gim->entrenadores, destructor_entrenador_lista, NULL);
    lista_destruir(gim->entrenadores);
    lista_con_cada_elemento(gim->lider.pokemones, destructor_pokemon_lista, NULL);
    lista_destruir(gim->lider.pokemones);
  }
  free(gimnasio);
}

void mostrar_mensaje_inicial(){
  printf("|-------| ¡Bienvenido a Aventura Pokemon! |-------|\n");
  printf("En este juego podrás poner a prueba tus habilidades como\n");
  printf("entrenador pokemon. Derrota los diversos gimnasios y obten\n");
  printf("a los pokemones mas fuertes para tu colección.\n\n");
}

void jugar(){
  mostrar_mensaje_inicial();
  partida_t partida;
  int accion = menu_inicio(&partida);
  if(accion == JUGAR){
    menu_gimnasio(&partida);
  }
  else if(accion == SIMULAR){

  }
}
