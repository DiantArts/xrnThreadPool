#include <pch.hpp>
#include <catch2/catch.hpp>
#include <ThreadPool/ThreadPool.hpp>

TEST_CASE("rule of 5", "[creation]")
{
    // ::xrn::ThreadPool tp1;
    // ::xrn::ThreadPool tp2{ ::std::move(tp1) };
    // tp1 = ::std::move(tp2);
}

TEST_CASE("basic test single thread", "[creation]")
{
    ::xrn::ThreadPool tp{ 1 };
    ::std::atomic value{ 0uz };
    for (auto i{ 0uz }; i < 1; ++i) {
        tp.push([&value]{
            ::std::this_thread::sleep_for(400ms);
            value++;
        });
    }
    ::std::this_thread::sleep_for(200ms);
    tp.join();
    REQUIRE(value == 1);
}

TEST_CASE("basic test multiple thread", "[creation]")
{
    ::xrn::ThreadPool tp{ 20 };
    ::std::atomic value{ 0uz };
    for (auto i{ 0uz }; i < 20; ++i) {
        tp.push([&value]{
            ::std::this_thread::sleep_for(400ms);
            value++;
        });
    }
    ::std::this_thread::sleep_for(200ms);
    tp.join();
    REQUIRE(value == 20);
}

TEST_CASE("basic test multiple thread multiple runs", "[creation]")
{
    ::xrn::ThreadPool tp{ 20 };
    ::std::atomic value{ 0uz };
    for (auto i{ 0uz }; i < 40; ++i) {
        tp.push([&value]{
            ::std::this_thread::sleep_for(400ms);
            value++;
        });
    }
    ::std::this_thread::sleep_for(200ms);
    tp.join();
    REQUIRE(value == 40);
}
