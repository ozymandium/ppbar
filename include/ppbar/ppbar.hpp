#pragma once

#include <iostream> 
#include <string> 
#include <chrono>
#include <cstdio>
#include <cmath>

using namespace std;


namespace ppbar
{

class ProgressBar
{
public:
    typedef size_t T;
    typedef chrono::time_point<chrono::steady_clock> Time;

    /**
     *  @param N total number of epochs.
     */
    ProgressBar(T N);

    /**
     *  @brief set current epoch.
     */
    void update(T n);

    /**
     *  @brief Increment by one.
     */
    inline void operator()() { update(n_ + 1); };

    /**
     *  @brief Increment by one.
     */
    inline void operator++() { update(n_ + 1); };

    /**
     *  @brief Increment by given number of epochs.
     */
    inline void operator+=(T dn) { update(n_ + dn); };

protected:
    static constexpr chrono::milliseconds REFRESH_PERIOD = chrono::milliseconds(250);

    /// Total number of epochs
    T N_;

    /// 
    T N_strlen_;

    /// The current epoch
    T n_;

    /// Beginning 
    const Time start_time_;

    /// 
    Time last_refresh_;

};

}