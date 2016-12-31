#pragma once

#include <iostream> 
#include <string> 
#include <chrono>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <vector>
#include <memory>
#include <utility>

#include "common.hpp"
#include "iterators.hpp"
#include "widgets.hpp"


using namespace std;


namespace ppbar
{

typedef chrono::time_point<chrono::steady_clock> Time;

/// how often to update the terminal
constexpr chrono::milliseconds REFRESH_PERIOD{1000};

class ProgressBarBase
{
public:

    // ProgressBar(T n0, T N, T dn);
    // ProgressBar(T n0, T N);
    // ProgressBar(T N);
    // ~ProgressBar();
    virtual void update(T n) = 0;
    virtual ProgressBarBase& operator++() = 0;
    virtual ProgressBarBase& operator+=(T dn) = 0;
    virtual const T& operator()() = 0;
    virtual void cleanup() = 0;
    virtual const Time& lastRefresh() const = 0;
    virtual const Time& startTime() const = 0;
    virtual const T& index() const = 0;
    virtual const T& startIndex() const = 0;
    virtual const T& extent() const = 0;
    virtual RangeIterator begin() = 0;
    virtual RangeIterator end() = 0;
protected:

};

/**
 *  @brief Class for progress bar...
 */
template <typename ...W>
class ProgressBar : public ProgressBarBase
{

public:

    /**
     *  @brief The full constructor. All other constructors send default arguments
     *  here where necessary.
     *  @param n0 starting index
     *  @param N end epoch (right side open ended interval)
     *  @param dn default increment
     */
    ProgressBar(T n0, T N, T dn);

    /**
     *  @param n0 starting index
     *  @param N end epoch (right side open ended interval)
     */
    ProgressBar(T n0, T N);

    /**
     *  @param N total number of epochs, starting from zero.
     */
    ProgressBar(T N);

    /**
     *  @brief Perform clean-up on exit.
     */
    ~ProgressBar();

    /**
     *  @brief set current epoch. Beware, going backward is untested.
     */
    virtual void update(T n);

    /**
     *  @brief Increment by one.
     */
    virtual ProgressBar& operator++();

    /**
     *  @brief Increment by given number of epochs.
     */
    virtual ProgressBar& operator+=(T dn);

    /**
     *  @brief Get a reference to the current index. Sugar for `index()`.
     */
    virtual const T& operator()();

    /**
     *  @brief just prints a newline so the next terminal print is not dangling.
     *  TODO: clear away the progress bar (overwrite with space, then \r ?)
     *  TODO: print elapsed time
     */
    virtual void cleanup();

    /**
     *  @brief Time of the last refresh
     */
    virtual const Time& lastRefresh() const;

    /**
     *  @brief Time the progress bar was created. It is expected this should be 
     *  very close to the start of the loop.
     */
    virtual const Time& startTime() const;

    virtual const T& index() const;

    virtual const T& startIndex() const;

    virtual const T& extent() const;

    virtual RangeIterator begin();

    virtual RangeIterator end();

protected:
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

    vector<unique_ptr<Widget>> widgets_;

};

////////////////////////////////////////////////////////////////////////////////

template <typename ...W>
ProgressBar<W...>::ProgressBar(T n0, T N, T dn)
:   N_(N)
,   n0_(n0)
,   n_(n0_)
,   dn_(dn)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_ - REFRESH_PERIOD)
{
    [](...){ }((widgets_.push_back(std::unique_ptr<W>(new W(this))), 0)...);
    update(n_);
};

template <typename ...W>
ProgressBar<W...>::ProgressBar(T n0, T N)
:   ProgressBar(n0, N, 1)
{};

template <typename ...W>
ProgressBar<W...>::ProgressBar(T N)
:   ProgressBar(0, N)
{};

template <typename ...W>
ProgressBar<W...>::~ProgressBar()
{
    cleanup();
};

template <typename ...W>
void ProgressBar<W...>::update(T n)
{
    n_ = n;
    Time now = chrono::steady_clock::now();
    if (now - last_refresh_ >= REFRESH_PERIOD)
    {
        last_refresh_ = now;

        /// reset to beginning of line
        printf("\r");

        for (auto& wp : widgets_)
        {
            printf(wp->refresh());
            printf(" ");
        }

        cout << flush;

    }
};

template <typename ...W>
ProgressBar<W...>& ProgressBar<W...>::operator++()
{
    update(n_ + dn_);
    return *this;
};

template <typename ...W>
ProgressBar<W...>& ProgressBar<W...>::operator+=(T dn)
{
    update(n_ + dn);
    return *this;
};

template <typename ...W>
const T& ProgressBar<W...>::operator()()
{
    return n_;
};

template <typename ...W>
void ProgressBar<W...>::cleanup()
{
    cout << endl;
};

template <typename ...W>
const Time& ProgressBar<W...>::lastRefresh() const
{
    return last_refresh_;
};

template <typename ...W>
const Time& ProgressBar<W...>::startTime() const
{
    return start_time_;
};

template <typename ...W>
const T& ProgressBar<W...>::index() const
{
    return n_;
};

template <typename ...W>
const T& ProgressBar<W...>::startIndex() const
{
    return n0_;
};

template <typename ...W>
const T& ProgressBar<W...>::extent() const
{
    return N_;
};

template <typename ...W>
RangeIterator ProgressBar<W...>::begin()
{
    return RangeIterator(this, std::bind(&ProgressBar::index, this));
};

template <typename ...W>
RangeIterator ProgressBar<W...>::end()
{
    return RangeIterator(this, std::bind(&ProgressBar::extent, this));
};

} // close namespace ppbar

