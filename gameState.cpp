#include "gameState.hpp"

GameState::GameState(SDL_Renderer* renderer, int screenWidth_, int screenHeight_)
    : renderer(renderer), screenWidth(screenWidth_), screenHeight(screenHeight_) {
    textColor = { 255, 0, 0, 255 };
    menu = new Menu(renderer);
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 1, 2));
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 2, 2));
    characters.push_back(new Character(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 1, 4));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 2, 1));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 1, 1));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 1, 3));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 2, 3));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 3, 3));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 3, 1));
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 3, 2));
    characters.push_back(new Character(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 3, 4));
    // Add other character initializations here
    rob = new Rob(renderer, "luoi.png", 650, 330, 30);
    totalScore = 0;
}

GameState::~GameState() {
    for (Character* character : characters) {
        delete character;
    }
    delete rob;

}

void GameState::handleEvent(SDL_Event& e) {
    if (menu) {
        std::string menuResult = menu->handleEvent(e);
        if (!menuResult.empty()) {
            if (menuResult == "start") {
                delete menu;
                menu = nullptr;
            }
            else if (menuResult == "info") {
                showInfoImage("info.png");
            }
        }
    }
    else {
        rob->handleEvent(e);
    }
}

void GameState::update() {
    for (Character* character : characters) {
        character->move(screenWidth, screenHeight);
        character->updateAnimation();
    }
    rob->update();
    SDL_Rect robRect = rob->getDestRect();
    for (Character* character : characters) {
        SDL_Rect characterRect = character->getDestRect();
        if (checkCollision(robRect, characterRect)) {
            rob->touched();
            character->touched();
            isSkillActivated = true;
            collisionPosition.x = robRect.x;
            collisionPosition.y = robRect.y;
            activatedSkill = new Skills(renderer, "shoot.png", collisionPosition.x, collisionPosition.y, 125, 94, 7, 0);
            totalScore += character->getPoint();
        }
    }
}

void GameState::render() {
    for (Character* character : characters) {
        character->render();
    }
    rob->render();
    if (isSkillActivated) {
        activatedSkill->updateAnimation();
        activatedSkill->render();
        if (activatedSkill->isEnded()) isSkillActivated = false;
    }
    font = TTF_OpenFont("arial.ttf", 40);
    if (font) {
        std::string scoreText = "Total Score: " + std::to_string(totalScore);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            if (textTexture) {
                SDL_Rect textRect = { 32, 32, 200, 50 };
                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                SDL_DestroyTexture(textTexture);
            }
        }
    }
    if (menu) {
        menu->render();
    }
}

bool GameState::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    if (a.x + a.w >= b.x && b.x + b.w >= a.x && a.y + a.h >= b.y && b.y + b.h >= a.y) {
        return true;
    }
    return false;
}

void GameState::showInfoImage(const std::string& imagePath) {
    SDL_Surface* infoSurface = IMG_Load(imagePath.c_str());
    if (!infoSurface) {
        std::cerr << "Failed to load info image: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(renderer, infoSurface);
    SDL_FreeSurface(infoSurface);
    delete menu;
    menu = nullptr;
    for (Character* character : characters) {
        delete character;
    }
    characters.clear();
    delete rob;
    rob = nullptr;
    delete activatedSkill;
    activatedSkill = nullptr;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, infoTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(infoTexture);
    SDL_Delay(9999);
}
