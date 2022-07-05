#pragma once

namespace xrn::pool {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains a function
///
/// \include IJob.hpp <IJob.hpp>
///
///////////////////////////////////////////////////////////////////////////
class IJob {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    IJob() = default;



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
    virtual ~IJob() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    IJob(
        const IJob& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const IJob& other
    ) noexcept
        -> IJob& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    IJob(
        IJob&& other
    ) noexcept = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        IJob&& other
    ) noexcept
        -> IJob& = default;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Runner
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the job
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void run() = 0;

};



///////////////////////////////////////////////////////////////////////////
/// \brief Contains a function
///
/// \include Job.hpp <Job.hpp>
///
///////////////////////////////////////////////////////////////////////////
template <
    typename JobType
> class Job
    : public ::xrn::pool::IJob
{

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
    explicit Job(
        JobType&& function
    )
        : m_function{ ::std::move(function) }
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
    ~Job() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Job(
        const Job& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const Job& other
    ) noexcept
        -> Job& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Job(
        Job&& other
    ) noexcept = default;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        Job&& other
    ) noexcept
        -> Job& = default;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Runner
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the job
    ///
    ///////////////////////////////////////////////////////////////////////////
    void run() override
    {
        m_function();
    }



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    JobType m_function;

};

} // namespace xrn::pool