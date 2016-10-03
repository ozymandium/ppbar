#include <ppbar/widgets.hpp>
#include <ppbar/progress_bar.hpp>

using namespace ppbar;

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

Widget::Widget(const ProgressBar* const pb)
:   pb_(pb)
{

}

Counter::Counter(const ProgressBar* const pb)
:   Widget(pb)
,   N_strlen_(numDigits(pb->extent()))
{

}

const char* Counter::refresh()
{
    sprintf(str_, "%*i / %i", N_strlen_, pb_->index(), pb_->extent());
    return str_;
}

Timer::Timer(const ProgressBar* const pb)
:   Widget(pb)
{

}

const char* Timer::refresh()
{
    // by the time this function has been called, `pb_::last_refresh_` has been 
    // updated.
    double total_elapsed = chrono::duration<double>(pb_->lastRefresh() - pb_->startTime()).count();
    double time_per_epoch = total_elapsed / (double) (pb_->index() - pb_->startIndex());
    double remaining = time_per_epoch * (pb_->extent() - pb_->index());
    sprintf(str_, "( %.1f / %.1f )", total_elapsed, remaining);
    return str_;
}