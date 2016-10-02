#pragma once

#include <string>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBar;

class Widget
{
public:
    Widget(const ProgressBar* const pb);
    ~Widget() = default;
    virtual const char* refresh() = 0;
protected:
    const ProgressBar* const pb_;
    char str_[1024];
};


class Counter : public Widget
{
public:
    Counter(const ProgressBar* const pb);
    virtual const char* refresh();
protected:
    size_t N_strlen_;
};

class Timer : public Widget
{
public:
    Timer(const ProgressBar* const pb);
    virtual const char* refresh();
};

} // namespace ppbar