#ifndef WORK_HPP_
#define WORK_HPP_

// Exported includes.
#include <work/detail/IndexSequence.hpp>

// Standard includes.
#include <functional>
#include <memory>
#include <tuple>

namespace work
{
    /// Define a Priority type.
    using WorkPriority = uint32_t;

	/**
	 * @brief Class wrapping a callable type and a set of corresponding arguments.
	 * 
	 * @tparam I type representing the ID
	 * @tparam ...Ts variadic type representing the arguments 
	 */
    template <typename I, typename... Ts>
    class Work
    {
      public:

        /// Define an IDType.
        using IDType = I;

        /**
         * @brief Constructor
         *
         * @tparam F signature of the callable type.
         * @param priority the priority level of this Work.
         * @param func the functor to be run.
         * @param ...args the arguments to be passed to func.
         */
        template <typename F>
        Work(IDType id, WorkPriority&& priority, F&& func, Ts&&... args)
            : m_id(std::move(id)),
              m_p(std::move(priority)),
              m_f(std::forward<F>(func)),
              m_args(std::forward_as_tuple(std::forward<Ts>(args)...))
        { }

		/**
		 * Run the wrapped functor.
		 */
        void run()
        {
            func(m_args);
        }

		/**
		 * Return the assigned ID. 
		 */
        IDType getID() const
        {
            return m_id;
        }

		/**
		 * Return the assigned priority.
		 */
        WorkPriority getWorkPriority() const
        {
            return m_p;
        }

      private:

        template <typename... Args, std::size_t... Is>
        void func(std::tuple<Args...>& tup, detail::index_sequence<Is...>)
        {
            m_f(std::get<Is>(tup)...);
        }

        template <typename... Args>
        void func(std::tuple<Args...>& tup)
        {
            func(tup, detail::make_index_sequence<sizeof...(Args)> {});
        }

        IDType m_id;
        WorkPriority m_p;
        std::function<void(Ts...)> m_f;
        std::tuple<Ts...> m_args;
    };

    /// Work shared pointer alias.
    template<typename I, typename... Args >
    using WorkSPtr = std::shared_ptr<Work<I, Args...> >;

    /// Work unique pointer alias.
    template<typename I, typename... Args >
    using WorkUPtr = std::unique_ptr<Work<I, Args...> >;

    /// Factory function.
    template <typename I, typename F, typename... Args>
    Work<I, Args...> makeWork(I id, WorkPriority p, F&& f, Args&&... args)
    {
        return Work<I, Args...>(std::forward<I>(id),
                                std::move(p),
                                std::forward<F>(f),
                                std::forward<Args>(args)...);
    }

    /// Factory function.
    template <typename I, typename F, typename... Args>
    WorkUPtr<I, Args...> makeWorkUPtr(I id, WorkPriority p, F&& f, Args&&... args)
    {
        return std::make_unique<Work<I, Args...> >(std::forward<I>(id),
                                                   std::move(p),
                                                   std::forward<F>(f),
                                                   std::forward<Args>(args)...);
    }
}
#endif /* WORK_HPP_ */
