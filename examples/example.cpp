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
    for (int k : ppbar::ProgressBar(100))
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void example5()
{
    for (int k : ppbar::ProgressBar(-5, 0))
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void example6()
{
    for (int k : ppbar::ProgressBar(-10, 0, 2))
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
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
        case 5:
            example5();
            break;
        case 6:
            example6();
            break;
        default:
            cout << "Unknown example." << endl;
            break;
    }
    return 0;
}