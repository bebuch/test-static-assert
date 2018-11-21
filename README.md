# test-static-assert

C++17 library to test `static_assert`'s.

Unfortunately there is still no realy nice way to test `static_assert`'s. This library can only test a `static_assert` if it is implemented in a special way. This is based on an idea from Roland Bock presented on CppCon 2016 “How to test static_assert?”.

- https://youtu.be/wTmAJAk7WV4

## Dependencies

- none

## Tested compilers

- GCC 8
- clang 7

## Usage

This is a header-only library.

Assume you have a file `foo.hpp` with a function `foo()` that contains a `static_assert`:

```cpp
#ifndef _foo__hpp_INCLUDED_
#define _foo__hpp_INCLUDED_

#include <type_traits>

template < typename T >
int foo(T){
    static_assert(std::is_same_v< T, int >, "T must be int");
    return 5;
}


#endif

```

You have to rewrite it as follow to make the `static_assert` testable:


```cpp
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

```

Now you can it use as you ever did in your normal program. The `static_assert` will print its message as before the change:

```
#include "foo.hpp"

int main(){
    foo(4); // Okay
    foo("4"); // Error: T must be int
}
```

In the unit test file you have to include the `enable_test_static_assert.hpp` header as first header file!


```
// Important: This has to be the first include!
// Note: In your foo.hpp you included test_static_assert.hpp, here you include:
#include <enable_test_static_assert.hpp>

#include "foo.hpp"


// Now you have to specialize your identifier type for all foo-calls

// When calling it with int your expect to not trigger the static_assert:
template <>
struct T_must_be_int_identifier_type< true, int >{};

// When calling it with char const* your expect to trigger the static_assert
template <>
struct T_must_be_int_identifier_type< false, char const* >{};


int main(){
    // Call foo with the types for that you wan't to test the static_assert:
    foo(4);
    foo("4");
}

```

## License notice

This software was originally developed privately by Benjamin Buch. All changes are released under the Boost Software License - Version 1.0 and published on GitHub.

https://github.com/bebuch/test-static-assert
