#pragma once

#include <functional>

#include "progress_bar_base.hpp"


namespace ppbar
{

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

////////////////////////////////////////////////////////////////////////////////

RangeIterator::RangeIterator(ProgressBarBase* const pb, std::function<const T& (void)> getter)
:   pb_(pb)
,   getter_(getter)
{

}

RangeIterator& RangeIterator::operator++()
{
    ++(*pb_);
    return *this;
}

const T& RangeIterator::get() const
{
    return getter_();
}

const T& RangeIterator::operator*() const
{
    return get();
}


bool RangeIterator::operator!=(const RangeIterator& other) const
{
    return getter_() != other.get();
}


} // close namespace ppbar
