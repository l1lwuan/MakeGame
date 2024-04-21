#include "mixer.hpp"
#include <iostream>

Mixer::Mixer() : music(nullptr) {}

Mixer::~Mixer() {
    close();
}

bool Mixer::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to open audio: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Mixer::close() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    Mix_CloseAudio();
}

bool Mixer::loadMusic(const std::string& filePath) {
    music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Mixer::playMusic(int loops) {
    if (Mix_PlayMusic(music, loops) == -1) {
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
    }
}

void Mixer::pauseMusic() {
    Mix_PauseMusic();
}

void Mixer::resumeMusic() {
    Mix_ResumeMusic();
}

void Mixer::stopMusic() {
    Mix_HaltMusic();
}
