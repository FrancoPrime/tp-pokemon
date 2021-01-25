#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, >1 si el primer elemento es mayor al
 * segundo o <-1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * se invoca al destructor pasandole el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
  void** vector;
  int tope;
  heap_comparador comparador;
  heap_liberar_elemento destructor;
} heap_t;

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

int heap_insertar(heap_t* heap, void* elemento);

void* heap_extraer_raiz(heap_t* heap);

#endif
