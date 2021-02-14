#include "batallas.h"
#include "../juego.h"
#include <string.h>

//Pre: Recibe dos punteros a pokemones
//Post: Devuelve al ganador, el primero ganara solo si tiene mayor velocidad
int funcion_batalla_1(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->velocidad+primero->bonificacion > segundo->velocidad+segundo->bonificacion) ? GANO_PRIMERO : GANO_SEGUNDO);
}

//Pre: Recibe dos punteros a pokemones
//Post: Devuelve al ganador, el primero ganara solo si tiene mayor defensa
int funcion_batalla_2(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->defensa+primero->bonificacion > segundo->defensa+segundo->bonificacion) ? GANO_PRIMERO : GANO_SEGUNDO);
}

//Pre: Recibe dos punteros a pokemones
//Post: Devuelve al ganador, el primero ganara solo si tiene mayor ataque
int funcion_batalla_3(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->ataque+primero->bonificacion > segundo->ataque+segundo->bonificacion) ? GANO_PRIMERO : GANO_SEGUNDO);
}

//Pre: Recibe dos punteros a pokemones
//Post: Devuelve al ganador, el primero ganara solo si su nombre es mayor alfabeticamente
int funcion_batalla_4(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((strcmp(primero->nombre, segundo->nombre) > 0) ? GANO_PRIMERO : GANO_SEGUNDO);
}

//Pre: Recibe dos punteros a pokemones
//Post: Devuelve al ganador, el primero ganara solo si tiene mayor ataque que defensa el segundo
int funcion_batalla_5(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->ataque+primero->bonificacion > segundo->defensa+segundo->bonificacion) ? GANO_PRIMERO : GANO_SEGUNDO);
}
