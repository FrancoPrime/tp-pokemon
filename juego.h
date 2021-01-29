#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arbol/abb.h"
#include "lista/lista.h"
#include "heap/heap.h"

#define MAX_POKEMONES_COMBATE 6
#define MAX_NOMBRE 100
#define MAX_POKEMONES 200

#define EXITO 0
#define ERROR -1

#define ENTER '\n'
#define SALIR_PARTIDA 'X'
#define SALIR 0
#define JUGAR 1
#define SIMULAR 2

typedef struct pokemon{
  char nombre[MAX_NOMBRE];
  int velocidad;
  int defensa;
  int ataque;
} pokemon_t;

typedef struct entrenador{
  char nombre[MAX_NOMBRE];
  lista_t* pokemones;//Cola
} entrenador_t;

typedef struct gimnasio{
  char nombre[MAX_NOMBRE];
  int dificultad;
  int id_puntero_funcion;
  entrenador_t lider;
  lista_t* entrenadores; //Pila
} gimnasio_t;

typedef struct personaje{
  char nombre[MAX_NOMBRE];
  lista_t* pokemones_combate; //Cola
  abb_t* pokemones_reserva;
} personaje_t;

typedef struct partida{
  heap_t* gimnasios;
  personaje_t personaje;
} partida_t;

void jugar();
void destruir_pokemon(void* pokemon);
int comparar_pokemones(void* primero, void* segundo);
void destruir_gimnasio(void* gimnasio);
int comparar_gimnasios(void* primero, void* segundo);

#endif
