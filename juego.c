#include "juego.h"
#include "menu_inicio.h"
#include "menu_gimnasio.h"

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
  lista_destruir(((entrenador_t*)(entrenador))->pokemones);
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
  system("clear");
  printf("|-------| ¡Bienvenido a Aventura Pokemon! |-------|\n");
  printf("En este juego podrás poner a prueba tus habilidades como\n");
  printf("entrenador pokemon. Derrota los diversos gimnasios y obten\n");
  printf("a los pokemones mas fuertes para tu colección.\n\n");
}

void inicializar_partida(partida_t* partida){
  heap_t* gimnasios = heap_crear(comparar_gimnasios, destruir_gimnasio);
  if(!gimnasios)
    return;
  partida->gimnasios = gimnasios;
  partida->personaje.pokemones_combate = lista_crear();
  if(!partida->personaje.pokemones_combate)
  {
    free(gimnasios);
    return;
  }
  partida->personaje.pokemones_reserva = arbol_crear(comparar_pokemones, destruir_pokemon);
  if(!partida->personaje.pokemones_reserva)
  {
    free(gimnasios);
    free(partida->personaje.pokemones_combate);
  }
}

void destruir_partida(partida_t* partida){
arbol_destruir(partida->personaje.pokemones_reserva);
lista_destruir(partida->personaje.pokemones_combate);
heap_destruir(partida->gimnasios);
}

void jugar(){
  mostrar_mensaje_inicial();
  partida_t partida;
  inicializar_partida(&partida);
  int accion = menu_inicio(&partida);
  system("clear");
  if(accion == JUGAR){
    menu_gimnasio(&partida);
  }
  else if(accion == SIMULAR){

  }
  destruir_partida(&partida);
}
