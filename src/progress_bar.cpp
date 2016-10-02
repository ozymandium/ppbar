#include <ppbar/progress_bar.hpp>
#include <ppbar/iterators.hpp>

using namespace ppbar;


constexpr chrono::milliseconds ProgressBar::REFRESH_PERIOD;

/// ugly, but faster than doing math.
/// only works for types in the `int` family.
uint8_t numDigits(T x)  
{
    uint8_t sz = 0;
    if (x < 0)
    {
        x = -x; // `fabs` / `abs` require knowing the type...
        sz = 1;
    }
    sz +=
        (x < 10 ? 1 : 
        (x < 100 ? 2 : 
        (x < 1000 ? 3 :   
        (x < 10000 ? 4 :   
        (x < 100000 ? 5 :   
        (x < 1000000 ? 6 :   
        (x < 10000000 ? 7 :  
        (x < 100000000 ? 8 :  
        (x < 1000000000 ? 9 :
        (x < 10000000000 ? 10 :
        (x < 100000000000 ? 11 :
        (x < 1000000000000 ? 12 :
        (x < 10000000000000 ? 13 :
        (x < 100000000000000 ? 14 :
        (x < 1000000000000000 ? 15 :
        (x < 10000000000000000 ? 16 :
        (x < 100000000000000000 ? 17 :
        (x < 1000000000000000000 ? 18 :
        19 ))))))))))))))))));  
}

ProgressBar::ProgressBar(T N)
:   N_(N)
,   N_strlen_(numDigits(N_))
,   n0_(0)
,   n_(n0_)
,   dn_(1)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{

}

ProgressBar::ProgressBar(T n0, T N)
:   N_(N)
,   N_strlen_(numDigits(N_))
,   n0_(n0)
,   n_(n0_)
,   dn_(1)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{

}

ProgressBar::ProgressBar(T n0, T N, T dn)
:   N_(N)
,   N_strlen_(numDigits(N_))
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
        double total_elapsed = chrono::duration<double>(now - start_time_).count();
        double time_per_epoch = total_elapsed / (double) (n_ - n0_);
        double remaining = time_per_epoch * (N_ - n_);
        
        /// reset to beginning of line
        printf("\r");

        // epoch counter
        printf("%*i / %i", N_strlen_, n_, N_);

        // space between widgets
        printf(" ");
        
        // timer
        printf("( %.1f / %.1f )", total_elapsed, remaining);

        // space for cursor and flush
        cout << " " << flush;

        last_refresh_ = now;
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

const T& ProgressBar::index() const
{
    return n_;
};

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
