/***************************************************************
 * Name:      Calculagraph.hpp
 * Purpose:   Code for Calculagraph
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-20
 **************************************************************/

#ifndef CALCULAGRAPH_HPP_INCLUDED
#define CALCULAGRAPH_HPP_INCLUDED

#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdexcept>

inline
uint64_t time_diff(timespec start, timespec stop)
{
    return (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_nsec - start.tv_nsec) / 1000;
}

inline
uint64_t time_diff(timeval start, timeval stop)
{
    return (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
}

inline
void read_time(timespec &_clock)
{
    clock_gettime(CLOCK_MONOTONIC, &_clock);
}

inline
void read_time(timeval &_clock)
{
    gettimeofday(&_clock, NULL);
}

template <class _TimeType>
class BaseCalculagraph
{
public:
    enum CalculagraphState{ RUNNING, PAUSED, STOP, TERMINATED };
    typedef _TimeType TimeType;

    BaseCalculagraph() { initiate(); }

    CalculagraphState getState() const
    {
        return state();
    }

    void initiate()
    {
        state = TERMINATED;
        duration = 0;
    }

    bool toggleStart()
    {
        switch (state)
        {
            case PAUSED:
                state = RUNNING;
                return true;
            case STOP:
                state = RUNNING;
                read_time(start);
                return true;
            case TERMINATED:
                state = RUNNING;
                duration = 0;
                read_time(start);
                return true;
            case RUNNING:
                return false;
            default:
                throw std::logic_error("toggle start error");
        }
    }

    bool togglePause()
    {
        switch (state)
        {
            case RUNNING:
                state = PAUSED;
                read_time(stop);
                duration += time_diff(start, stop);
                start = stop;
                return true;
            default:
                return false;
        }
    }

    bool toggleContinue()
    {
        switch (state)
        {
            case STOP:
                read_time(start);
            case PAUSED:
                state = RUNNING;
                return true;
            default:
                return false;
        }
    }

    bool togglePauseContinue()
    {
        switch (state)
        {
            case RUNNING:
                state = PAUSED;
                read_time(stop);
                duration += time_diff(start, stop);
                start = stop;
                return true;
            case PAUSED:
                state = RUNNING;
                return true;
            case STOP:
                state = RUNNING;
                read_time(start);
                return true;
            case TERMINATED:
                return false;
            default:
                throw std::logic_error("toggle pause/continue error");
        }
    }

    bool toggleStop()
    {
        switch (state)
        {
            case RUNNING:
                state = STOP;
                read_time(stop);
                duration += time_diff(start, stop);
                return true;
            case PAUSED:
                state = TERMINATED;
                read_time(stop);
                duration += time_diff(start, stop);
                return true;
            case STOP:
                state = TERMINATED;
                return true;
            case TERMINATED:
                return false;
            default:
                throw std::logic_error("toggle stop error");
        }
    }

    uint64_t get_msec() const
    {
        return getDuration() / 1000;
    }

    uint64_t get_usec() const
    {
        return getDuration();
    }

protected:
    uint64_t getDuration() const
    {
        switch (state)
        {
            case PAUSED:
            case STOP:
                return duration;
            case TERMINATED:
                return 0;
            case RUNNING:
                read_time(stop);
                return duration + time_diff(start, stop);
            default:
                throw std::logic_error("getting duration error");
        }
    }
private:
    TimeType start;
    mutable TimeType stop;
    CalculagraphState state;
    uint64_t duration;
};

typedef BaseCalculagraph<timespec> Calculagraph;



#endif // CALCULAGRAPH_HPP_INCLUDED
