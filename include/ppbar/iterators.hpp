#pragma once

#include <functional>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBar;

class Iterator
{
public:

    Iterator(ProgressBar* const pb, std::function<const T& (void)> getter);
    
    const T& get() const;

    Iterator& operator++();
    
    const T& operator*() const;

protected:

    ProgressBar* pb_;

    std::function<const T& (void)> getter_;

};


bool operator!=(const Iterator& lhs, const Iterator& rhs);

bool operator!=(Iterator& lhs, Iterator& rhs);


} // close namespace ppbar