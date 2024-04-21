#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "background.hpp"
#include "character.hpp"
#include "player.hpp"
#include "timer.hpp"
#include "rob.hpp"
#include "mixer.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Color textColor = { 0, 0, 0, 255 };
TTF_Font* font = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
        std::cout << "Failed";
        return false;
    }

    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1260, 780, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Failed";
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "Failed";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("Amatic-Bold.ttf", 40);
    if (font == nullptr) {
        std::cout << "Failed";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
}

void renderText(const std::string& text, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 40;
    int texH = 40;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    SDL_Rect dstRect = { 630, 0, texW, texH };

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

std::string formatTime(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::string formattedTime = std::to_string(minutes) + ":";

    if (remainingSeconds < 10) {
        formattedTime += "0";
    }

    formattedTime += std::to_string(remainingSeconds);

    return formattedTime;
}

int main(int argc, char* argv[]) {

    if (!init()) {
        return 1;
    }

    Background background1(renderer, "lastone.png");

    int centerX = 650;
    int centerY = 330;
    int radius = 65;
    Player player(renderer, "pointer.png", centerX, centerY, radius);

    Rob rob(renderer, "daycau.png", 650, 330, 0);

    Timer timer;
    timer.start();

    Mixer mixer;
    if (!mixer.loadMusic("merx-market-song-33936.mp3")) {
        std::cerr << "Failed to load background music" << std::endl;
        return 1;
    }
    mixer.playMusic(-1);

    Character fish0(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 1);
    Character fish1(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 2);
    Character fish2(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 1);
    Character fish3(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 2);
    Character fish4(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 1);
    Character fish5(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 1);
    Character fish6(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 2);
    Character fish7(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 3);
    Character fish8(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 3);
    Character fish9(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 3);
    Character fish10(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 3);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            player.handleEvent(event);
            rob.handleEvent(event);
        }
        player.update();

        rob.update();

        fish0.move(1260, 780);
        fish1.move(1260, 780);
        fish2.move(1260, 780);
        fish3.move(1260, 780);
        fish4.move(1260, 780);
        fish5.move(1260, 780);
        fish6.move(1260, 780);
        fish7.move(1260, 780);
        fish8.move(1260, 780);
        fish9.move(1260, 780);
        fish10.move(1260, 780);

        fish0.updateAnimation();
        fish1.updateAnimation();
        fish2.updateAnimation();
        fish3.updateAnimation();
        fish4.updateAnimation();
        fish5.updateAnimation();
        fish6.updateAnimation();
        fish7.updateAnimation();
        fish8.updateAnimation();
        fish9.updateAnimation();
        fish10.updateAnimation();
        SDL_RenderClear(renderer);

        background1.render({ 0, 0, 1260, 780 });

        player.render();

        rob.render();

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
        fish10.render();
        int timePlayed = timer.getTicks() / 1000;
        std::string formattedTime = formatTime(timePlayed);
        renderText(formattedTime, 10, 10);

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}