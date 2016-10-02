#include <ppbar/progress_bar.hpp>
#include <ppbar/iterators.hpp>
#include <ppbar/widgets.hpp>

using namespace ppbar;


constexpr chrono::milliseconds ProgressBar::REFRESH_PERIOD;

ProgressBar::ProgressBar(T N)
:   N_(N)
// ,   N_strlen_(numDigits(N_))
,   n0_(0)
,   n_(n0_)
,   dn_(1)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{

}

ProgressBar::ProgressBar(T n0, T N)
:   N_(N)
// ,   N_strlen_(numDigits(N_))
,   n0_(n0)
,   n_(n0_)
,   dn_(1)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{

}

ProgressBar::ProgressBar(T n0, T N, T dn)
:   N_(N)
// ,   N_strlen_(numDigits(N_))
,   n0_(n0)
,   n_(n0_)
,   dn_(dn)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{

}

ProgressBar::~ProgressBar()
{
    cleanup();
}

void ProgressBar::update(T n)
{
    n_ = n;
    Time now = chrono::steady_clock::now();
    if (now - last_refresh_ >= REFRESH_PERIOD)
    {
        last_refresh_ = now;

        /// reset to beginning of line
        printf("\r");

        // epoch counter
        Counter counter(this);
        printf(counter.refresh());

        // space between widgets
        printf(" ");
        
        Timer timer(this);
        printf(timer.refresh());

        // space for cursor and flush
        cout << " " << flush;

    }
}

ProgressBar& ProgressBar::operator++()
{
    update(n_ + dn_);
    return *this;
}

ProgressBar& ProgressBar::operator+=(T dn)
{
    update(n_ + dn);
    return *this;
}

const T& ProgressBar::operator()()
{
    return n_;
}

void ProgressBar::cleanup()
{
    cout << endl;
}

const ProgressBar::Time& ProgressBar::lastRefresh() const
{
    return last_refresh_;
}

const ProgressBar::Time& ProgressBar::startTime() const
{
    return start_time_;
}

const T& ProgressBar::index() const
{
    return n_;
};

const T& ProgressBar::startIndex() const
{
    return n0_;
}

const T& ProgressBar::extent() const
{
    return N_;
};

RangeIterator ProgressBar::begin()
{
    return RangeIterator(this, std::bind(&ProgressBar::index, this));
};

RangeIterator ProgressBar::end()
{
    return RangeIterator(this, std::bind(&ProgressBar::extent, this));
};
