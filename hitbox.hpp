#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "SDL.h"

class Hitbox {
public:
    Hitbox(SDL_Renderer* renderer, int x, int y, int width, int height);
    ~Hitbox();
    void render();
    void updatePosition(int x, int y, double angle, int radius);

private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
};

#endif // HITBOX_HPP
