#ifndef _foo__hpp_INCLUDED_
#define _foo__hpp_INCLUDED_

// include the test_static_assert header
#include "test_static_assert.hpp"

#include <type_traits>

// Define a templated type that is used to identify your static_assert.
//
// The type should contain all template arguments that are used in your
// static_assert condition
//
// It might be usefull to map also the condition result itself as Success:
template < bool Success, typename T >
struct T_must_be_int_identifier_type;

template < typename T >
// it might be useful to allow void as return type if your condition fails
auto foo(T){
	// out source your condition as variable
	constexpr bool condition = std::is_same_v< T, int >;

	// define the static_assert by map your condition to your identifier type
	static_assert(test_static_assert::static_assert_map< condition,
		T_must_be_int_identifier_type< condition, T > >,
		"T must be int");

	// ány static_assert must be followed by an constexpr-if with same condition
	if constexpr(condition){
		return 5;
	}
}


#endif
