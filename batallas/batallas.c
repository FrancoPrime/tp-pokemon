#include "batallas.h"
#include <string.h>

int funcion_batalla_1(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->velocidad > segundo->velocidad) ? GANO_PRIMERO : GANO_SEGUNDO);
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->defensa > segundo->defensa) ? GANO_PRIMERO : GANO_SEGUNDO);
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->ataque > segundo->ataque) ? GANO_PRIMERO : GANO_SEGUNDO);
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((strcmp(primero->nombre, segundo->nombre) > 0) ? GANO_PRIMERO : GANO_SEGUNDO);
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
  pokemon_t* primero = (pokemon_t*)pkm_1;
  pokemon_t* segundo = (pokemon_t*)pkm_2;
  return((primero->ataque > segundo->defensa) ? GANO_PRIMERO : GANO_SEGUNDO);
}
