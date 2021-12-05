#pragma once

#include <Foundation>

class FrameClock
{
public:

    static constexpr ADuration<ASteadyClock::rep, std::ratio<1, 120>> HighFrameRate{1};
    static constexpr ADuration<ASteadyClock::rep, std::ratio<1, 60>> MediumFrameRate{1};
    static constexpr ADuration<ASteadyClock::rep, std::ratio<1, 30>> LowFrameRate{1};

    ASteadyClock::duration currentFrameRate = std::chrono::duration_cast<ASteadyClock::duration>(MediumFrameRate); //TODO: c++17 is ok?
    size_t currentFrame = 0;
    size_t lastFPSFrame = 0;
    size_t currentFPS = 0;
    ASteadyClock::duration accumulatedTime{};
    ASteadyClock::time_point lastFrameTime = ASteadyClock::now();

    void sync()
    {
        ++currentFrame;

        //time: 0ms                 8ms                    16ms            17ms <- this will be used
        //loop: |====================|-----------------------|----------------| as time of next frame
        //           start sleep time^  wanted sleep end time^  real sleep end^
        //    this time point will be used as last frame time^

        auto currentFrameTime = ASteadyClock::now();
        auto elapsedTime = currentFrameTime - lastFrameTime;
        auto sleepTime = currentFrameRate - elapsedTime;
        if (elapsedTime < currentFrameRate)
        {
            lastFrameTime = currentFrameTime + sleepTime;
            accumulatedTime += elapsedTime + sleepTime;
            AThread::sleep(sleepTime);
        }
        else
        {
            lastFrameTime = currentFrameTime;
            accumulatedTime += elapsedTime;
        }

        if (accumulatedTime > ASeconds(1))
        {
            currentFPS = currentFrame - lastFPSFrame;
            lastFPSFrame = currentFrame;
            accumulatedTime -= ASeconds(1);
        }
    }
};

extern FrameClock GraphicsClock; //TODO: move to Window