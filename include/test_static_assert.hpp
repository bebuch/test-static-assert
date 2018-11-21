#ifndef _test_static_assert__test_static_assert__hpp_INCLUDED_
#define _test_static_assert__test_static_assert__hpp_INCLUDED_


namespace test_static_assert{


	/// \brief Helper to form void by a numeric template argument
	template < auto > using number2void = void;

	/// \brief By default types are not defined
	template < typename T, typename = void >
	constexpr auto is_defined = false;

	/// \brief If a type is defined this specialization is used
	template < typename T >
	constexpr auto is_defined< T, number2void< sizeof(T) > > = true;


	/// \brief By default this is not a unit test
	struct unit_test;


	/// \brief If this is not a unit test return the original condition
	template < bool condition, typename T, bool = is_defined< unit_test > >
	constexpr bool static_assert_map = condition;

	/// \brief If this is a unit test return always true
	template < bool condition, typename T >
	constexpr bool static_assert_map< condition, T, true >
		= []{
			static_assert(is_defined< T >,
				"You have to specialize T when unit_test is defined");
			return true;
		}();


}


#endif
