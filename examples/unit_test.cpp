#include <enable_test_static_assert.hpp>

#include "foo.hpp"


template <>
struct T_must_be_int_identifier_type< true, int >{};

template <>
struct T_must_be_int_identifier_type< false, char const* >{};


int main(){
	static_assert(
		test_static_assert::is_defined< test_static_assert::unit_test >);

	foo(4);
	foo("4");
}
