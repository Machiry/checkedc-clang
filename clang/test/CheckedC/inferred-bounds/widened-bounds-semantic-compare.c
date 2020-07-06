// Tests for bounds widening of _Nt_array_ptr's using function to semantically
// compare two expressions.
//
// RUN: %clang_cc1 -fdump-widened-bounds -verify -verify-ignore-unexpected=note -verify-ignore-unexpected=warning %s 2>&1 | FileCheck %s

// expected-no-diagnostics

void f1(int i) {
  _Nt_array_ptr<char> p : bounds(p, p + i) = "a";

  if (*(i + p)) {}

// CHECK: In function: f1
// CHECK:   2: *(i + p)
// CHECK: upper_bound(p) = 1
}

void f2(int i, int j) {
  _Nt_array_ptr<char> p : bounds(p, p + (i + j)) = "a";

  if (*(p + (j + i))) {}

// CHECK: In function: f2
// CHECK:   2: *(p + (j + i))
// CHECK: upper_bound(p) = 1
}

void f3(int i, int j) {
  _Nt_array_ptr<char> p : bounds(p, p + (i * j)) = "a";

  if (*(p + (j * i))) {}

// CHECK: In function: f3
// CHECK:   2: *(p + (j * i))
// CHECK: upper_bound(p) = 1
}

void f4(int i, int j, int m, int n) {
  _Nt_array_ptr<char> p : bounds (p, p + i + j + m + n) = "a";

  if (*(i + m + j + p + n)) {}

// CHECK: In function: f4
// CHECK:   2: *(i + m + j + p + n)
// CHECK: upper_bound(p) = 1
}

void f5(int i, int j, int m, int n) {
  _Nt_array_ptr<char> p : bounds (p, ((n * m) + (j * i)) + p) = "a";

  if (*(p + ((i * j) + (m * n)))) {}

// CHECK: In function: f5
// CHECK:   2: *(p + ((i * j) + (m * n)))
// CHECK: upper_bound(p) = 1
}
