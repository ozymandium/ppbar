#include <ppbar/ppbar.hpp>
#include <thread>
// #include <chrono>

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
    ppbar::ProgressBar pb(100);
    for (int k = 0; k < 100; k++)
    {
        pb();
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
        default:
            cout << "Unknown example." << endl;
            break;
    }
    return 0;
}