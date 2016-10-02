# ppbar
Handy progress bar for C++11

Supports range iterators similar to Boost `irange`:

    for (int k : ppbar::ProgressBar(0, 100, 1) {
      doWork(k);
    }
    
Developed on GCC 6.2.1, but earlier C++11 compilers should work as well.
