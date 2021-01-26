#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <stdlib.h>
#include <stdbool.h>
#include "arbol/abb.h"
#include "lista/lista.h"
#include "heap/heap.h"

#define MAX_NOMBRE 100

typedef struct pokemon{
  char nombre[MAX_NOMBRE];
  int velocidad;
  int defensa;
  int ataque;
} pokemon_t;

typedef struct entrenador{
  char nombre[MAX_NOMBRE];
  lista_t* pokemones;
} entrenador_t;

typedef struct gimnasio{
  char nombre[MAX_NOMBRE];
  int dificultad;
  int id_puntero_funcion;
  entrenador_t lider;
  lista_t* entrenadores;
} gimnasio_t;

typedef struct personaje{
  char nombre[MAX_NOMBRE];
  lista_t* pokemones_combate;
  abb_t* pokemones_reserva;
} personaje_t;

typedef struct partida{
  heap_t* gimnasios;
  personaje_t personaje;
} partida_t;

void jugar();


#endif
