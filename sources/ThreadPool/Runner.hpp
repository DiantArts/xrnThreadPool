#pragma once

#include <Job.hpp>

namespace xrn {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains a thread that can run things
///
/// \include Runner.hpp <Runner.hpp>
///
///////////////////////////////////////////////////////////////////////////
class Runner {

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
    explicit Runner()
        : m_runner{ &Runner::runner, this }
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
    ~Runner() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Runner(
        const Runner& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const Runner& other
    ) noexcept
        -> Runner& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Runner(
        Runner&& other
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        Runner&& other
    ) noexcept
        -> Runner&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Runner
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplace a function in the pool
    ///
    /// The function will be executed with the configuration provided
    ///
    ///////////////////////////////////////////////////////////////////////////
    void runner()
    {
        while (m_isRunning) {
            std::unique_lock lock{ m_mutex };
            if (m_pJobQueue.empty()) {
                if (m_exitWhenDone) {
                    break;
                }
                m_cv.wait(lock, [this]{ return !m_pJobQueue.empty() || !m_isRunning; });
            }

            if (m_isRunning) {
                do {
                    m_pJobQueue.front()->run();
                    m_pJobQueue.pop();
                } while (!m_pJobQueue.empty() && m_isRunning);
            }

            lock.unlock();
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds a function to the queue
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        ::std::unique_ptr<::xrn::IJob> job
    )
    {
        m_pJobQueue.push(::std::move(job));
        m_cv.notify_one();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks how many job there is to run
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto size()
        -> ::std::size_t
    {
        return m_pJobQueue.size();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Will exit when done with all jobs
    ///
    ///////////////////////////////////////////////////////////////////////////
    void exitWhenDone()
    {
        m_exitWhenDone = true;
        m_cv.notify_one();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief joins the thread
    ///
    ///////////////////////////////////////////////////////////////////////////
    void join()
    {
        m_runner.join();
    }



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    static inline ::std::atomic<::std::uint8_t> idGiver{ 0 };

    ::std::uint8_t m_id{ idGiver++ };
    ::std::atomic<bool> m_isRunning{ true };
    ::std::atomic<bool> m_exitWhenDone{ false };
    ::std::thread m_runner;
    ::std::mutex m_mutex;
    ::std::condition_variable m_cv;

    ::std::queue<::std::unique_ptr<::xrn::IJob>> m_pJobQueue;

};

} // namespace xrn
