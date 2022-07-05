#include <pch.hpp>
#include <fmt/format.h>
#include <Pool/ThreadPool.hpp>
#include <Scheduler/Scheduler.hpp>

int main()
{
    ::xrn::scheduler::Scheduler s{ 2 };
    s.start();
    return 0;
}
