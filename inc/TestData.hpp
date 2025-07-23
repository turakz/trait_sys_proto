#ifndef _TEST_DATA_HPP
#define _TEST_DATA_HPP
#include <cstdint>

#include "TestDataDependency.hpp"

// test data special type definitions
using TestDataUnsupported_t = class TestDataUnsupported {};

typedef enum TestDataEnum {
  TestDataEnum_X,
  TestDataEnum_Y
} TestDataEnum_t;

typedef union TestDataUnion {
  int x;
  int y;
} TestDataUnion_t;

typedef union {
  int x;
  int y;
} TestDataUnnamedUnion_t;

// test data definition
typedef struct TestData {
  TestDataUnsupported_t unsupported_v;

  int8_t   int8_t_v;
  uint8_t  uint8_t_v;
  int16_t  int16_t_v;
  uint16_t uint16_t_v;
  int32_t  int32_t_v;
  uint32_t uint32_t_v;
  int64_t  int64_t_v;
  uint64_t uint64_t_v;

  long               long_v;
  unsigned long      ulong_v;
  long long          longlong_v;
  unsigned long long ulonglong_v;

  char char_v;
  char char_null_v;
  bool bool_true_v;

  const char*    const_char_v;
  int32_t*       ptr_v;
  int32_t*       nullptr_v;
  void*          void_ptr_v;
  std::nullptr_t nullptr_t_v;
  int            c_array_v[5]{42, -42, 42, -42, 42};
  char           c_char_array_v[5]{'a', 'b', 'c', 'd', '3'};
  // enum type
  TestDataEnum enum_v;
  // union type
  TestDataUnion_t union_v;

  bool (*func_ptr)(int, int, int);

  // struct dependency
  TestDataDependency_t struct_dep_v;
} TestData_t;

typedef struct {
  TestData_t unnamed_v_data;
} TestDataUnnamed_t;
#endif
