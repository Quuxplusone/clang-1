// RUN: %clang_cc1 -fsyntax-only -std=c++1z -Waggregate-ctors -fno-p1008 -verify %s

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
  struct X {
    X() = default;
    int x;
  };

  X x1;
  X x2{};
  X x3{0};
}

namespace DefaultCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X() = delete;
    int x;
  };

  X x2{};
  X x3{0};
}

namespace CopyCtorDeclaredDefault {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(const X&) = default;
    int x;
  };

  X x2{};
  X x3{0};
}

namespace CopyCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(const X&) = delete;
    int x;
  };

  X x2{};
  X x3{0};
}

namespace ConvertingCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X(int) = delete;
    int x;
  };

  X x{0};
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
  struct X {
    X() = default;
    int& x;
  };

  int val = 0;
  X x{val};
}

namespace ImplicitlyDeletedDefaultCtorDeclaredDelete {
  // expected-warning@+1 {{P1008 proposes that this aggregate type with user-declared constructor should become a non-aggregate in C++2a}}
  struct X {
    X() = delete;
    int& x;
  };

  int val = 0;
  X x{val};
}
