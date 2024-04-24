#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL.h>
#include <SDL_image.h>

class Character {
public:
    Character(SDL_Renderer* renderer, const char* imagePath, int screenWidth, int screenHeight, int frameWidth, int frameHeight, int numFrames, int speed);
    ~Character();
    void render();
    void move(int screenWidth, int screenHeight);
    void updateAnimation();
    void touched();
    SDL_Rect getDestRect();
private:
    SDL_Rect destRect;
    SDL_Rect hitbox;
    SDL_Renderer* renderer;
    SDL_Texture* spriteSheet;
    int numFrames;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int posX;
    int posY;
    int speed;
    bool movingLeft;
    bool isMoving = true;

    SDL_Surface* remove(SDL_Surface* surface);
};

#endif // CHARACTER_HPP