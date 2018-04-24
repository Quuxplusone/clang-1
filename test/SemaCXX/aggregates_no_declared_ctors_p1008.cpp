// RUN: %clang_cc1 -std=c++1z -fp1008 -fsyntax-only -verify %s

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
  struct X { // expected-note 2 {{not viable}}
    X() = default; // expected-note {{not viable}}
    int x;
  };

  X x1;
  X x2{};
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace DefaultCtorDeclaredDelete {
  struct X { // expected-note 2 {{not viable}}
    X() = delete; // expected-note {{'X' has been explicitly marked deleted here}} expected-note {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{call to deleted constructor}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace CopyCtorDeclaredDefault {
  struct X {
    X(const X&) = default; // expected-note 1-2 {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{no matching constructor for initialization}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace CopyCtorDeclaredDelete {
  struct X {
    X(const X&) = delete; // expected-note 1-2 {{not viable}}
    int x;
  };

  X x2{};  // expected-error {{no matching constructor for initialization}}
  X x3{0};  // expected-error {{no matching constructor for initialization}}
}

namespace ConvertingCtorDeclaredDelete {
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
  struct X {  // expected-note 2 {{not viable}}
    X() = default; // expected-note {{not viable}}
    int& x;
  };

  int val = 0;
  X x{val}; // expected-error {{no matching constructor for initialization}}
}

namespace ImplicitlyDeletedDefaultCtorDeclaredDelete {
  struct X { // expected-note 2 {{not viable}}
    X() = delete; // expected-note {{not viable}}
    int& x;
  };

  int val = 0;
  X x{val}; // expected-error {{no matching constructor for initialization}}
}
