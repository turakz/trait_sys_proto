#ifndef _FRACTALS_PRINTER_TEST_DATA_STRUCTS_H
#define _FRACTALS_PRINTER_TEST_DATA_STRUCTS_H
// Standard
// test fixture has to implement types in terms of C aliases
// -> c++ implementation will still dispatch accordingly
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>
//bool (*field_callback)(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field);

//bool (*decode)(pb_istream_t *stream, const pb_field_t *field, void **arg);

//bool (*encode)(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);

//bool (*decode)(pb_istream_t *stream, pb_extension_t *extension,
//               uint32_t tag, pb_wire_type_t wire_type);

// example production struct
struct Message {
  void* Context;
  uint32_t Id;
  union {
    int32_t I32;
    uint64_t U64;
  } Payload;
};

typedef struct NamedTypedefStruct {
  int x;
  float y;
} NamedTypedefStruct_t;

struct NamedStruct {
  char x;
  unsigned char y;
};

typedef struct {
  double x;
  const char* y;
} UnnamedTypdefStruct_t;

// test data special type definitions
//using TestDataUnsupported_t = class TestDataUnsupported {};

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
  //TestDataUnsupported_t unsupported_v;

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

  bool bool_true_v;
  char char_v;
  char char_null_v;
  const char*    const_char_v;

  wchar_t        wchar_v;
  wchar_t        wchar_null_v;

  int32_t*       ptr_v;
  void*          void_ptr_v;

  int            c_array_v[5]{42, -42, 42, -42, 42};
  char           c_char_array_v[5]{'a', 'b', 'c', 'd', '3'};

  bool (*func_ptr)(int, int, int);

  enum TestDataEnum enum_v;

  TestDataUnion_t union_v;
  TestDataUnnamedUnion_t unnamed_union_v;
  // struct dependency
  //TestDataDependency_t struct_dep_v;
} TestData_t;
#endif
