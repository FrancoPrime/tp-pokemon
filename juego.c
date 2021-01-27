#include <stdio.h>
#include "juego.h"


#define EXITO 0
#define ERROR -1

#define ACTUALIZAR_PERSONAJE 'E'
#define AGREGA_GIMNASIO 'A'
#define COMIENZA_PARTIDA_INTERACTIVA 'I'
#define SIMULA_PARTIDA 'S'

bool destructor_pokemon_lista(pokemon_t* pokemon){
  if(pokemon)
    free(pokemon);
  return true;
}

void destruir_pokemon(pokemon_t* pokemon){
  if(pokemon)
    free(pokemon);
}

int comparar_pokemones(pokemon_t* primero, pokemon_t* segundo){
  return(strcmp(primero->nombre, segundo->nombre));
}

void mostrar_mensaje_inicial(){
  printf("|-------| ¡Bienvenido a Aventura Pokemon! |-------|\n");
  printf("En este juego podrás poner a prueba tus habilidades como\n");
  printf("entrenador pokemon. Derrota los diversos gimnasios y obten\n");
  printf("a los pokemones mas fuertes para tu colección.\n\n");
}

void jugar(){
  mostrar_mensaje_inicial();
  partida_t partida;
  menu_inicio(&partida);
}
