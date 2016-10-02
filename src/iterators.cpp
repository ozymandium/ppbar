#include <ppbar/iterators.hpp>
#include <ppbar/progress_bar.hpp>

using namespace ppbar;


RangeIterator::RangeIterator(ProgressBar* const pb, std::function<const T& (void)> getter)
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
