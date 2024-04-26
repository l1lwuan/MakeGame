#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "rob.hpp"
#include "character.hpp"
#include "skills.hpp"
#include <vector>
#include "menu.hpp"
#include "mixer.hpp"

class GameState {
private:
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    std::vector<Character*> characters;
    Rob* rob;
    bool isSkillActivated;
    Skills* activatedSkill;
    SDL_Point collisionPosition;
    Menu* menu;
    int totalScore;
    SDL_Texture* scoreTexture;
    TTF_Font* font;
    SDL_Color textColor;


public:
    GameState(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~GameState();
    void handleEvent(SDL_Event& e);
    void update();
    void render();
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    void showInfoImage(const std::string& imagePath);
};

#endif // !GAMESTATE_HPP
