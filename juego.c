#include "juego.h"
#include "menus/menu_inicio.h"
#include "menus/menu_gimnasio.h"

//Destructor de entrenadores para listas
//Pre: Recibe un entrenador y un contexto
//Post: Libera la memoria asociada al entrenador
void destructor_entrenador(void* entrenador){
  if(entrenador)
    lista_destruir(((entrenador_t*)(entrenador))->pokemones);
  free(entrenador);
}

//Destructor de pokemones para arboles
//Pre: Recibe un puntero void* a un pokemon
//Post: Libera la memoria asociada al pokemon
void destruir_pokemon(void* pokemon){
  if(pokemon)
    free(pokemon);
}

//Pre: Recibe dos punteros a pokemones
//Post: Compara sus nombres y devuelve un valor > 0 si el primero es más grande alfabeticamente
//O < 0 en caso contrario
int comparar_pokemones(void* primero, void* segundo){
  if(!primero || !segundo)
    return 0;
  return(strcmp(((pokemon_t*)(primero))->nombre, ((pokemon_t*)(segundo))->nombre));
}

//Pre: Recibe dos punteros a gimnasios
//Pos: Compara sus dificultades, devuelve un valor > 0 si el primero tiene menos dificultad
//O < 0 en caso contrario
int comparar_gimnasios(void* primero, void* segundo){
  gimnasio_t* gim_1 = (gimnasio_t*)primero;
  gimnasio_t* gim_2 = (gimnasio_t*)segundo;
  return (int)(gim_2->dificultad - gim_1->dificultad);
}

//Pre: Recibe un puntero a un gimnasio
//Post: Libera toda la memoria asociada a dicho gimnasio
void destruir_gimnasio(void* gimnasio){
  gimnasio_t* gim = (gimnasio_t*)gimnasio;

  if(gimnasio){
    lista_destruir(gim->entrenadores);
    lista_destruir(gim->lider.pokemones);
  }
  free(gimnasio);
}

//Post: Imprime un mensaje de bienvenida
void mostrar_mensaje_inicial(){
  system("clear");
  printf(ANSI_COLOR_BLUE "|-------| ¡Bienvenido a Aventura Pokemon! |-------|\n");
  printf("En este juego podrás poner a prueba tus habilidades como\n");
  printf("entrenador pokemon. Derrota los diversos gimnasios y obten\n");
  printf("a los pokemones mas fuertes para tu colección.\n\n" ANSI_COLOR_RESET);
  printf("                                  ,'\n");
  printf("    _.----.        ____         ,'  _\\   ___    ___     ____\n");
  printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
  printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
  printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
  printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
  printf("    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
  printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
  printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
  printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
  printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
  printf("                                `'                            '-._|\n");
}

//Pre: Recibe un puntero a una partida
//Post: Crea los tdas y reserva la memoria necesaria para iniciar una partida.
void inicializar_partida(partida_t* partida){
  heap_t* gimnasios = heap_crear(comparar_gimnasios, destruir_gimnasio);
  if(!gimnasios)
    return;
  partida->gimnasios = gimnasios;
  partida->personaje.pokemones_combate = lista_crear(NULL);
  if(!partida->personaje.pokemones_combate)
  {
    free(gimnasios);
    return;
  }
  partida->personaje.pokemones_reserva = arbol_crear(comparar_pokemones, destruir_pokemon);
  if(!partida->personaje.pokemones_reserva)
  {
    free(gimnasios);
    free(partida->personaje.pokemones_combate);
  }
  partida->simulacion = false;
}

//Pre: Recibe un puntero a una partida
//Post: Destruye todos los tdas asociados a la partida y libera la memoria utilizada.
void destruir_partida(partida_t* partida){
  arbol_destruir(partida->personaje.pokemones_reserva);
  lista_destruir(partida->personaje.pokemones_combate);
  heap_destruir(partida->gimnasios);
}

//Post: Crea una partida. Muestra secuencialmente los menús del juego.
//Finalmente destruye la partida.
void jugar(){
  mostrar_mensaje_inicial();
  partida_t partida;
  inicializar_partida(&partida);
  int accion = menu_inicio(&partida);
  system("clear");
  if(accion == JUGAR){
    if(heap_raiz(partida.gimnasios) == NULL || lista_vacia(partida.personaje.pokemones_combate))
      printf("Error: No se cargaron datos suficientes para iniciar la partida\n");
    else
      menu_gimnasio(&partida);
  }
  else if(accion == SIMULAR){
    if(heap_raiz(partida.gimnasios) == NULL || lista_vacia(partida.personaje.pokemones_combate))
      printf("Error: No se cargaron datos suficientes para iniciar la partida\n");
    else{
      partida.simulacion = true;
      menu_gimnasio(&partida);
    }
  }
  destruir_partida(&partida);
}
