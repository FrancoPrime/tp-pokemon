=Aventura Pokemon=

-¿Qué es?-

Es un juego de terminal hecho en C, basado en la popular franquicia animé llamada "Pokémon". En el mismo podrás batallar con los distintos entrenadores y consagrarte Maestro Pokemon al derrotar todos los gimnasios disponibles. Una vez que derrotes el gimnasio, podrás tomar prestado uno de los pokemones del lider y guardarlo en tus pokemones de reserva.

Antes de pelear contra un gimnasio, podrás:
Ver la información de tu personaje y tus pokemones de combate;
colocar pokemones de tu reserva para que peleen;
ver la dificultad del gimnasio contra el cual lucharás.

Por cada combate que tus pokemones ganen incrementarán sus habilidades hasta un máximo posible de 63 puntos.

El juego te guiará mediante menús en los cuales decidirás como deseas avanzar. En un principio, se te pedirá que cargues la información de la partida tal como tu personaje principal y los gimnasios disponibles.
Puedes crear tus propios archivos de gimnasios y entrenador. El juego trae los archivos entrenador.txt y gimnasios.txt como prueba.

-Compilación-

Para compilar el proyecto se utilizará la linea
$ make aventura

Luego, para ejecutar el proyecto, se utilizará la linea
$ ./aventura

Para realizar pruebas de memoria y verificar que no hay pérdidas de la misma, se utilizará la linea
$ make valgrind

-Implementación-

El juego se realizó en el lenguaje C como aplicación de consola. Se utilizaron los distintos TDAs aprendidos a lo largo de la cursada.

-Estructura y organización-

Los archivos del juego se encuentran en la carpeta principal. Siendo:

Juego.c y Juego.h = Se establecen las estructuras a usar en todo el juego. Se crearon las funciones de comparación y destrucción de estructuras necesarias. Tiene el flujo principal del juego. Desde la función Jugar() se llama a los menús de inicio y luego al de gimnasio. Finalmente se encarga de destruir la partida antes de salir de la aplicación.

menus/Menu_inicio.c = Aquí se colocó todo lo relacionado al menú de inicio y la carga de datos para el inicio de la partida. Se encuentra la lógica de lectura de archivos. Una vez fuera del menú de inicio lo contenido en este archivo no se vuelve a utilizar.

menus/Menu_Gimnasio.c = Se encarga de controlar la partida una vez iniciada. Contiene el menú de gimnasio, que permite ver al personaje, ver el gimnasio actual y cambiar pokemones. Se encarga del flujo de batallas, llamando a la función(ubicada en otro archivo) y dependiendo del resultado mostrando el menú de victoria o derrota segun corresponda.

batallas/batallas.c = Contiene las distintas batallas posibles entre pokemones

batallas/logica_batallas.c = Se encarga de la logica de batallas. Ejecuta las respectivas peleas dentro de un gimnasio, las mismas son: Batallar contra entrenadores/Batallar contra el Lider. Y dentro de estas la lógica de batallar contra los pokemones correspondientes.

-Utilización y explicación del uso de TDAs-

Las estructuras utilizadas fueron: Lista, Cola, Pila, Arbol binario de busqueda, Heap

Heap: Se utilizó para guardar los gimnasios de la partida en orden minimal. Siendo siempre el siguiente a enfrentar el de menor dificultad.

Arbol binario de búsqueda: Se utilizó para guardar los pokemones de reserva. Teniendo en cuenta que éstos pueden alcanzar un volúmen amplio y era preferible mantener un orden, se decidió ordenarlos alfabeticamente. Para hacer esta tarea luego más sencilla, debido a que se deberá imprimir y luego buscar al pokemon cuando se lo quiera colocar como pokemon de combate.

Lista: La lista fue utilizada para guardar los pokemones de combate del personaje principal y de los distintos entrenadores. Esto se debe a que se quiere recorrerlos sin ir descartandolos.

Cola: La cola se utiliza dentro de los combates, en donde las listas de combate de pokemones se trasladan a una cola y se van desencolando a medida que los distintos pokemones pierden el combate.

Pila: La pila se utiliza adentro del gimnasio, para ir almacenando a los entrenadores que le pertenecen al mismo. Esto se debe a que el último entrenador leído del archivo es el primero al cual se debe enfrentar el usuario, y que una vez derrotado dicho entrenador, el usuario no debe volver a enfrentarse a éste por lo cual puede ser removido.

-Modificaciones de TDAs-

Se decidió añadirle un destructor al TDA Lista con el fin de hacer más sencilla la liberación de memoria almacenada en la misma.
