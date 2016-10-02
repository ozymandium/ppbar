#pragma once

#include <functional>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBar;

class RangeIterator
{
public:

    RangeIterator(ProgressBar* const pb, std::function<const T& (void)> getter);
    
    const T& get() const;

    RangeIterator& operator++();
    
    const T& operator*() const;

    bool operator!=(const RangeIterator& other) const;

protected:

    ProgressBar* pb_;

    std::function<const T& (void)> getter_;

};

} // close namespace ppbar
