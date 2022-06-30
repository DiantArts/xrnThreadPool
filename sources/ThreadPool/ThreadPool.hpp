#pragma once

#include <ThreadPool/Runner.hpp>

namespace xrn {

///////////////////////////////////////////////////////////////////////////
/// \brief Runs function in parallel
///
/// \include ThreadPool.hpp <ThreadPool.hpp>
///
///////////////////////////////////////////////////////////////////////////
class ThreadPool {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Configuration
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Configure a function call pattern
    ///
    /// latency: time between each calls in milliseconds
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Configuration {
        float latency;
    };

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit ThreadPool(
        ::std::uint8_t numberOfThread = 8
    )
        : m_runners{ numberOfThread }
    {}



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Rule of 5
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    ~ThreadPool() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    ThreadPool(
        const ThreadPool& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ThreadPool& other
    ) noexcept
        -> ThreadPool& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    ThreadPool(
        ThreadPool&& other
    ) noexcept = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ThreadPool&& other
    ) noexcept
        -> ThreadPool& = default;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Function managment
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplace a function in the pool
    ///
    /// The function will be executed with the configuration provided
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename LambdaType
    > void push(
        LambdaType&& lambda
    )
    {
        auto runnersSize{ m_runners.size() };
        auto lastSize{ m_runners[runnersSize - 1].size() };

        if (m_runners[0].size() == lastSize) {
            m_runners[0].push(::std::make_unique<::xrn::Job<LambdaType>>(::std::move(lambda)));
        } else if (m_runners[runnersSize / 2 - 1].size() == lastSize) {
            for (
                auto& runner :
                ::std::span{ m_runners.begin(), m_runners.end() - (runnersSize / 2) }
            ) {
                if (runner.size() == lastSize) {
                    runner.push(::std::make_unique<::xrn::Job<LambdaType>>(::std::move(lambda)));
                    break;
                }
            }
        } else {
            for (
                auto& runner :
                ::std::span{ m_runners.begin() + (runnersSize / 2), m_runners.end() }
            ) {
                if (runner.size() == lastSize) {
                    runner.push(::std::make_unique<::xrn::Job<LambdaType>>(::std::move(lambda)));
                    break;
                }
            }
        }
    }

    void join()
    {
        for (auto& runner : m_runners) {
            runner.exitWhenDone();
        }
        for (auto& runner : m_runners) {
            runner.join();
        }
    }



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ::std::vector<::xrn::Runner> m_runners;

};

} // namespace xrn
