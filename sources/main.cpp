#include <pch.hpp>
#include <fmt/format.h>
#include <ThreadPool/ThreadPool.hpp>

int main()
{
    ::xrn::ThreadPool tp{ 20 };
    ::std::atomic value{ 0uz };
    for (auto i{ 0uz }; i < 100; ++i) {
        tp.push([&value]{
            ::fmt::print("enter lambda: {}\n", value);
            ::std::this_thread::sleep_for(250ms);
            value++;
            ::fmt::print("exit lambda: {}\n", value);
        });
    }
    tp.join();
    ::fmt::print("final value: {}\n", value);
    return 0;
}
