#include "background.hpp"

SDL_Surface* removeWhiteBackground(SDL_Surface* surface) {
    if (surface == nullptr) {
        std::cerr << "Invalid surface" << std::endl;
        return nullptr;
    }

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);

    SDL_SetColorKey(surface, SDL_TRUE, white);

    return surface;
}


Background::Background(SDL_Renderer* renderer, const char* imagePath) : renderer(renderer) {
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        std::cerr << "Failed to load " << imagePath << ": " << IMG_GetError() << std::endl;
        return;
    }

    surface = removeWhiteBackground(surface);
    if (!surface) {
        std::cerr << "Failed to remove white background" << std::endl;
        return;
    }


    image = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Background::~Background() {
    SDL_DestroyTexture(image);
}

void Background::render(SDL_Rect rect) {
    SDL_RenderCopy(renderer, image, nullptr, &rect);
}