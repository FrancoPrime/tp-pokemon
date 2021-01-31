#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#define EXITO 0
#define ERROR -1

//Devuelve el nodo en la posicion indicada, donde 0 es el primer
//elemento.
//Si no existe dicha posicion devuelve NULL.
nodo_t* lista_nodo_en_posicion(lista_t* lista, size_t posicion){
  if(!lista || lista->cantidad < posicion)
    return NULL;
  nodo_t* nodo_actual = lista->nodo_inicio;
  size_t indice=0;
  while(indice < posicion)
  {
    nodo_actual = nodo_actual->siguiente;
    indice++;
  }
  return nodo_actual;
}

//Pre: -
//Post: Si puede crear la lista devuelve un puntero a ella
lista_t* lista_crear(){
  lista_t* lista = malloc(sizeof(lista_t));
  if(!lista)
    return NULL;
  lista->nodo_inicio = NULL;
  lista->nodo_fin = NULL;
  lista->cantidad = 0;
  return lista;
}

//Inserta un elemento al principio de la lista.
//Devuelve EXITO si pudo insertar o ERROR si no pudo.
int lista_insertar_inicio(lista_t* lista, void* elemento){
  if(!lista)
    return ERROR;
  nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
  if(!nodo_nuevo)
    return ERROR;
  nodo_nuevo->siguiente = lista->nodo_inicio;
  nodo_nuevo->elemento = elemento;
  lista->nodo_inicio = nodo_nuevo;
  if(lista->cantidad == 0)
    lista->nodo_fin = nodo_nuevo;
  lista->cantidad += 1;
  return EXITO;
}

//Inserta un elemento al final de la lista.
//Devuelve EXITO si pudo insertar o ERROR si no pudo.
int lista_insertar(lista_t* lista, void* elemento){
  if(!lista)
    return ERROR;
  if(lista->cantidad == 0)
    return lista_insertar_inicio(lista, elemento);
  nodo_t* nodo_nuevo = calloc(1,sizeof(nodo_t));
  if(!nodo_nuevo)
    return ERROR;
  nodo_nuevo->siguiente = NULL;
  nodo_nuevo->elemento = elemento;
  nodo_t* nodito = lista->nodo_fin;
  nodito->siguiente = nodo_nuevo;
  lista->nodo_fin = nodo_nuevo;
  lista->cantidad += 1;
  return EXITO;
}

//Inserta un elemento en la posicion indicada, donde 0 es insertar
//como primer elemento y 1 es insertar luego del primer elemento.
//En caso de no existir la posicion indicada, lo inserta al final.
//Devuelve EXITO si pudo insertar o ERROR si no pudo.
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
  if(!lista)
    return ERROR;
  if(posicion == 0)
    return lista_insertar_inicio(lista, elemento);
  if(lista->cantidad < posicion+1)
    return lista_insertar(lista, elemento);
  nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
  if(!nodo_nuevo)
    return ERROR;
  nodo_t* nodo_anterior = lista_nodo_en_posicion(lista, posicion-1);
  nodo_nuevo->siguiente = nodo_anterior->siguiente;
  nodo_nuevo->elemento = elemento;
  nodo_anterior->siguiente = nodo_nuevo;
  lista->cantidad += 1;
  return EXITO;
}

//Quita de la lista el elemento que se encuentra en la ultima posición.
//Devuelve EXITO si pudo eliminar o ERROR si no pudo.
int lista_borrar(lista_t* lista){
  if(lista_vacia(lista))
    return ERROR;
  if(lista->cantidad == 1)
  {
    free(lista->nodo_fin);
    lista->nodo_fin = NULL;
    lista->nodo_inicio = NULL;
    lista->cantidad = 0;
  }
  else
  {
    nodo_t* nodo_anterior = lista_nodo_en_posicion(lista, (lista->cantidad)-2);
    nodo_anterior->siguiente = NULL;
    free(lista->nodo_fin);
    lista->nodo_fin = nodo_anterior;
    lista->cantidad -= 1;
  }
  return EXITO;
}

//Quita de la lista el elemento que se encuentra en la posición
//indicada, donde 0 es el primer elemento.
//En caso de no existir esa posición se intentará borrar el último
//elemento.
//Devuelve EXITO si pudo eliminar o ERROR si no pudo.
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista)
    return ERROR;
  if(lista->cantidad <= posicion+1 || lista->cantidad == 1)
    return lista_borrar(lista);
  if(posicion == 0)
  {
    nodo_t* auxiliar = lista->nodo_inicio;
    lista->nodo_inicio = lista->nodo_inicio->siguiente;
    free(auxiliar);
  }
  else
  {
    nodo_t* nodo_anterior = lista_nodo_en_posicion(lista, posicion-1);
    nodo_t* auxiliar = nodo_anterior->siguiente;
    nodo_anterior->siguiente = auxiliar->siguiente;
    free(auxiliar);
  }
  lista->cantidad -= 1;
  return EXITO;
}

