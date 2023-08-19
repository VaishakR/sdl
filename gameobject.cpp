#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

class GameObject
{
	public:
		GameObject(float x, float y, int scw, int sch, int w, int h, SDL_Texture* t)
			: xPos(x), yPos(y), SCREEN_WIDTH(scw), SCREEN_HEIGHT(sch), IMG_WIDTH(w), IMG_HEIGHT(h), texture(t) {};
		float xPos; float yPos;
		float dx; float dy;
		float ax; float ay;
		SDL_Texture* texture;
		SDL_Rect hitbox = {(int)xPos, (int)yPos, IMG_WIDTH, IMG_HEIGHT};
		bool colliding(GameObject* other);
		void render(SDL_Renderer* rend);
		int getWidth(); int getHeight();
		void setPosition(int newX, int newY);
		void move(int x, int y);
	private:
		int SCREEN_WIDTH; int SCREEN_HEIGHT;
		int IMG_WIDTH; int IMG_HEIGHT;
};

bool GameObject::colliding(GameObject* other) 
{
    if (xPos + IMG_WIDTH <= other->xPos) // rect1 is to the left of rect2
        return false;
    
    if (xPos >= other->xPos + other->getWidth()) // rect1 is to the right of rect2
        return false;
    
    if (yPos + IMG_HEIGHT <= other->yPos) // rect1 is above rect2
        return false;
    
    if (yPos >= other->yPos + other->getHeight()) // rect1 is below rect2
        return false;
    
    return true;
}

int GameObject::getWidth()
{
	return IMG_WIDTH;
}

int GameObject::getHeight()
{
	return IMG_HEIGHT;
}

void GameObject::render(SDL_Renderer* rend) 
{
	SDL_Rect destRect = { xPos, yPos, IMG_WIDTH, IMG_HEIGHT };

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture, nullptr, &destRect);
    SDL_RenderPresent(rend);

	cout << "rendered\n";
}

void GameObject::setPosition (int newX, int newY)
{
	xPos = newX;
	yPos = newY;
}

void GameObject::move (int x, int y)
{
	cout << "og: " << xPos << ", " << yPos << "\n";
	xPos += x;
	yPos += y;
	cout << "new: " << xPos << ", " << yPos << "\n";
}


