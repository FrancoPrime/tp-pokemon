#include "heap.h"

#define ERROR -1
#define EXITO 0

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
  if(!comparador)
    return NULL;
  heap_t* heap = calloc(1, sizeof(heap_t));
  heap->comparador = comparador;
  if(destructor)
    heap->destructor = destructor;
  return heap;
}

int posicion_padre(int n){
  return(n-1)/2;
}

int posicion_hijo_derecho(int n){
  return 2*n+2;
}

int posicion_hijo_izquierdo(int n){
  return 2*n+1;
}

void swap(void** vector, int i, int j){
  void* aux = vector[i];
  vector[i] = vector[j];
  vector[j] = aux;
}

void sift_up(heap_t* heap, int n){
  if(n==0)
    return;
  int padre = posicion_padre(n);
  if(heap->comparador(heap->vector[n], heap->vector[padre]) >= 1){
    swap(heap->vector, n, padre);
    sift_up(heap, padre);
  }

}

int heap_insertar(heap_t* heap, void* elemento){
  if(!heap)
    return NULL;
  void* aux = realloc(heap->vector, sizeof(int)*(heap->tope+1));
  if(!aux)
    return ERROR;
  heap->vector = aux;
  heap->vector[heap->tope] = elemento;
  heap->tope++;
  sift_up(heap, heap->tope-1);
  return EXITO;
}

void sift_down(heap_t* heap, int n){

}

void* heap_extraer_raiz(heap_t* heap){
  if(!heap || heap->tope == 0)
    return NULL;
  void* elemento = heap->vector[0];
  heap->vector[0] = heap->vector[heap->tope-1];
  heap->tope--;
  if(heap->tope != 0)
    sift_down(heap, 0);

  return elemento;
}