//Devuelve el elemento en la posicion indicada, donde 0 es el primer
//elemento.
//Si no existe dicha posicion devuelve NULL.
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
  if(!lista || lista->cantidad < posicion+1)
    return NULL;
  nodo_t* nodo_actual = lista->nodo_inicio;
  size_t indice=0;
  while(indice < posicion)
  {
    nodo_actual = nodo_actual->siguiente;
    indice++;
  }
  return nodo_actual->elemento;
}

//Devuelve el último elemento de la lista o NULL si la lista se
//encuentra vacía.
void* lista_ultimo(lista_t* lista){
  if(lista_vacia(lista))
    return NULL;
  return lista->nodo_fin->elemento;
}

//Devuelve true solo si la lista está vacía
bool lista_vacia(lista_t* lista){
  if(!lista)
    return true;
  return (lista->cantidad == 0);
}

//Devuelve la cantidad de elementos almacenados en la lista.
//o 0 si la lista no existe
size_t lista_elementos(lista_t* lista){
  if(!lista)
    return 0;
  return (lista->cantidad);
}

//Apila un elemento.
//Devuelve 0 si pudo o -1 en caso contrario.
int lista_apilar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

//Desapila un elemento.
//Devuelve EXITO si pudo desapilar o ERROR si no pudo.
int lista_desapilar(lista_t* lista){
  return lista_borrar(lista);
}

//Devuelve el elemento en el tope de la pila o NULL
//en caso de estar vacía.
void* lista_tope(lista_t* lista){
  return lista_ultimo(lista);
}

//Encola un elemento.
//Devuelve EXITO si pudo encolar o ERROR si no pudo.
int lista_encolar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

//Desencola un elemento.
//Devuelve 0 si pudo desencolar o -1 si no pudo.
int lista_desencolar(lista_t* lista){
  return lista_borrar_de_posicion(lista, 0);
}

//Devuelve el primer elemento de la cola o NULL en caso de estar
//vacía.
void* lista_primero(lista_t* lista){
  if(lista_vacia(lista))
    return NULL;
  return lista->nodo_inicio->elemento;
}

//Pre: Recibe un puntero a una lista
//Post: Libera el bloque de memoria al que apunta
void lista_destruir(lista_t* lista){
  if(!lista)
    return;
  while(lista->cantidad > 0)
  {
    lista_borrar_de_posicion(lista, 0);
  }
  free(lista);
}

//Crea un iterador para una lista.
//Al momento de la creación, el iterador queda listo para devolver el
//primer elemento utilizando lista_iterador_elemento_actual.
//Devuelve el puntero al iterador creado o NULL en caso de error.
lista_iterador_t* lista_iterador_crear(lista_t* lista){
  if(!lista)
    return NULL;
  lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
  if(!iterador)
    return NULL;
  iterador->lista = lista;
  iterador->corriente = lista->nodo_inicio;
  return iterador;
}

//Devuelve true si hay mas elementos sobre los cuales iterar o false
//si no hay mas.
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
  if(!iterador)
    return false;
  return (iterador->corriente != NULL);
}

//Avanza el iterador al siguiente elemento.
//Devuelve true si pudo avanzar el iterador o false en caso de
//que no queden elementos o en caso de error.
bool lista_iterador_avanzar(lista_iterador_t* iterador){
  if(!iterador || iterador->corriente == NULL)
    return false;
  iterador->corriente = iterador->corriente->siguiente;
  return (iterador->corriente != NULL);
}

//Devuelve el elemento actual del iterador o NULL en caso de que no
//exista dicho elemento o en caso de error.
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
  if(!iterador || !(iterador->corriente))
    return NULL;
  return iterador->corriente->elemento;
}

//Libera la memoria reservada por el iterador.
void lista_iterador_destruir(lista_iterador_t* iterador){
  if(!iterador)
    return;
  free(iterador);
}

//Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
//la misma. Dicha función puede devolver true si se deben seguir recorriendo
//elementos o false si se debe dejar de iterar elementos.
//La función retorna la cantidad de elementos iterados o 0 en caso de error.
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
  if(lista_vacia(lista) || funcion == NULL)
    return 0;
  nodo_t* nodo_actual = lista->nodo_inicio;
  size_t indice = 0;
  bool seguir_recorriendo=true;
  while(nodo_actual != NULL && seguir_recorriendo)
  {
    seguir_recorriendo = funcion(nodo_actual->elemento, contexto);
    nodo_actual = nodo_actual->siguiente;
    indice++;
  }
  return indice;
}
