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


class Calculagraph
{
public:
    enum CalculagraphState{ RUNNING, PAUSED, STOP, TERMINATED };

    Calculagraph() { initiate(); }

    CalculagraphState getState() const
    {
        return state;
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
                start = getCurrent();
                return true;
            case TERMINATED:
                state = RUNNING;
                duration = 0;
                start = getCurrent();
                return true;
            default: // RUNNING
                return false;
        }
    }

    bool togglePause()
    {
        switch (state)
        {
            case RUNNING:
                state = PAUSED;
                duration += getCurrent() - start;
                start += duration;
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
                start = getCurrent();
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
                duration += getCurrent() - start;
                start += duration;
                return true;
            case PAUSED:
                state = RUNNING;
                return true;
            case STOP:
                state = RUNNING;
                start = getCurrent();
                return true;
            default: // TERMINATED
                return false;
        }
    }

    bool toggleStop()
    {
        switch (state)
        {
            case RUNNING:
                state = STOP;
                duration += getCurrent() - start;
                return true;
            case PAUSED:
                state = TERMINATED;
                duration += getCurrent() - start;
                return true;
            case STOP:
                state = TERMINATED;
                return true;
            default: // TERMINATED:
                return false;
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
    uint64_t getCurrent() const
    {
        timespec current;
        timespec_get(&current, TIME_UTC);
        return current.tv_sec * 1000000 + current.tv_nsec / 1000;
    }

    uint64_t getDuration() const
    {
        switch (state)
        {
            case PAUSED:
            case STOP:
                return duration;
            case RUNNING:
                return duration + getCurrent() - start;
            default: // TERMINATED
                return 0;
        }
    }
private:
    uint64_t start;
    CalculagraphState state;
    uint64_t duration;
};



#endif // CALCULAGRAPH_HPP_INCLUDED
