#include <ppbar/progress_bar.hpp>
#include <ppbar/iterators.hpp>
#include <ppbar/widgets.hpp>

using namespace ppbar;


constexpr chrono::milliseconds ProgressBar::REFRESH_PERIOD;

ProgressBar::ProgressBar(T n0, T N, T dn, const initializer_list<WidgetType&>& widgets = {WidgetType::Counter, WidgetType::Timer})
:   N_(N)
,   n0_(n0)
,   n_(n0_)
,   dn_(dn)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{
    for (WidgetType& wt : widgets)
    {
        widgets_.push_back(getWidget(wt, this));
    }
    // widgets_.push_back(unique_ptr<Counter>(new Counter(this)));
    // widgets_.push_back(unique_ptr<Timer>(new Timer(this)));
}

ProgressBar::ProgressBar(T n0, T N)
:   ProgressBar(n0, N, 1)
{

}

ProgressBar::ProgressBar(T N)
:   ProgressBar(0, N)
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

        for (auto& wp : widgets_)
        {
            printf(wp->refresh());
            printf(" ");
        }

        cout << flush;

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
