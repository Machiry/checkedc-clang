// Tests to make sure _For_any specifier is parsed correctly.
//
// More specifically, we are testing for correctness of _For_any specifier.
// 1) _For_any specifier is correctly parsed along with new type polymorphism.
// 2) _For_any specifier correctly enters a new scope and function declaration
//    or definition is registered to a correct scope.
// For this test file, we expect that there are no errors.
//
// RUN: %clang_cc1 -fcheckedc-extension -S -emit-llvm -verify %s
// expected-no-diagnostics

// Testing for function declaration with statement body, without parameters.
_For_any(T) T TestDefinitionWithNoParameter() {
  T returnVal;
  return returnVal;
}

// Testing for function declaration with statement body, with parameters
_For_any(T, S) T TestDefinitionWithParameter(T at, T bt, S cs) {
  S newT = at;
  return newT;
}

// Testing for function declaration without statement body, without parameters.
_For_any(R) R TestDeclarationWithNoParameter();
// Testing for function declaration without statement body, with parameters
_For_any(Q) Q TestDeclarationWithParameter(Q aq, Q bq, Q cq);

int callPolymorphicTypes() {
  void *x, *y, *z;
  TestDefinitionWithNoParameter();
  TestDefinitionWithParameter(x, y, z);
  TestDeclarationWithNoParameter();
  TestDeclarationWithParameter(x, y, z);
  return 0;
}