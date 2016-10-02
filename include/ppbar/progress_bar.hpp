#pragma once

#include <iostream> 
#include <string> 
#include <chrono>
#include <cstdio>
#include <cmath>
#include <iomanip>

#include "common.hpp"

using namespace std;


namespace ppbar
{

// forward declaration
class RangeIterator;

/**
 *  @brief Class for progress bar...
 */
class ProgressBar
{

public:
    typedef chrono::time_point<chrono::steady_clock> Time;

    /**
     *  @param N total number of epochs.
     */
    ProgressBar(T N);

    ~ProgressBar();

    /**
     *  @brief set current epoch. Beware, going backward is untested.
     */
    void update(T n);

    /**
     *  @brief Increment by one.
     */
    ProgressBar& operator++();

    /**
     *  @brief Increment by given number of epochs.
     */
    ProgressBar& operator+=(T dn);

    /**
     *  @brief just prints a newline so the next terminal print is not dangling.
     *  TODO: clear away the progress bar (overwrite with space, then \r ?)
     *  TODO: print elapsed time
     */
    void cleanup();

    const T& index() const;
    
    const T& extent() const;

    RangeIterator begin();

    RangeIterator end();
    
protected:
    /// how often to update the terminal
    static constexpr chrono::milliseconds REFRESH_PERIOD{250};

    /// Total number of epochs
    T N_;

    /// 
    T N_strlen_;

    /// The starting epoch
    T n0_;

    /// The current epoch
    T n_;

    /// Beginning 
    const Time start_time_;

    /// when the screen was last written
    Time last_refresh_;

};

} // close namespace ppbar