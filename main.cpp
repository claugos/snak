#include <SDL.h> // Cargamos la libreria de graficos
#include "easydl.h" // copiamos aqui el codigo escrito en easydl.h 
#include <iostream> // Agregamos la libreria de streams
#include <string.h> // tambien agregamos la libreria que nos permite manejar facilmente cadenas de texto
#include <map> // y la libreria map, que es un contenedor de objetos
#include "Tanque.h" // aqui copiamos el codigo que escribimos en Tanque.h
/*
Cuando se copia codigo escrito por uno mismo como en el caso de easydl y Tanque es porque asi solo le pasamos al compilador un solo archivop
copia y pega el contenido indicado en el mismo archivo y asi procesa solo uno a la vez, que contiene el codigo escrito en todos
El orden es importante, si en uno defines algo que vas a usar en otro es necesario añadirlo antes para que no devuelva errores
*/
 struct nodo{ // Generamos una estructura llamada nodo, esto nos permitira crear variables tipo "nodo" como creamos tipo int, string o char.
     // cada variable tipo nodo tendra los siguientes datos
     Tanque * valor;  // un puntero a un valor
     nodo * siguiente; // un puntero a el valor de siguiente
     nodo(){ // Al ser creado sucedera esto

         siguiente = nullptr; // se especifica que el valor de siguiente sera un puntero null, o no definido para que no haya errores.
     }
 };
 struct lista { // Generamos otro struct llamado lista, sera una lista de nodos, algo asi como un array
     nodo * inicial,*fin; // Tendra dos punteros de nodos, llamados inicial y fin

     void insertar (Tanque*m){ // Cada lista puede permitir que se le inserten tanques (por su puntero, aqui llamado m)
         nodo * nuevo = new nodo(); // creamos un ojbeto nuevo nodo llamado nuevo
     nuevo -> valor = m; // al nodo nuevo se le asigna el valor de m (valor es una variable definida en el struct de nodo)
         if(inicial== nullptr){ // Si el valor ide inicial es un puntero nulo
                inicial = nuevo; // entonces le asignamos a inicial un nuevo valor, el de nuevo
                fin = inicial; // Y a fin, el valor de inicial
         }
         else // Si no
         {
             fin -> siguiente = nuevo; // al nodo fin, en su variable interna siguiente, le asignamos el valor de nuevo
        fin = nuevo; // y a fin le asignamos el valor de "nuevo"
         }

     }
      nodo * obtener( int j ){ // Cada lista puede permitir que le soliciten valores tipo nodo dando solo el numero de lista del nodo solicitado
         nodo *actual = inicial; // En este caso se crea un puntero de nodo llamado actual y se le asigna el valor de inicial
         while(j > 0 & actual != nullptr){ // mientras el numero dado sea mayor que cero y el valor de actual no sea un puntero nulo
            actual = actual -> siguiente; // Hacemos que el valor de la variable interna del nodo llamada actual del puntero de nodo llamado "actual", sea el de siguiente
            -- j; // y luego decrementamos en uno el valor de j
         }
         return actual; // Una vez terminado el proceso anterior devolvemos el valor de actual

     }
     lista (){ // Este es el constructor de la lista
         inicial = nullptr; // Genera sus variables internas con valores iniciales tipo puntero nulo
         fin = nullptr;


     }
 };
// ahora esta definido todo lo necesario para comenzar a programar el juego..

using namespace std; // indicamos que usaremos el espacio de nombres por defecto de c++

const int W_SCREEN = 580; // Creamos la variable de ancho de ventana en 580 px
const int H_SCREEN = 420; // El alto en 420px
const int TAM_IMAGEN = 16; // Y el tamaño unitario de imagen en 16
int main(int argc, char *argv[]) // creamos el vector de entrada del programa, recibe sus argumentos por defecto...
{
    lista y; // generamos una lista de nodos llamada y
    Game game; // creamos una variable "game" de tipo "Game"

    game.start(W_SCREEN, H_SCREEN, 50, true); // iniciamos el juego con los valores de ventana ants definidos

    // Rect destino para pintar
    SDL_Rect DestR; // creamos un rectangulo de SDL llamado DestR
    DestR.x = W_SCREEN /2  - TAM_IMAGEN /2 ; // le asignamos un valor de coordenadas
    DestR.y = H_SCREEN / 2 - TAM_IMAGEN / 2;
    DestR.w = TAM_IMAGEN; // Y ancho y alto
    DestR.h = TAM_IMAGEN;

    Tanque *t = new Tanque( // Ahora creamos una instancia de Clase Tanque llamada T, un puntero a el mejor dicho
        SDL_SCANCODE_UP, // le pasamos el sistema de deteccion de teclas de direccion como argumento
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT,
        DestR, // rectangulo destino
        game.loadImage("Jugador.bmp")); // y le asignamos la imagen jugador.bmp como sprite (su representacion en pantalla)

         SDL_Rect DesR; // Generawmos un rectangulo de SDL llamado DesR
    DesR.x = W_SCREEN /3- TAM_IMAGEN /2 ; // Le damos coordenadas de posicion
    DesR.y = H_SCREEN / 3 - TAM_IMAGEN / 2;
    DesR.w = TAM_IMAGEN; // y alto y ancho
    DesR.h = TAM_IMAGEN;

        // Ademas creamos otro tanque llamado o
        Tanque *o = new Tanque( // Recibe tambien el sistema de deteccion de teclas de direccion como argumento para que pueda hacer uso de el
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT,
        DesR, // tambien recibe el rectangulo creado antes
        game.loadImage("Jugador.bmp")); // y usa el mismo sprite que el tanque anteriror
    while(!game.quitEvent()){ // Esto mantiene vivo el juego, pregunta si se ha dado la orden de cerrar, y si no, repite el proceso del juego
        t->update(); // Actualiza el tanque t
        t->draw(&game); // Lo redibuja en el tablero game
         o->update(); // hace lo mismo para el tanque o
        o->draw(&game);
        game.update(); // Finalente actualiza el juego, es decir renderiza la imagen y la muestra, justo como definimos en "Game", en el archivo easydl
    }
    y.insertar(t); // una vez terminado el programa añadimos los tanques a la lista y
    y.insertar(o);
    game.quit(); // Y con esto limpiamos las memoria usada durante la ejecucion del juego (la memoria de las funciones internas de sdl)

    return 0; // Retornamos 0 indicando que todo salio bien
}
