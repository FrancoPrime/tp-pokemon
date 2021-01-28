#include "menu_inicio.h"
#include <stdio.h>
#define FORMATO_POKEMON "P;%100[^;];%i;%i;%i\n"
#define FORMATO_LIDER "L;%100[^\n]\n"
#define FORMATO_ENTRENADOR "E;%100[^\n]\n"
#define FORMATO_GIMNASIO "G;%100[^;];%i;%i\n"

#define CANTIDAD_LEIDOS_POKEMON 4
#define CANTIDAD_LEIDOS_NOMBRE 1
#define CANTIDAD_LEIDOS_GIMNASIO 3

#define ID_LIDER 'L'
#define ID_ENTRENADOR 'E'
#define ID_POKEMON 'P'

#define ACTUALIZAR_PERSONAJE 'E'
#define AGREGA_GIMNASIO 'A'
#define COMIENZA_PARTIDA_INTERACTIVA 'I'
#define SIMULA_PARTIDA 'S'

#define MAX_NOMBRE 100

FILE* leer_archivo(char* mensaje){
  char nombre_archivo[MAX_NOMBRE_ARCHIVO];
  printf("%s", mensaje);
  scanf("%s", nombre_archivo);
  FILE* archivo = fopen(nombre_archivo, "r");
  if(!archivo)
    printf("Archivo no encontrado\n");
  return archivo;
}

entrenador_t* agregar_entrenador(gimnasio_t* gim, char* linea)
{
  entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
  if(!entrenador)
    return NULL;
  int campos_leidos = sscanf(linea,
                          FORMATO_ENTRENADOR,
                          entrenador->nombre);
  if(campos_leidos != CANTIDAD_LEIDOS_NOMBRE){
    free(entrenador);
    return NULL;
  }
  entrenador->pokemones = lista_crear();
  if(!entrenador->pokemones)
  {
    free(entrenador);
    return NULL;
  }
  lista_apilar(gim->entrenadores, (void*)entrenador);
  return entrenador;
}

pokemon_t* agregar_pokemon(char* linea)
{
  pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
  if(!pokemon)
    return NULL;
  int campos_leidos = sscanf(linea,
                            FORMATO_POKEMON,
                            pokemon->nombre,
                            &pokemon->velocidad,
                            &pokemon->ataque,
                            &pokemon->defensa);
  if(campos_leidos != CANTIDAD_LEIDOS_POKEMON)
  {
    free(pokemon);
    return NULL;
  }
  return pokemon;
}

int leer_nombre_personaje(FILE* archivo, char nombre[MAX_NOMBRE], char letra_id){
  char buffer[1024];
  char* linea = fgets(buffer, 1024, archivo);

  if(!linea)
    return ERROR;
  int campos_leidos;
  if(letra_id == ID_LIDER)
    campos_leidos = sscanf(linea,
                            FORMATO_LIDER,
                            nombre);
  else
    campos_leidos = sscanf(linea,
                            FORMATO_ENTRENADOR,
                            nombre);
  if(campos_leidos == CANTIDAD_LEIDOS_NOMBRE)
    return EXITO;

  return ERROR;
}

pokemon_t* pokemon_leer_de_archivo(FILE* archivo){
  char buffer[1024];
  char* linea = fgets(buffer, 1024, archivo);

  if(!linea)
    return NULL;

  return agregar_pokemon(linea);
}

