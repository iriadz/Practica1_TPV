#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Vehiculo.h"
#include "vector2D.h"
#include "Frog.h"
//rana(0), fondo(1)

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2}, // parte a la mitad la imagen a lo largo
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 6},
	{"wasp.png"},

};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	v1 = new Vehiculo(this, getTexture(CAR1), Point2D(410, 372), Vector2D<float>(-7, 0));
	frog = new Frog(this, textures[0]);
	// Configura que se pueden utilizar capas translúci
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Game::~Game()
{
	// TODO: liberar memoria reservada por la clase
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	textures[1]->render(); //FONDO
	// Llamar a pintar un coche
	v1->render();
	// Pinta una rana
	frog->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// TODO
	v1->update();
	frog->update();
}

void
Game::run()
{
	while (!exit) {
		update();
		handleEvents();
		render();
		SDL_Delay(30);
		// TODO: implementar bucle del juego
		
	}
}



void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
		frog->handleEvent(event);
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	return false;
}
