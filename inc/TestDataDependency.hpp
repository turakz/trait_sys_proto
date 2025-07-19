#ifndef _TEST_DATA_DEPENDENCY_HPP
#define _TEST_DATA_DEPENDENCY_HPP
#include <cstdint>
using TestDataDependencyUnsupported_t = class TestDataDependencyUnsupported {};

typedef enum TestDataDependencyEnum {
  TestDataDependency_X,
  TestDataDependency_Y
} TestDataDependencyEnum_t;

typedef union TestDataDependencyUnion {
  int x;
  int y;
} TestDataDependencyUnion_t;

typedef struct TestDataDependency {
  TestDataDependencyUnsupported_t unsupported_v;

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
  TestDataDependencyEnum_t enum_v;
  // union type
  TestDataDependencyUnion_t union_v;
  // does not define a struct dep
} TestDataDependency_t;
#endif
