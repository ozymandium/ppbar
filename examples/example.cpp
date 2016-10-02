#include <ppbar/ppbar.hpp>
#include <thread>
#include <chrono>

using namespace std;


void example1()
{
    ppbar::ProgressBar pb(200);
    for (int k = 0; k < 200; k += 2)
    {
        pb.update(k);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void example2()
{
    ppbar::ProgressBar pb(1000);
    for (int k = 0; k < 1000; k++)
    {
        ++pb;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void example3()
{
    ppbar::ProgressBar pb(100);
    for (int k = 0; k < 100; k += 1)
    {
        pb += 1;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void example4()
{
    for (size_t k : ppbar::ProgressBar(100))
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main(int argc, char* argv[])
{
    switch (atoi(argv[1]))
    {
        case 1:
            example1();
            break;
        case 2:
            example2();
            break;
        case 3:
            example3();
            break;
        case 4:
            example4();
            break;
        default:
            cout << "Unknown example." << endl;
            break;
    }
    return 0;
}