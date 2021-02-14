#include "menu_gimnasio.h"

#define VER_ENTRENADOR 'E'
#define VER_GIMNASIO_ACTUAL 'G'
#define CAMBIAR_POKEMONES 'C'
#define BATALLAR 'B'
#define TOMAR_PRESTADO 'T'
#define AVANZAR 'N'
#define CARACTER_VOLVER 'R'
#define CARACTER_FINALIZAR 'F'
#define VOLVER_GIMNASIO 1
#define FINALIZAR_PARTIDA -1

#define POKEMON_EN_USO "NO"

//Pre: Recibe un puntero a un pokemon y un contexto con un contador.
//Post: Imprime al pokemon y sus caracteristicas.
bool imprimir_pokemon_lista(void* pokemon, void* contexto){
  pokemon_t* pkm = (pokemon_t*)pokemon;
  printf("\t%li-%s Vel: %i Def: %i Att: %i\n", *(size_t*)contexto, pkm->nombre, pkm->velocidad+pkm->bonificacion, pkm->defensa+pkm->bonificacion, pkm->ataque+pkm->bonificacion);
  (*(size_t*)contexto)++;
  return true;
}

//Pre: Recibe un puntero a pokemon a analizar y un pokemon contexto que se busca
//Post: Si encuentra al pokemon buscado modifica al buscado como POKEMON_EN_USO
bool busqueda_de_pokemon(void* pokemon, void* contexto){
  if(!contexto)
    return false;
  pokemon_t* seleccionado = (pokemon_t*)contexto;
  pokemon_t* actual = (pokemon_t*)pokemon;
  if (strcmp(seleccionado->nombre, actual->nombre) != 0)
    return true;
  strcpy(seleccionado->nombre, POKEMON_EN_USO);
  return false;
}

//Pre: Recibe un puntero a una partida
//Post: Imprime la información del personaje principal
void mostrar_entrenador(partida_t* partida){
  system("clear");
  printf("|======| Personaje Principal |========|\n\n");
  printf("|*|Información:\n");
  printf("\tNombre: %s\n", partida->personaje.nombre);
  printf("|*|Pokemones de combate:\n");
  size_t id=1;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, (void*)&id);
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
  system("clear");
}

//Pre: Recibe un puntero a una partida
//Post: Imprime la información del gimnasio actual
void mostrar_gimnasio(partida_t* partida){
  system("clear");
  gimnasio_t* actual = heap_raiz(partida->gimnasios);
  printf("|======| Gimnasio Actual |========|\n\n");
  printf("|*|Información:\n");
  printf("\tNombre: %s\n", actual->nombre);
  printf("\tDificultad: %i\n", actual->dificultad);
  printf("\tLider: %s\n", actual->lider.nombre);
  printf("\nIngrese una letra cualquiera para continuar...\n");
  while(getchar() == '\n');
  system("clear");
}

//Pre: Recibe un puntero a una partida y un pokemon a añadir a la lista de combate
//Post: En caso de ser posible ingresa al pokemon a la lista de pokemones de combate
void seleccionar_slot_de_cambio(partida_t* partida, pokemon_t* pokemon){
  system("clear");
  pokemon_t seleccionado = *pokemon;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, busqueda_de_pokemon, (void*)&seleccionado);
  if(strcmp(seleccionado.nombre, POKEMON_EN_USO) == 0){
    printf("Este pokemon ya está en tu lista de combate\n");
    return;
  }
  printf("Has seleccionado a %s\n", pokemon->nombre);
  printf("Ahora escribe el" ANSI_COLOR_BLUE " numero de slot " ANSI_COLOR_RESET "del pokemon por el cual deseas cambiarlo:\n");
  size_t id=1;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, (void*)&id);
  size_t slot;
  scanf("%zu", &slot);
  if(slot < 1 || slot > MAX_POKEMONES_COMBATE+2)
    return;
  lista_borrar_de_posicion(partida->personaje.pokemones_combate, (slot-1));
  int resultado = lista_insertar_en_posicion(partida->personaje.pokemones_combate, (void*)pokemon, (slot-1));
  system("clear");
  if(resultado == EXITO)
    printf("Exito al cambiar pokemones\n");
  else
    printf("Error al cambiar pokemones\n");
}

