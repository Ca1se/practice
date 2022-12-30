#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include <cstdint>
#include <stdint.h>

class GameTimer {
public:
    GameTimer();

    float game_time() const;
    float delta_time() const;

    void reset();
    void start();
    void stop();
    void tick();

private:
    double  m_seconds_per_count;

    int64_t m_delta_time;
    int64_t m_base_time;
    int64_t m_paused_time;
    int64_t m_stop_time;
    int64_t m_prev_time;

    bool m_stopped;
};

#endif // game_timer.hpp