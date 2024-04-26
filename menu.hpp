#ifndef MENU_HPP
#define MENU_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


class Menu {
public:
	Menu(SDL_Renderer* renderer);
	~Menu();
	void render();
	std::string handleEvent(SDL_Event& e);
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Rect Start;
	SDL_Rect Info;
	SDL_Texture* backgroundTexture;
};
#endif // !MENU_HPP
