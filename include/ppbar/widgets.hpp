#pragma once

#include <string>
#include <exception>
#include <memory>

#include "common.hpp"


namespace ppbar
{

// forward declaration
class ProgressBar;

enum class WidgetType
{
    Counter,
    Timer,
};

shared_ptr<Widget> getWidget(WidgetType type, const ProgressBar* const);

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


class CounterWidget : public Widget
{
public:
    CounterWidget(const ProgressBar* const pb);
    virtual const char* refresh();
protected:
    size_t N_strlen_;
};

class TimerWidget : public Widget
{
public:
    TimerWidget(const ProgressBar* const pb);
    virtual const char* refresh();
};

} // namespace ppbar