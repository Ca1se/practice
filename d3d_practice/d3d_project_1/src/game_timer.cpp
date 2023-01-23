#include <windows.h>
#include <winerror.h>

#include "game_timer.hpp"


GameTimer::GameTimer():
    m_seconds_per_count(0.0), m_delta_time(-1.0), m_base_time(0),
    m_paused_time(0), m_stop_time(0), m_prev_time(0), m_stopped(false)
{
    int64_t counts_per_sec = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*) &counts_per_sec);
    m_seconds_per_count = 1.0 / (double) counts_per_sec;
}

inline float GameTimer::game_time() const
{
    if(m_stopped)
        return (float) ((m_stop_time - m_paused_time - m_base_time) * m_seconds_per_count);
    
    int64_t curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*) &curr_time);

    return (float) ((curr_time - m_paused_time - m_base_time) * m_seconds_per_count);
}

inline float GameTimer::delta_time() const
{
    return (float) (m_delta_time * m_seconds_per_count);
}

void GameTimer::reset()
{
    int64_t curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*) &curr_time);

    m_base_time = curr_time;
    m_prev_time = curr_time;
    m_stop_time = 0;
    m_stopped   = false;
}

void GameTimer::start()
{
    if(m_stopped) {
        int64_t curr_time = 0;
        QueryPerformanceCounter((LARGE_INTEGER*) &curr_time);

        m_paused_time  += curr_time - m_stop_time;
        m_prev_time     = curr_time;
        m_stop_time     = 0;
        m_stopped       = false;
    }
}

void GameTimer::stop()
{
    if(!m_stopped) {
        int64_t curr_time = 0;
        QueryPerformanceCounter((LARGE_INTEGER*) &curr_time);

        m_stop_time = curr_time;
        m_stopped   = true;
    }
}

inline void GameTimer::tick()
{
    if(m_stopped) {
        m_delta_time = 0;
        return;
    }

    int64_t curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*) &curr_time);

    m_delta_time = curr_time - m_prev_time;
    m_prev_time = curr_time;

    if(m_delta_time < 0)
        m_delta_time = 0;
}

