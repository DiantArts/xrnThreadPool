#include <pch.hpp>
#include <fmt/format.h>
#include <ThreadPool/ThreadPool.hpp>

int main()
{
    ::xrn::ThreadPool tp;
    ::xrn::ThreadPool tp2{ ::std::move(tp) };
    tp = ::std::move(tp2);
    ::std::atomic value{ 0uz };
    for (auto i{ 0uz }; i < 100; ++i) {
        tp.push([&value]{
            ::fmt::print("enter lambda: {}\n", value);
            ::std::this_thread::sleep_for(1000ms);
            value++;
            ::fmt::print("exit lambda: {}\n", value);
        });
    }
    ::std::this_thread::sleep_for(500ms);
    ::fmt::print("Waiting\n");
    tp.join();
    ::fmt::print("final value: {}\n", value);
    return 0;
}
