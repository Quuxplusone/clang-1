// RUN: %clang_cc1 -fsyntax-only -std=c++11 -verify %s

struct A;  // OK
struct A *pa;  // OK
extern struct A *epa;  // OK
template<struct A *> void ta1();  // OK
template<class = struct A> void ta2(); // OK

struct B {};  // OK
struct B *pb;  // OK

struct C *pc;  // expected-warning{{implicitly declared}}
struct C *pc2;  // OK

extern struct D pd;  // expected-warning{{implicitly declared}}
extern struct D pd2;  // OK

void foo(struct E *);  // expected-warning{{implicitly declared}}

struct F *pf();  // expected-warning{{implicitly declared}}

namespace N {
    struct A;  // OK, declares N::A
    struct B *pb();  // OK, refers to ::B
    template<struct C*> void ta1();  // OK, refers to ::C
    template<class = struct D> void ta2();  // OK, refers to ::D

    struct NG *png();  // expected-warning{{implicitly declared}}
    struct NG;  // OK
    struct NG {};  // OK
}

namespace N2 {
    struct N::A *pa();  // OK
}

template<struct H *> void th();  // expected-warning{{implicitly declared}}
template<struct H *> void th();  // OK

template<class T = struct I> void ti();  // expected-warning{{implicitly declared}}
struct I fi();  // OK

void *test1() {
    return (void *)(struct J *)0;  // expected-warning{{implicitly declared}}
}

void *test2() {
    return (void *)(struct J *)0;  // expected-warning{{implicitly declared}}
}
