#include "gameState.hpp"
#include "skills.hpp"

GameState::GameState(SDL_Renderer* renderer, int screenWidth_, int screenHeight_)
    : renderer(renderer), screenWidth(screenWidth_), screenHeight(screenHeight_) {
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 1));
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 2));
    characters.push_back(new Character(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 1));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 2));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 1));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 1));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 2));
    characters.push_back(new Character(renderer, "turtleSwim.png", 1260, 780, 44, 48, 6, 3));
    characters.push_back(new Character(renderer, "eelSwim.png", 1260, 780, 49, 48, 6, 3));
    characters.push_back(new Character(renderer, "squidSwim.png", 1260, 780, 44, 48, 6, 3));
    characters.push_back(new Character(renderer, "angleSwim.png", 1260, 780, 50, 48, 6, 3));
    rob = new Rob(renderer, "luoi.png", 650, 330, 30);
}

GameState::~GameState() {
    // Giải phóng bộ nhớ của các nhân vật và Rob
    for (Character* character : characters) {
        delete character;
    }
    delete rob;
}

void GameState::handleEvent(SDL_Event& e) {
    // Xử lý sự kiện cho các nhân vật và Rob ở đây
    rob->handleEvent(e);
}

void GameState::update() {
    // Cập nhật trạng thái của các nhân vật và Rob
    for (Character* character : characters) {
        character->move(screenWidth, screenHeight);
        character->updateAnimation();
    }
    rob->update();

    // Kiểm tra va chạm giữa Rob và các nhân vật
    SDL_Rect robRect = rob->getDestRect();
    for (Character* character : characters) {
        SDL_Rect characterRect = character->getDestRect();
        if (checkCollision(robRect, characterRect)) {
            // Xử lý va chạm ở đây
            rob->touched();
            character->touched();

        }
    }
}

void GameState::render() {
    // Vẽ các nhân vật và Rob lên màn hình
    for (Character* character : characters) {
        character->render();
    }
    rob->render();
}

bool GameState::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    if (a.x + a.w >= b.x && b.x + b.w >= a.x && a.y + a.h >= b.y && b.y + b.h >= a.y) {
        return true;
    }
    return false;
}

//Skills skills(render, "sk.png", );