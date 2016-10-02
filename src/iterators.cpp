#include <ppbar/iterators.hpp>
#include <ppbar/progress_bar.hpp>

using namespace ppbar;


Iterator::Iterator(ProgressBar* const pb, std::function<const T& (void)> getter)
:   pb_(pb)
,   getter_(getter)
{

}

Iterator& Iterator::operator++()
{
    *pb_ += (T)1;
    return *this;
}

const T& Iterator::get() const
{
    return getter_();
}

const T& Iterator::operator*() const
{
    return get();
}

bool operator!=(const Iterator& lhs, const Iterator& rhs)
{
    return lhs.get() != rhs.get();
}

bool operator!=(Iterator& lhs, Iterator& rhs)
{
    return lhs.get() != rhs.get();
}