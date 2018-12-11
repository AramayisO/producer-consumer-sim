#ifndef TS_PRINTF_H
#define TS_PRINTF_H

#include <mutex>

template <typename... Args>
int tsprintf(const char *fmt, Args... args)
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    return std::printf(fmt, args...);
}

#endif