#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Vehiculo.h"
#include "vector2D.h"
#include "Wasp.h"
#include "Log.h"
#include "Frog.h"
#include "Collision.h"
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

	//CARGAR ELEMENTOS ---- COCHES/RANA/TORTUGAS/TRONCOS --------------

	//Carga los coches. fala inicializar varios de cada tipo 
	for (int i = 0; i < CAR_NUM; i++)
	{
		if (i % 2 == 0)coches[i] = new Vehiculo(this, getTexture(static_cast<TextureName>(i + 2)), Point2D(410, 372 - (i * 30)), Vector2D<float>(-6, 0));
		else coches[i] = new Vehiculo(this, getTexture(static_cast<TextureName>(i + 2)), Point2D(0, 372 - (i * 30)), Vector2D<float>(6, 0));
	}
	
	//Carga rana
	Point2D iniPos(WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT - 32);
	frog = new Frog(this, textures[0], iniPos);

	//Cargar troncos
	for (int i = 0; i < LOG_NUM; i++)
	{
		//troncos[i] = new Log(this, getTexture(static_cast<TextureName>(i + 7)), Point2D(410, 170 - (i * 30)), Vector2D<float>(-6 - i, 0));

		if (i % 2 == 0)troncos[i] = new Log(this, getTexture(LOG1), Point2D(410, 170 - (i * 30)), Vector2D<float>(-6 - i, 0));
		else troncos[i] = new Log(this, getTexture(LOG2), Point2D(410, 170 - (i * 30)), Vector2D<float>(-6 - i, 0));
	}

	//Cargar avispas

	for (int i = 0; i < WASP_NUM; i++)
	{
		wasps[i] = new Wasp(this, getTexture(WASP), Point2D(0, 0), 100);
	}
	


	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Game::~Game()
{
	// TODO: liberar memoria reservada por la clase
	delete[] coches[0];
	delete[]troncos[0];
	delete frog;
	delete[] wasps[0];
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// TODO
	textures[1]->render();
	for (int i = 0; i < CAR_NUM; i++)
	{
		coches[i]->render();
	}
	for (int i = 0; i < LOG_NUM; i++)
	{
		troncos[i]->render();
	}
	
	frog->render();

	for (int i = 0; i < WASP_NUM; i++)
	{
		wasps[i]->render();
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// TODO
	
	for (int i = 0; i < CAR_NUM; i++)
	{
		coches[i]->update();
	}

	for (int i = 0; i < LOG_NUM; i++)
	{
		troncos[i]->update();
	}

	frog->update();

	for (int i = 0; i < WASP_NUM; i++)
	{
		wasps[i]->update();
		if (!wasps[i]->isAlive()) delete wasps[i]; // Borrar de la memoria las avispas muertas
	}

}

void
Game::run()
{
	while (!exit) {
		// Bucle principal del juego
		update();
		handleEvents();
		render();
		if (frog->getLifes() <= 0) {
			exit = true;
		}
		SDL_Delay(30);		
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

Collision::Type
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	int i = 0; int j = 0;
	while (!coches[i]->checkCollision(rect) && i < CAR_NUM - 1) {
		i++;
	}
	if (coches[i]->checkCollision(rect)) {
		return Collision::Type::ENEMY;
	}
	
	while (!troncos[j]->checkCollision(rect) && j < LOG_NUM - 1) {
		j++;
	}
	if (frog->getPosition() <= 170 && frog->getPosition() >= 20) // solo comprueba las posiciones de los troncos si esta en el rio
	{
		if (!troncos[j]->checkCollision(rect)) {
			return Collision::Type::ENEMY;
		}
	}
	
	return Collision::Type::NONE;
}
