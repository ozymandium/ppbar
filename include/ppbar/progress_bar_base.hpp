#pragma once

#include "common.hpp"


namespace ppbar
{

class RangeIterator;

class ProgressBarBase
{
public:
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
};

}