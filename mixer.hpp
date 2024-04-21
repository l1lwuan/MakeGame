#ifndef MIXER_HPP
#define MIXER_HPP

#include <SDL_mixer.h>
#include <string>

class Mixer {
public:
    Mixer();
    ~Mixer();
    bool init();
    void close();
    bool loadMusic(const std::string& filePath);
    void playMusic(int loops = -1);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();

private:
    Mix_Music* music;
};

#endif // MIXER_HPP
