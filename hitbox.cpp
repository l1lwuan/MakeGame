#include "hitbox.hpp"

Hitbox::Hitbox(SDL_Renderer* renderer, int x, int y, int width, int height)
    : renderer(renderer) {
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}

Hitbox::~Hitbox() {
    // Không cần hàm hủy vì không có bộ nhớ động được cấp phát
}

void Hitbox::render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Đặt màu về mặc định
}

void Hitbox::updatePosition(int x, int y, double angle, int radius) {
    // Cập nhật vị trí của hitbox theo vị trí và góc của nhân vật
    rect.x = x + static_cast<int>(radius * -cos(angle)) - rect.w / 2;
    rect.y = y + static_cast<int>(radius * -sin(angle)) - rect.h / 2;
}