//Pre: Recibe un puntero a una partida
//Post: Imprime los pokemones en reserva y llama a incorporar al seleccionado
void cambiar_pokemones(partida_t* partida){
  system("clear");
  printf(ANSI_COLOR_GREEN"|======| Pokemones en reserva |========|\n"ANSI_COLOR_RESET);
  printf("Bienvenido a la pantalla de cambio de pokemones. Aqui abajo se encontrarán los pokemones\n");
  printf("que usted dispone para cambiar. Ingrese el" ANSI_COLOR_BLUE " nombre " ANSI_COLOR_RESET "del pokemon que desee agregar:\n");
  pokemon_t* pkms_reserva[MAX_POKEMONES];
  size_t cantidad = arbol_recorrido_inorden(partida->personaje.pokemones_reserva, (void**)pkms_reserva, MAX_POKEMONES);
  for(size_t i=0;i<cantidad;i++)
  {
    printf("-%s Vel:%i Def:%i Att:%i\n", pkms_reserva[i]->nombre, pkms_reserva[i]->velocidad+pkms_reserva[i]->bonificacion, pkms_reserva[i]->defensa+pkms_reserva[i]->bonificacion, pkms_reserva[i]->ataque+pkms_reserva[i]->bonificacion);
  }
  printf("\nPokemon solicitado: ");
  char linea_leida[120];
  scanf("%s", linea_leida);

  pokemon_t pkm_cambio;
  strcpy(pkm_cambio.nombre, linea_leida);
  pokemon_t* pokemon_buscado = (pokemon_t*)arbol_buscar(partida->personaje.pokemones_reserva, (void*)&pkm_cambio);
  if(!pokemon_buscado)
  {
    system("clear");
    printf("No se encontró dicho pokemon\n\n");
    return;
  }
  seleccionar_slot_de_cambio(partida, pokemon_buscado);
}

//Pre: Recibe una lista de pokemones
//Post: Solicita un numero y lo devuelve
size_t slot_del_lider_seleccionado(lista_t* pokemones){
  size_t id=1;
  lista_con_cada_elemento(pokemones, imprimir_pokemon_lista, (void*)&id);
  size_t slot;
  do{
    scanf("%zu", &slot);
  } while(slot < 1 || slot > MAX_POKEMONES_COMBATE+1);
  return slot;
}

//Pre: Recibe una lista de pokemones
//Post: Devuelve el pokemon del slot seleccionado por el usuario
pokemon_t* elegir_pokemon_del_lider(lista_t* pokemones){
  system("clear");
  printf("|========| Elige el pokemon que quieras tomar prestado: |=======|\n");
  printf("Escribe el" ANSI_COLOR_BLUE " numero de slot " ANSI_COLOR_RESET "al que pertenezca:\n");

  size_t slot = slot_del_lider_seleccionado(pokemones);

  return (pokemon_t*)lista_elemento_en_posicion(pokemones, slot-1);
}

//Pre: Recibe un puntero a una partida
//Post: Le permite al usuario tomar uno de los pokemones del lider
void tomar_pokemon_prestado(partida_t* partida){
  gimnasio_t* gimnasio = heap_raiz(partida->gimnasios);
  pokemon_t* nuevo_pokemon = calloc(1, sizeof(pokemon_t));
  if(!nuevo_pokemon)
    return;
  pokemon_t* pokemon_prestado = elegir_pokemon_del_lider(gimnasio->lider.pokemones);
  *nuevo_pokemon = *pokemon_prestado;
  arbol_insertar(partida->personaje.pokemones_reserva, nuevo_pokemon);
  system("clear");
  printf("\tExito al agregar dicho pokemon. Puedes verlo en tus pokemones de reserva\n");
}

//Pre: Recibe un puntero a una partida y un bool
//Post: Redirige al usuario segun la opción del menú seleccionada
void menu_victoria(partida_t* partida, bool puede_tomar_prestado){
  printf(ANSI_COLOR_GREEN"|====| Menú de victoria |======|\n\n");
  printf("\t¡Gimnasio derrotado!\n" ANSI_COLOR_RESET);
  printf("Enhorabuena, añadiste una medalla a tu colección.\n");
  printf("|*| Ingrese alguna de las siguientes opciones:\n");
  if(puede_tomar_prestado)
    printf("\tT: Tomar un pokemon del Lider como recompensa\n");
  printf("\tC: Cambiar los pokemones de batalla\n");
  printf("\tN: Avanzar al proximo gimnasio\n");
  char caracter;
  do
  {
    caracter = (char)getchar();
    switch(caracter)
    {
      case TOMAR_PRESTADO:
        if(puede_tomar_prestado){
          tomar_pokemon_prestado(partida);
          menu_victoria(partida, false);
        }
        else
          caracter = ENTER;
      break;
      case CAMBIAR_POKEMONES:
        cambiar_pokemones(partida);
        menu_victoria(partida, puede_tomar_prestado);
      break;
      case AVANZAR:
        heap_extraer_raiz(partida->gimnasios);
      break;
      default:
        caracter = ENTER;
      break;
    }
  } while(caracter == ENTER);
}

