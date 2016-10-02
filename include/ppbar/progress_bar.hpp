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
     *  @param N total number of epochs, starting from zero.
     */
    ProgressBar(T N);

    /**
     *  @param n0 starting index
     *  @param N end epoch (right side open ended interval)
     */
    ProgressBar(T n0, T N);

    /**
     *  @param n0 starting index
     *  @param N end epoch (right side open ended interval)
     *  @param dn default increment
     */
    ProgressBar(T n0, T N, T dn);

    /**
     *  @brief Perform clean-up on exit.
     */
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
     *  @brief Get a reference to the current index. Sugar for `index()`.
     */
    const T& operator()();

    /**
     *  @brief just prints a newline so the next terminal print is not dangling.
     *  TODO: clear away the progress bar (overwrite with space, then \r ?)
     *  TODO: print elapsed time
     */
    void cleanup();

    /**
     *  @brief Time of the last refresh
     */
    const Time& lastRefresh() const;

    /**
     *  @brief Time the progress bar was created. It is expected this should be 
     *  very close to the start of the loop.
     */
    const Time& startTime() const;

    const T& index() const;

    const T& startIndex() const;
    
    const T& extent() const;

    RangeIterator begin();

    RangeIterator end();
    
protected:
    /// how often to update the terminal
    static constexpr chrono::milliseconds REFRESH_PERIOD{250};

    /// Total number of epochs
    T N_;

    /// The starting epoch
    T n0_;

    /// The current epoch
    T n_;

    /// The default increment
    T dn_;

    /// Beginning 
    const Time start_time_;

    /// when the screen was last written
    Time last_refresh_;

};

} // close namespace ppbar