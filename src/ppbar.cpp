#include <ppbar/ppbar.hpp>

using namespace ppbar;


constexpr chrono::milliseconds ProgressBar::REFRESH_PERIOD;


ProgressBar::T num_digits(ProgressBar::T number){
    ProgressBar::T i = 0;
    if (number < 0) {
        i += 1;
        number *= -1;
    }
    while (number > pow(10, i)) i++;
    return i;
}

ProgressBar::ProgressBar(size_t N)
:   N_(N)
,   n_(0)
,   start_time_(chrono::steady_clock::now())
,   last_refresh_(start_time_)
{
    N_strlen_ = num_digits(N_);
}

void ProgressBar::update(T n)
{
    Time now = chrono::steady_clock::now();
    if (now - last_refresh_ >= REFRESH_PERIOD)
    {
        n_ = n;
        double total_elapsed = chrono::duration<double>(now - start_time_).count();
        double time_per_epoch = total_elapsed / (double) n_;
        double remaining = time_per_epoch * (N_ - n_);

        // TODO pad using setw?

        // cout << endl;
        cout << "\r"
             << n_ << " / " << N_ << " ( " << total_elapsed << " / " << remaining << " )  "
             << std::flush;

        last_refresh_ = now;
    }
    else
    {
        // cout << "not refreshing" << endl;
    }
}