//Pre: Recibe un puntero a una partida
//Post: Redirige al usuario segun la opción del menú seleccionada
int menu_derrota(partida_t* partida){
  printf(ANSI_COLOR_RED "|====| Menú de derrota |======|\n\n");
  printf("\tLa proxima tal vez :(\n" ANSI_COLOR_RESET);
  printf("Puedes volver a intentarlo, pero antes...\n");
  printf("|*| Ingrese alguna de las siguientes opciones:\n");
  printf("\tC: Cambiar los pokemones de batalla\n");
  printf("\tR: Volver al menú gimnasio\n");
  printf("\tF: Finalizar partida (rendirse)\n");
  char caracter;
  do
  {
    caracter = (char)getchar();
    switch(caracter)
    {
      case CAMBIAR_POKEMONES:
        cambiar_pokemones(partida);
        return menu_derrota(partida);
      break;
      case CARACTER_VOLVER:
        system("clear");
      break;
      case CARACTER_FINALIZAR:
        //
      break;
      default:
        caracter = ENTER;
      break;
    }
  } while(caracter == ENTER);
  return ((caracter == CARACTER_VOLVER) ? VOLVER_GIMNASIO : FINALIZAR_PARTIDA);
}

//Post: Muestra el mensaje final una vez ganada la partida
void mostrar_mensaje_final(partida_t* partida){
  system("clear");
  printf("Felicidades %s, de verdad que has demostrado tu poder. Llegaste al final de la aventura\n", partida->personaje.nombre);
  printf("\t¡Te has transformado en Maestro Pokemon!\n");
  printf("Esperamos que te hayas divertido.\n");
}

//Post: Muestra el mensaje final cuando se pierde una partida simulada
void mostrar_derrota_simulada(partida_t* partida){
  system("clear");
  gimnasio_t* gimnasio = heap_raiz(partida->gimnasios);
  printf("Que lastima %s\n", partida->personaje.nombre);
  printf("Parece que has perdido en: %s\n", gimnasio->nombre);
  printf("Pokemones que utilizaste:\n");
  size_t id=1;
  lista_con_cada_elemento(partida->personaje.pokemones_combate, imprimir_pokemon_lista, (void*)&id);
  printf("Más suerte la proxima :)\n");
}

//Pre: Recibe un puntero a una partida
//Post: Redirige al usuario según la opcion que elija, o en caso de ser simulada realiza las batallas
void menu_gimnasio(partida_t* partida){
  if(heap_raiz(partida->gimnasios) == NULL){
    mostrar_mensaje_final(partida);
    return;
  }
  if(partida->simulacion){
    int resultado = batallar(partida);
    if(resultado == GANO){
      heap_extraer_raiz(partida->gimnasios);
      menu_gimnasio(partida);
    }
    else
      mostrar_derrota_simulada(partida);
    return;
  }
  printf("|====| Bienvenido al menú de gimnasio |======|\n\n");
  printf("|*| Ingrese alguna de las siguientes opciones:\n");
  printf("\tE: Ver al entrenador principal junto a sus pokemones\n");
  printf("\tG: Ver información del gimnasio actual\n");
  printf("\tC: Cambiar los pokemones de batalla\n");
  printf("\tB: Realizar la proxima batalla planificada\n");
  printf("\tX: Salir\n");
  char caracter;
  do
  {
    caracter = (char)getchar();
    switch(caracter)
    {
      case VER_ENTRENADOR:
        mostrar_entrenador(partida);
        menu_gimnasio(partida);
      break;
      case VER_GIMNASIO_ACTUAL:
        mostrar_gimnasio(partida);
        menu_gimnasio(partida);
      break;
      case CAMBIAR_POKEMONES:
        cambiar_pokemones(partida);
        menu_gimnasio(partida);
      break;
      case BATALLAR:{
        int resultado = batallar(partida);
        if(resultado == GANO){
          menu_victoria(partida, true);
          menu_gimnasio(partida);
        }
        else{
          int continuacion = menu_derrota(partida);
          if(continuacion == VOLVER_GIMNASIO)
            menu_gimnasio(partida);
        }
      break;
      }
      case SALIR_PARTIDA:
        caracter = SALIR;
      break;
      default:
        caracter = ENTER;
      break;
    }
  } while(caracter == ENTER);
}
