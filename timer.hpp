#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Timer {
public:
	Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int getTicks();
    bool isStarted();
    bool isPaused();
private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;
    bool mPaused;
    bool mStarted;
};

#endif // TIMER_HPP
