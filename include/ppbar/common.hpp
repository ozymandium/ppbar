#pragma once

#include <cstddef>
#include <chrono>


using namespace std;


namespace ppbar
{

typedef int T;

typedef chrono::time_point<chrono::steady_clock> Time;

/// how often to update the terminal
constexpr chrono::milliseconds REFRESH_PERIOD{1000};


}