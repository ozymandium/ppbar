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

Widget::Widget(const ProgressBarBase* const pb)
:   pb_(pb)
{

}

Counter::Counter(const ProgressBarBase* const pb)
:   Widget(pb)
,   N_strlen_(numDigits(pb->extent()))
{

}

const char* Counter::refresh()
{
    sprintf(str_, "%*i/%i", N_strlen_, pb_->index(), pb_->extent());
    return str_;
}

ETA::ETA(const ProgressBarBase* const pb)
:   Widget(pb)
{

}

const char* ETA::refresh()
{
    // by the time this function has been called, `pb_::last_refresh_` has been 
    // updated.
    double total_elapsed = chrono::duration<double>(pb_->lastRefresh() - pb_->startTime()).count();
    double remaining_sec = total_elapsed / (double) (pb_->index() - pb_->startIndex()) 
                           * (pb_->extent() - pb_->index());
    double remaining_min = remaining_sec / 60.0;
    double remaining_hr = remaining_min / 60.0;
    sprintf(str_, "%02u:%02u:%02u", 
        (uint)remaining_hr%60, (uint)remaining_min%60, (uint)remaining_sec%60);
    return str_;
}