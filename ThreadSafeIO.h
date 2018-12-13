#ifndef THREAD_SAFE_IO_H
#define THREAD_SAFE_IO_H

#include <mutex>

namespace ThreadSafeIO
{
    /**
     * Since the stdout stream is a shared resource among all the  threads,
     * this wrapper function makes the std::printf function thread safe
     * by using a mutex to allow only one thread to write to stdout at a time.
     * 
     * @param fmt  format string same as the first argument to std::printf. 
     * @param args additional arguments same as those passed to std::printf.
     */
    template <typename... Args>
    int printf(const char *fmt, Args... args)
    {
        static std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        return std::printf(fmt, args...);
    }
}


#endif