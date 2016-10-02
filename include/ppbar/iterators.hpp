#ifndef PPBAR__ITERATORS_HPP
#define PPBAR__ITERATORS_HPP

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

    bool operator!=(const Iterator& other) const;

protected:

    ProgressBar* pb_;

    std::function<const T& (void)> getter_;

};

// bool operator!=(const Iterator& lhs, const Iterator& rhs);
// bool operator==(const Iterator& lhs, const Iterator& rhs)
// {
//     return true;
// }

} // close namespace ppbar

#endif // #define PPBAR__ITERATORS_HPP