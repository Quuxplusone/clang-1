// RUN: %clang_cc1 -fsyntax-only -std=c++1z -Waggregate-ctors -fp1008 -verify %s

// Verify that a user-declared constructor (even if it's neither explicit
// nor user-provided, but declared as =delete or =default) makes a type
// non-aggregate. This is the change proposed by P1008

namespace NoDeclaredCtors {
  struct X {
    int x;
  };

  X x1;
  X x2{};
  X x3{0};
}

namespace DefaultCtorDeclaredDefault {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X { // expected-note 2 {{not viable}}
    X() = default; // expected-note {{not viable}}
    int x;
  };

  X x1;
  X x2{};
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace DefaultCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X { // expected-note 2 {{not viable}}
    X() = delete; // expected-note {{'X' has been explicitly marked deleted here}} expected-note {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{call to deleted constructor}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace CopyCtorDeclaredDefault {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(const X&) = default; // expected-note 1-2 {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{no matching constructor for initialization}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace CopyCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(const X&) = delete; // expected-note 1-2 {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{no matching constructor for initialization}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace ConvertingCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(int) = delete;  // expected-note {{'X' has been explicitly marked deleted here}}
    int x;
  };

  X x{0};  // expected-error {{call to deleted constructor}}
}

namespace ImplicitlyDeletedDefaultCtor {
  struct X {
    int& x;
  };

  int val = 0;
  X x{val};
}

namespace ImplicitlyDeletedDefaultCtorDeclaredDefault {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {  // expected-note 2 {{not viable}}
    X() = default; // expected-note {{not viable}}
    int& x;
  };

  int val = 0;
  X x{val}; // expected-error {{no matching constructor for initialization}}
}

namespace ImplicitlyDeletedDefaultCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X { // expected-note 2 {{not viable}}
    X() = delete; // expected-note {{not viable}}
    int& x;
  };

  int val = 0;
  X x{val}; // expected-error {{no matching constructor for initialization}}
}
