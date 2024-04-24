//#ifndef PLAYER_HPP
//#define PLAYER_HPP
//
//#include <SDL.h>
//#include <SDL_image.h>
//#include <cmath>
//#include <vector>
//#include <chrono>
//
//class Player {
//public:
//    Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int radius);
//    ~Player();
//    void render();
//    void update();
//    void handleEvent(SDL_Event& e);
//private:
//    SDL_Rect destRect;
//    SDL_Renderer* renderer;
//    SDL_Texture* image;
//    int centerX;
//    int centerY;
//    int radius;
//    double angle;
//    bool round;
//    bool isMoving=true;
//    std::chrono::time_point<std::chrono::steady_clock> lastSpacePressTime;
//    const std::chrono::seconds cooldownTime{ 3 };
//};
//
//#endif // PLAYER_HPP
