#include "foo.hpp"


int main(){
	static_assert(
		!test_static_assert::is_defined< test_static_assert::unit_test >);

	foo(4);
}
