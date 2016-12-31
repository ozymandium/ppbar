#pragma once

#include <string>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBarBase;

class Widget
{
public:
    Widget(const ProgressBarBase* const pb);
    ~Widget() = default;
    virtual const char* refresh() = 0;
protected:
    const ProgressBarBase* const pb_;
    char str_[1024];
};


class Counter : public Widget
{
public:
    Counter(const ProgressBarBase* const pb);
    virtual const char* refresh();
protected:
    size_t N_strlen_;
};

class ETA : public Widget
{
public:
    ETA(const ProgressBarBase* const pb);
    virtual const char* refresh();
};

} // namespace ppbar