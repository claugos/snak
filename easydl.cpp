#pragma once // esto se explica en tanque.cpp

#include "easydl.h" // copiamos aqui lo que contiene el archivo easydl.h

using namespace std; // declaramos que usaremos el espacio de nombres por defecto de c++

/*
En este archivo ampliamos la capacidad de la clase Game de SDL para hacer mas facil y rapido el desarrollo
*/

bool Game::start(int w, int h, int fps, bool hw) // Definimos una funcion que devuelve valores booleanos, llamada Game
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { // comprobamos el video
		cout << "Error iniciando SDL: " << SDL_GetError()  << '\n';
		return false;
	}

    window = SDL_CreateWindow( // Creamos una ventana llamada window, recibe como argumentos su nombre, posicion y tamaño
                  "SDL Base Project",
                  SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOWPOS_UNDEFINED,
                  w, h,
                  0);

    if (window == NULL) { // comprobamos si hubo un error al crear la ventana
        cout << "Error creando la ventana: " << SDL_GetError()  << '\n';
        return false;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP; // cargamos los tipos de imagenes aceptados
    if (!(IMG_Init(imgFlags) & imgFlags)){ // comprobamos si todo va bien
        cout << "Error cargando SDL_Image: " << IMG_GetError()  << '\n';
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, hw ? SDL_RENDERER_ACCELERATED : SDL_RENDERER_SOFTWARE); // renderizamos la imagen

    FPS = fps;
	return true; // si no hubo errores devuelve true
}

void Game::draw(SDL_Texture *t, SDL_Rect &r, float rot) // La funcion redibujar que tendran los personajes e items, objetos en general
{
    SDL_RenderCopyEx(renderer, t, NULL, &r, rot, NULL, SDL_FLIP_NONE);
}

void Game::drawRect(SDL_Rect &rect, Uint8 r, Uint8 g, Uint8 b) // la capacidad de dibujar rectangulos de forma facil
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void Game::update() // Actualizar la imagen en la ventana a los FPS calculados
{
    auto timerFps = SDL_GetTicks();
    SDL_PumpEvents();
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    timerFps = SDL_GetTicks() - timerFps;

    if (timerFps < 1000 / FPS) {
        SDL_Delay((1000 / FPS) - timerFps);
    }
}

void Game::quit() // Terminar el juego destruyendo objetos y liberando memoria
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* Game::loadImage(string path) { // Hacemos un modo de obtener imagenes de forma sencilla por su nombre y
//  las devolvemos como textura utilizable en objetos como personajes, fondos e items
	auto img = IMG_Load(path.c_str());
	if (img == NULL) {
		cout << "No se pudo cargar " << path.c_str() << ". " << SDL_GetError() << '\n';
		return NULL;
	}

    auto texture = SDL_CreateTextureFromSurface(renderer, img);

    SDL_FreeSurface(img);

	return texture;
}

bool Game::quitEvent() // Agilizamos el manejo de events
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

