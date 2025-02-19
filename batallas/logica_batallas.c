#include "logica_batallas.h"

//Pre: Recibe un puntero a pokemon
//Post: Aumenta sus atributos siempre que no excedan el maximo permitido
void aumentar_estadisticas(pokemon_t* pokemon){
  if(pokemon->bonificacion < MAX_PUNTOS_HABILIDADES)
    (pokemon->bonificacion)++;
}

//Pre: Recibe un puntero a pokemon
//Post: Imprime la información de dicho pokemon
void imprimir_pokemon(pokemon_t* pokemon){
  printf("|======================================|\n");
  printf("Información del pokemón\n");
  printf("\t|-| %s |-|\n", pokemon->nombre);
  printf("Velocidad: %i - Ataque: %i - Defensa: %i\n", pokemon->velocidad+pokemon->bonificacion, pokemon->ataque+pokemon->bonificacion, pokemon->defensa+pokemon->bonificacion);
  printf("|======================================|\n");
}

//Pre: Recibe un resultado
//Post: Imprime si ganó o perdió y espera que el usuario ingrese la letra N para continuar
void mostrar_resultado(int resultado){
  printf("Resultado: ");
  if(resultado == GANO_PRIMERO)
    printf("¡Has ganado!\n");
  else
    printf("Has perdido\n");
  printf("\nIngrese la letra N para continuar...\n");
  while(getchar() != 'N');
  system("clear");
}

//Pre: Recibe una cola con pokemones aliados, una con enemigos, el id de funcion a utilizar y si es una simulación
//Post: Realiza las batallas entre ambas colas mostrando los resultados según corresponda. Devuelve el resultado final.
int pelear_contra_entrenador(lista_t* aliados, lista_t* enemigos, int id_puntero, bool simulacion){
  int (*funcion_batalla[5])(void*, void*);
  funcion_batalla[0] = funcion_batalla_1;
  funcion_batalla[1] = funcion_batalla_2;
  funcion_batalla[2] = funcion_batalla_3;
  funcion_batalla[3] = funcion_batalla_4;
  funcion_batalla[4] = funcion_batalla_5;

  pokemon_t* pokemon_a_derrotar = lista_primero(enemigos);
  pokemon_t* pokemon_peleando = lista_primero(aliados);
  while(pokemon_a_derrotar != NULL && pokemon_peleando != NULL){
    int resultado = funcion_batalla[id_puntero-1]((void*)pokemon_peleando, (void*)pokemon_a_derrotar);
    if(!(simulacion)){
      printf("Tu pokemon:\n");
      imprimir_pokemon(pokemon_peleando);
      printf("Pokemon rival:\n");
      imprimir_pokemon(pokemon_a_derrotar);
      mostrar_resultado(resultado);
      system("clear");
    }
    if(resultado == GANO_PRIMERO){
      lista_desencolar(enemigos);
      pokemon_a_derrotar = lista_primero(enemigos);
      aumentar_estadisticas(pokemon_peleando);
    }else{
      lista_desencolar(aliados);
      pokemon_peleando = lista_primero(aliados);
    }
  }
  if(pokemon_a_derrotar == NULL)
    return GANO;
  return PERDIO;
}

//Pre: Recibe un puntero a una partida y uno a un gimnasio
//Post: Realiza los combates entre el personaje principal y los entrenadores del gimnasio. Devuelve el resultado
int pelear_contra_entrenadores(partida_t* partida, gimnasio_t* gimnasio){
    if(lista_vacia(gimnasio->entrenadores))
      return GANO;
    entrenador_t* entrenador = lista_tope(gimnasio->entrenadores);
    lista_t* cola_enemigos = lista_crear(NULL);
    size_t posicion=0;
    pokemon_t* pokemon = lista_elemento_en_posicion(entrenador->pokemones, posicion);
    while(pokemon != NULL){
      lista_encolar(cola_enemigos, pokemon);
      posicion++;
      pokemon = lista_elemento_en_posicion(entrenador->pokemones, posicion);
    }
    lista_t* cola_aliados = lista_crear(NULL);
    posicion=0;
    pokemon = lista_elemento_en_posicion(partida->personaje.pokemones_combate, posicion);
    while(pokemon != NULL){
      lista_encolar(cola_aliados, pokemon);
      posicion++;
      pokemon = lista_elemento_en_posicion(partida->personaje.pokemones_combate, posicion);
    }
    if(!partida->simulacion)
      printf("Pelea entre %s y %s:\n", partida->personaje.nombre, entrenador->nombre);
    int resultado = pelear_contra_entrenador(cola_aliados, cola_enemigos, gimnasio->id_puntero_funcion, partida->simulacion);
    lista_destruir(cola_enemigos);
    lista_destruir(cola_aliados);
    if(resultado == PERDIO)
      return PERDIO;
    lista_desapilar(gimnasio->entrenadores);
    return pelear_contra_entrenadores(partida, gimnasio);
}

//Pre: Recibe un puntero a la partida y uno a un gimnasio
//Post: Realiza el combate contra el lider y devuelve el resultado
int pelear_contra_lider(partida_t* partida, gimnasio_t* gimnasio){
  lista_t* cola_enemigos = lista_crear(NULL);
  size_t posicion=0;
  pokemon_t* pokemon = lista_elemento_en_posicion(gimnasio->lider.pokemones, posicion);
  while(pokemon != NULL){
    lista_encolar(cola_enemigos, pokemon);
    posicion++;
    pokemon = lista_elemento_en_posicion(gimnasio->lider.pokemones, posicion);
  }
  lista_t* cola_aliados = lista_crear(NULL);
  posicion=0;
  pokemon = lista_elemento_en_posicion(partida->personaje.pokemones_combate, posicion);
  while(pokemon != NULL){
    lista_encolar(cola_aliados, pokemon);
    posicion++;
    pokemon = lista_elemento_en_posicion(partida->personaje.pokemones_combate, posicion);
  }
  if(!partida->simulacion)
    printf("Pelea entre %s y %s:\n", partida->personaje.nombre, gimnasio->lider.nombre);
  int resultado = pelear_contra_entrenador(cola_aliados, cola_enemigos, gimnasio->id_puntero_funcion, partida->simulacion);
  lista_destruir(cola_enemigos);
  lista_destruir(cola_aliados);
  if(resultado == PERDIO)
    return PERDIO;
  return GANO;
}

//Pre: Recibe un puntero a una partida
//Post: Pelea contra el gimnasio correspondiente y devuelve el resultado de este intento.
int batallar(partida_t* partida){
  gimnasio_t* gimnasio = heap_raiz(partida->gimnasios);
  int resultado = pelear_contra_entrenadores(partida, gimnasio);
  if(resultado == PERDIO)
    return resultado;
  resultado = pelear_contra_lider(partida, gimnasio);
  if(resultado == PERDIO)
    return resultado;
  return GANO;
}
