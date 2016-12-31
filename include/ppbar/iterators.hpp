#pragma once

#include <functional>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBarBase;

class RangeIterator
{
public:

    RangeIterator(ProgressBarBase* const pb, std::function<const T& (void)> getter);
    
    const T& get() const;

    RangeIterator& operator++();
    
    const T& operator*() const;

    bool operator!=(const RangeIterator& other) const;

protected:

    ProgressBarBase* pb_;

    std::function<const T& (void)> getter_;

};

} // close namespace ppbar
