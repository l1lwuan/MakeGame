#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "background.hpp"
#include "character.hpp"
#include "player.hpp"
#include "timer.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1260, 780, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[]) {

    if (!init()) {
        return 1;
    }

    Background background1(renderer, "deepsea.png");

    Timer timer;

    Character fish0(renderer, "squidSwim.png", 700, 500, 400, 800, 350, 350, 44, 48, 6, 1);
    Character fish1(renderer, "squidSwim.png", 300, 600, 300, 1150, 650, 650, 44, 48, 6, 2);
    Character fish2(renderer, "angleSwim.png", 500, 680, 300, 1150, 650, 650, 50, 48, 6, 1);
    Character fish3(renderer, "jellySwim.png", 1000, 450, 200, 550, 1200, 550, 50, 48, 4, 0);
    Character fish4(renderer, "jellySwim.png", 300, 490, 200, 550, 1200, 550, 50, 48, 4, 0);
    Character fish5(renderer, "jellySwim.png", 700, 530, 200, 550, 1200, 550, 50, 48, 4, 0);
    Character fish6(renderer, "eelSwim.png", 450, 550, 300, 900, 515, 515, 49, 48, 6, 1);
    Character fish7(renderer, "eelSwim.png", 600, 650, 300, 1000, 650, 650, 49, 48, 6, 2);
    Character fish8(renderer, "turtleSwim.png", 800, 400, 800, 1100, 400, 400, 44, 48, 6, 1);
    Character fish9(renderer, "turtleSwim.png", 300, 450, 300, 500, 450, 450, 44, 48, 6, 1);
    int centerX = 650;
    int centerY = 360;
    int radius = 50;
    Player player(renderer, "pointer.png", centerX, centerY, radius);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        player.update();


        fish0.move();
        fish0.updateAnimation();

        fish1.move();
        fish1.updateAnimation();


        fish2.move();
        fish2.updateAnimation();

        fish3.move();
        fish3.updateAnimation();

        fish4.move();
        fish4.updateAnimation();

        fish5.move();
        fish5.updateAnimation();

        fish6.move();
        fish6.updateAnimation();

        fish7.move();
        fish7.updateAnimation();

        fish8.move();
        fish8.updateAnimation();

        fish9.move();
        fish9.updateAnimation();
        SDL_RenderClear(renderer);
        background1.render({ 0, 0, 1260, 780 });

        player.render();

        fish0.render();
        fish1.render();
        fish2.render();
        fish3.render();
        fish4.render();
        fish5.render();
        fish6.render();
        fish7.render();
        fish8.render();
        fish9.render();

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}
