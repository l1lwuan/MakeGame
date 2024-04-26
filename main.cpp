#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "background.hpp"
#include "character.hpp"
#include "timer.hpp"
#include "rob.hpp"
#include "mixer.hpp"
#include "gameState.hpp"
#include "skills.hpp"

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

    Timer timer;
    timer.start();

    GameState GameState(renderer, 1260, 780);

    Mixer mixer;
    if (!mixer.loadMusic("merx-market-song-33936.mp3")) {
        std::cerr << "Failed to load background music" << std::endl;
        return 1;
    }
    mixer.playMusic(-1);

  
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            GameState.handleEvent(event);
        }

        GameState.update();

        SDL_RenderClear(renderer);

        background1.render({ 0, 0, 1260, 780 });

        GameState.render();

        int timePlayed = timer.getTicks() / 1000;
        std::string formattedTime = formatTime(timePlayed);
        if (timePlayed == 180) {
            close();
        }

        renderText(formattedTime, 10, 10);

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}