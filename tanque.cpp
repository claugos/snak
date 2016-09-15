#pragma once // para ver que es esto: https://es.wikipedia.org/wiki/Pragma_once
#include "tanque.h" // Indicamos que incluya en esta parte el contenido del archivo "tanque.h"

using namespace std; // Trabajaremos en el espacio de nombres por defecto de c++
// significa que no puedes usar el mismo nombre de variable para dos variables distintas.
// cuando se usa :: se esta haciendo uso de un espacio de nombres, por ejemplo
// Tanque::update se refiere a que la funcion update del objeto o nombre Tanque, si hubiera otro objeto con su propio update
// aunque se llamen igual el compilador no se confunde.

void Tanque::update(){ // esta funcion actualiza la posicion del tanque en cada instante
    const Uint8 *state = SDL_GetKeyboardState(NULL); // lee las teclas
    if (state[tDerecha]) { // Pregunta si ha pulsado la tecla ir a la derecha
        rot = 90; // Hace que el tanque apunte a la derecha
        rect.x += 10; // Mueve el tanque a la derecha 10 pasos (por lo general pasos = pixeles)
    }
    else if (state[tIzquierda]) { // Si no fue a la derecha revisa si fue a la izquierda
        rot = -90; // Apunta al lado contrario, la izquierda
        rect.x -= 10; // Y avanza los 10 pasos a la izquierda
    }
    // Lo mismo con el resto de las funciones, pero ahora en el eje y
    else if (state[tArriba]) {
        rot = 0;
        rect.y -= 10;
    }
    else if (state[tAbajo]) {
        rot = 180;
        rect.y += 10;
    }
}

void Tanque::draw(Game *game) { // esta funcion re dibuja el tanque cada vez que se revisa su hubicacion, 
// recibe como argumento una variable tipo Game, llamada dentro de esta funcion como game
    game->draw(textura, rect, rot); // En la pantalla principal del juego redibuja el tanque con la textura, forma y posicion dados
    game->drawRect(rect, 255, 0, 0);
}

Tanque::Tanque(Uint8 arriba, Uint8 abajo, Uint8 izquierda, Uint8 derecha, SDL_Rect r, SDL_Texture* t) { // Este es el constructor del tanque, 
//definimos las variables que internamente usaran sus funciones, y en algunos casos les damos valor inicial, recibe como argumento la mayoria
    tArriba = arriba;
    tAbajo = abajo;
    tIzquierda = izquierda;
    tDerecha = derecha;
    rect = r;
    textura = t;
    rot = 0;
}


