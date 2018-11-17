// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++14
// expected-diagnostics

static_assert(__has_extension(trivially_relocatable), "");

template<bool B> constexpr bool ValueOf = B;

struct [[clang::trivially_relocatable(true)]] A1 {};
struct [[clang::trivially_relocatable(false)]] A2 {};
struct [[clang::trivially_relocatable(true)]] A3 { ~A3(); };
struct [[clang::trivially_relocatable(false)]] A4 { ~A4(); };

static_assert(__is_trivially_relocatable(A1), "");
static_assert(!__is_trivially_relocatable(A2), "");
static_assert(__is_trivially_relocatable(A3), "");
static_assert(!__is_trivially_relocatable(A4), "");

struct [[clang::trivially_relocatable(ValueOf<true>)]] B1 {};
struct [[clang::trivially_relocatable(ValueOf<false>)]] B2 {};
struct [[clang::trivially_relocatable(ValueOf<true>)]] B3 { ~B3(); };
struct [[clang::trivially_relocatable(ValueOf<false>)]] B4 { ~B4(); };

static_assert(__is_trivially_relocatable(B1), "");
static_assert(!__is_trivially_relocatable(B2), "");
static_assert(__is_trivially_relocatable(B3), "");
static_assert(!__is_trivially_relocatable(B4), "");

template<bool B> struct [[clang::trivially_relocatable(ValueOf<B>)]] C1 {};
template<bool B> struct [[clang::trivially_relocatable(ValueOf<B>)]] C2 { ~C2(); };
static_assert(__is_trivially_relocatable(C1<true>), "");
static_assert(__is_trivially_relocatable(C2<true>), "");
static_assert(!__is_trivially_relocatable(C1<false>), "");
static_assert(!__is_trivially_relocatable(C2<false>), "");

template<class T> struct [[clang::trivially_relocatable(sizeof(T)==1)]] C3 {};
// expected-error@-1{{invalid application of 'sizeof' to an incomplete type 'void'}}
static_assert(__is_trivially_relocatable(C3<char>), "");
static_assert(__is_trivially_relocatable(C3<void>), "");
// expected-note@-1{{in instantiation of template class 'C3<void>' requested here}}
