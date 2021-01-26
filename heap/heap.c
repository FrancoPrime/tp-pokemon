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
  if(!heap || n==0)
    return;
  int padre = posicion_padre(n);
  if(heap->comparador(heap->vector[n], heap->vector[padre]) > 0){
    swap(heap->vector, n, padre);
    sift_up(heap, padre);
  }

}

int heap_insertar(heap_t* heap, void* elemento){
  if(!heap)
    return ERROR;
  void* aux = realloc(heap->vector, sizeof(void*)*(size_t)(heap->tope+1));
  if(!aux)
    return ERROR;
  heap->vector = aux;
  heap->vector[heap->tope] = elemento;
  heap->tope++;
  sift_up(heap, heap->tope-1);
  return EXITO;
}

void sift_down(heap_t* heap, int n){
  if(!heap || n < 0)
    return;
  int pos_der = posicion_hijo_derecho(n);
  int pos_izq = posicion_hijo_izquierdo(n);
  int pos_mayor = pos_izq;
  if(pos_izq >= heap->tope)
    return;

  if(pos_der < heap->tope)
    if(heap->comparador(heap->vector[pos_der], heap->vector[pos_izq]) > 0)
      pos_mayor = pos_der;

  if(heap->comparador(heap->vector[n], heap->vector[pos_mayor]) < 0){
    swap(heap->vector, n, pos_mayor);
    sift_down(heap, pos_mayor);
  }
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

void* heap_raiz(heap_t* heap){
  if(!heap || heap->tope == 0)
    return NULL;
  return heap->vector[0];
}

int heap_cantidad(heap_t* heap){
  if(!heap)
    return 0;
  return heap->tope;
}

void heap_destruir(heap_t* heap){
  if(!heap)
    return;
  if(heap->tope == 0){
    free(heap->vector);
    free(heap);
    return;
  }
  void* elemento = heap_extraer_raiz(heap);
  if(heap->destructor)
    heap->destructor(elemento);
  heap_destruir(heap);
}