int leer_pokemones_personaje(FILE* archivo, personaje_t* personaje){
  pokemon_t* un_pokemon;
  while((un_pokemon = pokemon_leer_de_archivo(archivo)) != NULL)
  {
    if(personaje->pokemones_combate->cantidad < MAX_POKEMONES_COMBATE)
      lista_encolar(personaje->pokemones_combate, un_pokemon);
    arbol_insertar(personaje->pokemones_reserva, un_pokemon);
  }
  if(arbol_vacio(personaje->pokemones_reserva))
    return ERROR;
  return EXITO;
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

gimnasio_t* crear_gimnasio(){
  gimnasio_t* nuevo_gim = calloc(1, sizeof(gimnasio_t));
  if(!nuevo_gim)
    return NULL;

  nuevo_gim->entrenadores = lista_crear();
  if(!nuevo_gim->entrenadores){
    free(nuevo_gim);
    return NULL;
  }

  return nuevo_gim;
}

int leer_informacion_gim(FILE* archivo, gimnasio_t* gim)
{
  char buffer[1024];
  char* linea = fgets(buffer, 1024, archivo);

  if(!linea)
    return ERROR;
  int campos_leidos = sscanf(linea,
                            FORMATO_GIMNASIO,
                            gim->nombre,
                            &gim->dificultad,
                            &gim->id_puntero_funcion);
  if(campos_leidos == CANTIDAD_LEIDOS_GIMNASIO)
    return EXITO;
  return ERROR;
}

int agregar_gimnasio(partida_t* partida){
  FILE* archivo = leer_archivo("Ingrese la ruta del archivo del gimnasio: ");
  if(!archivo){
    return ERROR;
  }

  gimnasio_t* nuevo_gim = crear_gimnasio();
  if(!nuevo_gim){
    fclose(archivo);
    return ERROR;
  }

  if(leer_informacion_gim(archivo, nuevo_gim) == ERROR){
    destruir_gimnasio(nuevo_gim);
    fclose(archivo);
    return ERROR;
  }

 if(leer_nombre_personaje(archivo, (nuevo_gim->lider.nombre), ID_LIDER) == ERROR){
    printf("No se encontró al lider del gimnasio\n");
    destruir_gimnasio(nuevo_gim);
    fclose(archivo);
    return ERROR;
  }

  entrenador_t* entrenador_actual = &(nuevo_gim->lider);
  entrenador_actual->pokemones = lista_crear();
  if(!entrenador_actual->pokemones)
  {
    destruir_gimnasio(nuevo_gim);
    fclose(archivo);
    return ERROR;
  }

  char identificador_linea;
  while(entrenador_actual)
  {
    char buffer[1024];
    char* linea = fgets(buffer, 1024, archivo);

    if(!linea)
      entrenador_actual = NULL;
    else
    {
      sscanf(linea, "%c;", &identificador_linea);
      if(identificador_linea == ID_ENTRENADOR){
        entrenador_actual = agregar_entrenador(nuevo_gim, linea);
      }
      else if(identificador_linea == ID_POKEMON){
        pokemon_t* pokemon = agregar_pokemon(linea);
        if(pokemon)
          lista_apilar(entrenador_actual->pokemones, (void*)pokemon);
        else
          entrenador_actual = NULL;
      }
      else
        entrenador_actual = NULL;
    }
  }

  if(lista_vacia(nuevo_gim->lider.pokemones)){
    destruir_gimnasio(nuevo_gim);
    fclose(archivo);
    return ERROR;
  }

  heap_insertar(partida->gimnasios, (void*)nuevo_gim);
  fclose(archivo);
  printf("Exito al añadir gimnasio\n");
  return EXITO;
}

int menu_inicio(partida_t* partida){
  printf("|-------| Menú de Inicio |-------|\n\n");
  printf("|*| Opciones:\n");
  printf("\tE: Ingresar el entrenador principal\n");
  printf("\tA: Agregar un gimnasio a la partida\n");
  printf("\tI: Comenzar la partida\n");
  printf("\tS: Simular la partida\n");
  char caracter = (char)getchar();
  switch(caracter)
  {
    case ACTUALIZAR_PERSONAJE:
      actualizar_personaje(partida);
      return menu_inicio(partida);
    break;
    case AGREGA_GIMNASIO:
      agregar_gimnasio(partida);
      return menu_inicio(partida);
    break;
    case COMIENZA_PARTIDA_INTERACTIVA:
      return JUGAR;
    break;
    case SIMULA_PARTIDA:
      return SIMULAR;
    break;
    default:
      system("clear");
      return menu_inicio(partida);
    break;
  }
}
