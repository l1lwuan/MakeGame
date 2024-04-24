#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "rob.hpp"
#include "character.hpp"
#include "boss.hpp"
#include <vector>

class GameState {
public:
    GameState(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~GameState();

    void handleEvent(SDL_Event& e);
    void update();
    void render();
    SDL_Renderer* renderer;
    std::vector<Character*> characters;
    Rob* rob;
    int screenWidth;
    int screenHeight;

    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
};

#endif // !GAMESTATE_HPP
