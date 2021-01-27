#define "menu_inicio.h"
#define FORMATO_POKEMON "P:%100[^;];%i;%i;%i;\n"


FILE* leer_archivo(char* mensaje){
  char nombre_archivo[MAX_NOMBRE_ARCHIVO];
  printf("%s", mensaje);
  scanf("%s", nombre_archivo);
  FILE* archivo = fopen(nombre_archivo, r);
  if(!archivo)
    printf("Archivo no encontrado\n");
  return archivo;
}

pokemon_t* pokemon_leer_de_archivo(FILE* archivo){
  char buffer[1024];
  char* linea = fgets(buffer, 1024, archivo);

  if(!linea)
    return NULL;

  pokemon_t* pokemon = malloc(sizeof(pokemon_t));

  if(!pokemon)
    return NULL;

  int campos_leidos = sscanf(linea,
                            FORMATO_POKEMON,
                            pokemon->nombre,
                            &pokemon->velocidad,
                            &pokemon->ataque,
                            &pokemon->defensa);
  if(campos_leidos == 4)
    return pokemon;

  free(pokemon);
  return NULL;
}

int leer_pokemones_personaje(FILE* archivo, entrenador_t* entrenador){
  pokemon_t* un_pokemon;
  while((un_pokemon = pokemon_leer_de_archivo(archivo)) != NULL)
  {
    if(entrenador->pokemones_combate->cantidad < MAX_POKEMONES_COMBATE)
      lista_encolar(entrenador->pokemones_combate, un_pokemon);
    arbol_insertar(entrenador->pokemones_reserva, un_pokemon);
  }
}

int actualizar_personaje(partida_t* partida){
  FILE* archivo =  leer_archivo("Ingrese la ruta del archivo del personaje: ");
  if(!archivo){
    return ERROR;
  }

  if(leer_nombre_personaje(archivo, (partida->personaje.nombre), ID_ENTRENADOR) == ERROR){
    printf("No se pudo leer el nombre del personaje\n");
    fclose(archivo);
    return ERROR;
  }

  //lista_con_cada_elemento(partida->personaje.pokemones_combate, destructor_pokemon_lista, NULL);
  lista_destruir(partida->personaje.pokemones_combate);
  partida->personaje.pokemones_combate = lista_crear();

  if(!partida->personaje.pokemones_combate){
    fclose(archivo);
    return ERROR;
  }

  arbol_destruir(partida->personaje.pokemones_reserva);
  partida->personaje.pokemones_reserva = arbol_crear(comparar_pokemones, destruir_pokemon);
  if(!partida->personaje.pokemones_reserva){
    fclose(archivo);
    lista_destruir(partida->personaje.pokemones_combate);
    return ERROR;
  }

  int resultado = leer_pokemones_personaje(archivo, (void*)(&(partida->personaje)));

  if(resultado == ERROR){
    printf("Ocurrió un error al intentar cargar los pokemones\n");
  } else {
    printf("Información del personaje cargada correctamente.\n");
  }

  fclose(archivo);
  return EXITO;
}

void menu_inicio(partida_t* partida){
  printf("|-------| Menú de Inicio |-------|\n");
  printf("*Opciones:\n");
  printf("E: Ingresar el entrenador principal\n");
  printf("A: Agregar un gimnasio a la partida\n");
  printf("I: Comenzar la partida\n");
  printf("S: Simular la partida\n");
  char caracter = (char)getchar();
  switch(caracter)
  {
    case ACTUALIZAR_PERSONAJE:
      actualizar_personaje(partida);
      menu_inicio(partida);
    break;
    case AGREGA_GIMNASIO:
      printf("Ingresaste A");
    break;
    case COMIENZA_PARTIDA_INTERACTIVA:
      printf("Ingresaste I");
    break;
    case SIMULA_PARTIDA:
      printf("Ingresaste S");
    break;
    default:
      system("clear");
      menu_inicio();
    break;
  }
}
