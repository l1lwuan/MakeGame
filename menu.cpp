#include "menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer)
    : renderer(renderer), font(nullptr), backgroundTexture(nullptr) {
    font = TTF_OpenFont("font.tff", 40);
    Start = { 530, 400, 200, 100 };
    Info = { 530, 500, 200, 100 };

    // Load background image from file
    SDL_Surface* backgroundSurface = IMG_Load("menu.png");
    if (!backgroundSurface) {
        // Handle error if image loading fails
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    }
    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
        SDL_FreeSurface(backgroundSurface);
    }
}

Menu::~Menu() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    // Destroy background texture
    if (backgroundTexture != nullptr) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

void Menu::render() {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the background image if it exists
    if (backgroundTexture != nullptr) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }
    else {
        // If background image doesn't exist, render a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, NULL);
    }

    // Render transparent rectangles for Start and Info buttons
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Set blend mode to blend

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // Set transparent white color
    SDL_RenderFillRect(renderer, &Start);
    SDL_RenderFillRect(renderer, &Info);

    // Render button text
    SDL_Color textColor = { 0, 0, 0, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, "Start", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { Start.x + 50, Start.y + 10, 100, 30 };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, "Info", textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    textRect = { Info.x + 20, Info.y + 10, 160, 30 };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // Reset blend mode to default
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Present the renderer
    SDL_RenderPresent(renderer);
}


std::string Menu::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= Start.x && mouseX <= Start.x + Start.w && mouseY >= Start.y && mouseY <= Start.y + Start.h) {
            return "start";
        }
        else if (mouseX >= Info.x && mouseX <= Info.x + Info.w && mouseY >= Info.y && mouseY <= Info.y + Info.h) {
            return "info";
        }
    }
    return "";
}
