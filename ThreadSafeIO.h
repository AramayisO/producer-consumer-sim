#ifndef THREAD_SAFE_IO_H
#define THREAD_SAFE_IO_H

#include <mutex>

namespace ThreadSafeIO
{
    template <typename... Args>
    int printf(const char *fmt, Args... args)
    {
        static std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        return std::printf(fmt, args...);
    }
}


#endif