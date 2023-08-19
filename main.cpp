#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "gameobject.cpp"

using namespace std;

void init();
void loadMedia();
void render();
void close();

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;
int SCREEN_WIDTH = 800; int SCREEN_HEIGHT = 600;
int IMG_WIDTH; int IMG_HEIGHT;

string mntPath = "/mnt/c/Users/beelz/images/sdl/";

vector<GameObject> gameObjects;

int main(int argc, char* argv[]) 
{
	init(); loadMedia(); 
	GameObject g(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT, 20*IMG_WIDTH, 20*IMG_HEIGHT, gTexture);
	gameObjects.push_back(g);
	render();
    SDL_Delay(3000);
	render();
	SDL_Delay(3000);
	close();
    return 0;
}

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        cout << "SDL initialization failed: " << SDL_GetError() << endl;

    gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN);
    
    if (!gWindow) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer) {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image initialization failed: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
}

void loadMedia()
{
    string imagePath = mntPath + "wizard.png";
	SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());

    if (!imageSurface) {
        cout << "Failed to load image: " << IMG_GetError() << endl;
        IMG_Quit();
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }

    gTexture = SDL_CreateTextureFromSurface(gRenderer, imageSurface);
	IMG_WIDTH = imageSurface->w; IMG_HEIGHT = imageSurface->h;
	SDL_FreeSurface(imageSurface);

    if (!gTexture) {
        cout << "Failed to create texture: " << SDL_GetError() << endl;
        IMG_Quit();
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
}

void render()
{
	for (GameObject& g : gameObjects)
	{
		g.render(gRenderer);
		g.move(10, 10);
	}
}

void close()
{
    SDL_DestroyTexture(gTexture);
    IMG_Quit();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
