#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL.h>
#include <SDL_image.h>

class Character {
public:
    Character(SDL_Renderer* renderer, const char* imagePath, int x, int y, int minX, int maxX, int minY, int maxY, int frameWidth, int frameHeight, int numFrames, int speed);
    ~Character();
    void render();
    void move();
    void updateAnimation();

private:
    SDL_Rect destRect;
    SDL_Renderer* renderer;
    SDL_Texture* spriteSheet;
    int numFrames;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int minX;
    int minY;
    int maxX;
    int maxY;
    int posX;
    int posY;
    int speed;
    bool movingLeft;
};

#endif // CHARACTER_HPP
