// RUN: %clang_cc1 -verify -fopenmp -std=c++11 %s -Wuninitialized

// RUN: %clang_cc1 -verify -fopenmp-simd -std=c++11 %s -Wuninitialized

void xxx(int argc) {
  int x; // expected-note {{initialize the variable 'x' to silence this warning}}
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < 10; ++i)
    argc = x; // expected-warning {{variable 'x' is uninitialized when used here}}
}

void foo() {
}

static int pvt;
#pragma omp threadprivate(pvt)

#pragma omp teams distribute simd // expected-error {{unexpected OpenMP directive '#pragma omp teams distribute simd'}}

int main(int argc, char **argv) {
  #pragma omp target
  #pragma omp teams distribute simd
  f; // expected-error {{use of undeclared identifier 'f'}}
#pragma omp target
#pragma omp teams distribute simd { // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd ( // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd[ // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd] // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd) // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd } // expected-warning {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < argc; ++i)
    foo();
// expected-warning@+2 {{extra tokens at the end of '#pragma omp teams distribute simd' are ignored}}
#pragma omp target
#pragma omp teams distribute simd unknown()
  for (int i = 0; i < argc; ++i)
    foo();
L1:
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < argc; ++i)
    foo();
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < argc; ++i) {
    goto L1; // expected-error {{use of undeclared label 'L1'}}
    argc++;
  }

  for (int i = 0; i < 10; ++i) {
    switch (argc) {
    case (0):
#pragma omp target
#pragma omp teams distribute simd
      for (int i = 0; i < argc; ++i) {
        foo();
        break; // expected-error {{'break' statement cannot be used in OpenMP for loop}}
        continue;
      }
    default:
      break;
    }
  }
#pragma omp target
#pragma omp teams distribute simd default(none) // expected-note {{explicit data sharing attribute requested here}}
  for (int i = 0; i < 10; ++i)
    ++argc; // expected-error {{ariable 'argc' must have explicitly specified data sharing attributes}}

  goto L2; // expected-error {{use of undeclared label 'L2'}}
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < argc; ++i)
  L2:
  foo();
#pragma omp target
#pragma omp teams distribute simd
  for (int i = 0; i < argc; ++i) {
    return 1; // expected-error {{cannot return from OpenMP region}}
  }

  [[]] // expected-error {{an attribute list cannot appear here}}
#pragma omp target
#pragma omp teams distribute simd
      for (int n = 0; n < 100; ++n) {
  }

#pragma omp target
#pragma omp teams distribute simd copyin(pvt) // expected-error {{unexpected OpenMP clause 'copyin' in directive '#pragma omp teams distribute simd'}}
  for (int n = 0; n < 100; ++n) {}

  return 0;
}

void test_ordered() {
#pragma omp target
#pragma omp teams distribute simd ordered // expected-error {{unexpected OpenMP clause 'ordered' in directive '#pragma omp teams distribute simd'}}
  for (int i = 0; i < 16; ++i)
    ;
}

