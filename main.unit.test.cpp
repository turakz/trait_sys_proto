#include <gtest/gtest.h>

#include <iostream>

#include "Printer.hpp"
#include "TestData.hpp"
#include "TestDataDependency.hpp"
#include "TestDataPrinter.hpp"

class TestDataFixture : public ::testing::Test {
protected:
  NamedTypedefStruct_t namedStructTypedefData{.x = 42, .y = 42.24};
  NamedTypedefStruct_t namedStructTypedefData_NE{.x = 24, .y = 24.42};

  NamedStruct namedStructData{.x = 'x', .y = 'y'};
  NamedStruct namedStructData_NE{.x = 'y', .y = 'x'};

  UnnamedTypdefStruct_t unnamedTypedefStructData{
      .x = 42.24,
      .y = "42",
  };
  UnnamedTypdefStruct_t unnamedTypedefStructData_NE{
      .x = 24.24,
      .y = "24",
  };

  TestData data{};

  void SetUp() override
  {
    // numeric
    data.int8_t_v   = INT8_MIN;
    data.uint8_t_v  = UINT8_MAX;
    data.int16_t_v  = INT16_MIN;
    data.uint16_t_v = UINT16_MAX;
    data.int32_t_v  = INT32_MIN;
    data.uint32_t_v = UINT32_MAX;
    data.int64_t_v  = INT64_MIN;
    data.uint64_t_v = UINT64_MAX;

    // use std::numeric_limits for long/ulong to ensure platform-specific min/max
    data.long_v  = std::numeric_limits<long>::min();
    data.ulong_v = std::numeric_limits<unsigned long>::max();

    data.longlong_v  = LLONG_MIN;
    data.ulonglong_v = ULLONG_MAX;

    data.bool_true_v = true;

    data.char_v       = 'x';
    data.char_null_v  = '\0';
    data.const_char_v = "]{}@!#$6^*)%*&__+_--42forty$@#@#4two!!@#%..';::'''"
                        ""
                        ";;'lf\0";

    data.wchar_v      = L'Ω';
    data.wchar_null_v = L'\0';

    // special cases
    // ptrs handled in unit tests
    // func ptr defined in struct definition
    // c_array initialized in struct definition
    data.enum_v            = TestDataEnum::TestDataEnum_X;
    data.union_v.x         = 42;
    data.unnamed_union_v.x = 42;

    // save struct dependency for last so that its values get assigned to for unit testing
    // data.struct_dep_v = dependencyData;
  };
  void TearDown() override {};
};

/* Test Definitions
***********************************/
TEST_F(TestDataFixture, TestUnsupportedTag)
{
  class unsupported_t {};
  unsupported_t unsupported_v{};

  std::ostringstream oss;
  fractals::printer::print(oss, unsupported_v, "unsupported_t unsupported_v", 0,
                              fractals::traits::classify_t<unsupported_t>{});
  std::ostringstream expected;

  expected << "unsupported_t unsupported_v: [unsupported type]";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt8Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.int8_t_v, "int8_t int8_t_v", 0,
                              fractals::traits::classify_t<decltype(data.int8_t_v)>{});

  std::ostringstream expected;
  expected << "int8_t int8_t_v: " << static_cast<int>(INT8_MIN); // Cast to int for printing
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUInt8Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.uint8_t_v, "uint8_t uint8_t_v", 0,
                              fractals::traits::classify_t<decltype(data.uint8_t_v)>{});

  std::ostringstream expected;
  expected << "uint8_t uint8_t_v: " << static_cast<unsigned int>(UINT8_MAX); // Cast to unsigned int for printing
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt16Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.int16_t_v, "int16_t int16_t_v", 0,
                              fractals::traits::classify_t<decltype(data.int16_t_v)>{});

  std::ostringstream expected;
  expected << "int16_t int16_t_v: " << INT16_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint16Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.uint16_t_v, "uint16_t uint16_t_v", 0,
                              fractals::traits::classify_t<decltype(data.uint16_t_v)>{});

  std::ostringstream expected;
  expected << "uint16_t uint16_t_v: " << UINT16_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt32Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.int32_t_v, "int32_t int32_t_v", 0,
                              fractals::traits::classify_t<decltype(data.int32_t_v)>{});

  std::ostringstream expected;
  expected << "int32_t int32_t_v: " << INT32_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint32Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.uint32_t_v, "uint32_t uint32_t_v", 0,
                              fractals::traits::classify_t<decltype(data.uint32_t_v)>{});

  std::ostringstream expected;
  expected << "uint32_t uint32_t_v: " << UINT32_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt64Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.int64_t_v, "int64_t int64_t_v", 0,
                              fractals::traits::classify_t<decltype(data.int64_t_v)>{});

  std::ostringstream expected;
  expected << "int64_t int64_t_v: " << INT64_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint64Tag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.uint64_t_v, "uint64_t uint64_t_v", 0,
                              fractals::traits::classify_t<decltype(data.uint64_t_v)>{});

  std::ostringstream expected;
  expected << "uint64_t uint64_t_v: " << UINT64_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestLongTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.long_v, "long long_v", 0,
                              fractals::traits::classify_t<decltype(data.long_v)>{});

  std::ostringstream expected;
  expected << "long long_v: " << std::numeric_limits<long>::min();
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUlongTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.ulong_v, "unsigned long ulong_v", 0,
                              fractals::traits::classify_t<decltype(data.ulong_v)>{});

  std::ostringstream expected;
  expected << "unsigned long ulong_v: " << std::numeric_limits<unsigned long>::max();
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestLonglongTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.longlong_v, "long long long_v", 0,
                              fractals::traits::classify_t<decltype(data.longlong_v)>{});

  std::ostringstream expected;
  expected << "long long long_v: " << LLONG_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUlonglongTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.ulonglong_v, "unsigned long long ulonglong_v", 0,
                              fractals::traits::classify_t<decltype(data.ulonglong_v)>{});

  std::ostringstream expected;
  expected << "unsigned long long ulonglong_v: " << ULLONG_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestBoolTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.bool_true_v, "_Bool bool_true_v", 0,
                              fractals::traits::classify_t<decltype(data.bool_true_v)>{});

  std::ostringstream expected;
  expected << "_Bool bool_true_v: true";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCharTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.char_v, "char char_v", 0,
                              fractals::traits::classify_t<decltype(data.char_v)>{});

  std::ostringstream expected;
  expected << "char char_v: \'" << data.char_v << "\'";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCharTagNull)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.char_null_v, "char char_null_v", 0,
                              fractals::traits::classify_t<decltype(data.char_null_v)>{});

  std::ostringstream expected;
  expected << "char char_null_v: \'" << '\0' << "\'";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestConstCharTag)
{
  const char*        expected_const_char_v = "]{}@!#$6^*)%*&__+_--42forty$@#@#4two!!@#%..';::'''"
                                             ""
                                             ";;'lf\0";
  std::ostringstream oss;
  fractals::printer::print(oss, data.const_char_v, "const char* const_char_v", 0,
                              fractals::traits::classify_t<decltype(data.const_char_v)>{});

  std::ostringstream expected;
  expected << "const char* const_char_v: \"" << expected_const_char_v << "\"";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestWcharTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.wchar_v, "wchar_t wchar_v", 0,
                              fractals::traits::classify_t<decltype(data.wchar_v)>{});

  std::ostringstream expected;
  // wchar_t prints its numeric value by default to std::ostream
  expected << "wchar_t wchar_v: "
           << static_cast<long>(data.wchar_v); // Cast to long to ensure it's treated as an integer
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestWcharTagNull)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.wchar_null_v, "wchar_t wchar_null_v", 0,
                              fractals::traits::classify_t<decltype(data.wchar_null_v)>{});

  std::ostringstream expected;
  expected << "wchar_t wchar_null_v: " << static_cast<long>(data.wchar_null_v);
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestVoidPtrTag)
{
  int32_t expected_v = 42;
  data.void_ptr_v    = &expected_v;
  std::ostringstream oss;
  fractals::printer::print(oss, data.void_ptr_v, "void* ptr_v", 0,
                              fractals::traits::classify_t<decltype(data.void_ptr_v)>{});

  std::ostringstream expected;
  expected << "void* ptr_v: " << data.void_ptr_v << " -> void";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestPtrTag)
{
  int32_t expected_v = 42;
  data.ptr_v         = &expected_v;
  std::ostringstream oss;
  fractals::printer::print(oss, data.ptr_v, "ptr ptr_v", 0, fractals::traits::classify_t<decltype(data.ptr_v)>{});

  std::ostringstream expected;
  expected << "ptr ptr_v: " << data.ptr_v << " -> " << (*data.ptr_v);
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestFuncPtrTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.func_ptr, "ptr func_ptr", 0,
                              fractals::traits::classify_t<decltype(data.func_ptr)>{});

  std::ostringstream expected;
  // The printer uses reinterpret_cast<const void*>(value)
  expected << "ptr func_ptr: " << reinterpret_cast<const void*>(data.func_ptr) << " -> [func_ptr]";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestPtrTagNull)
{
  data.ptr_v = nullptr; // Use nullptr for C++11+
  std::ostringstream oss;
  fractals::printer::print(oss, data.ptr_v, "ptr ptr_v", 0, fractals::traits::classify_t<decltype(data.ptr_v)>{});

  std::ostringstream expected;
  // The printer explicitly outputs "NULL" for null pointers.
  // The address of nullptr is typically 0x0 or 0.
  expected << "ptr ptr_v: " << static_cast<void*>(nullptr) << " -> NULL";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCarrayTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.c_array_v, "int[5] c_array_v", 0,
                              fractals::traits::classify_t<decltype(data.c_array_v)>{});

  std::ostringstream expected;
  // Construct the exact expected string based on your printer's output format
  // Assuming printer outputs: "label: address -> {element1, element2, ...}"
  expected << "int[5] c_array_v: " << static_cast<const void*>(data.c_array_v) << " -> {42, -42, 42, -42, 42}";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCharCarrayTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.c_char_array_v, "char[5] c_char_array_v", 0,
                              fractals::traits::classify_t<decltype(data.c_char_array_v)>{});

  std::ostringstream expected;
  // Corrected: The last element is the integer 3, not a null character.
  // The char_tag printer will output '3' for the char value 3.
  expected << "char[5] c_char_array_v: " << static_cast<const void*>(data.c_char_array_v) << " -> {a, b, c, d, 3}";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestEnumTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.enum_v, "enum enum_v", 0,
                              fractals::traits::classify_t<decltype(data.enum_v)>{});

  std::ostringstream expected;
  // The printer outputs the underlying integer value of the enum
  expected << "enum enum_v: "
           << static_cast<typename std::underlying_type<TestDataEnum>::type>(TestDataEnum::TestDataEnum_X);
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUnionTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.union_v, "union union_v", 0,
                              fractals::traits::classify_t<decltype(data.union_v)>{});

  std::ostringstream expected;
  expected << "union union_v: [union]";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUnnamedUnionTag)
{
  std::ostringstream oss;
  fractals::printer::print(oss, data.unnamed_union_v, "union unnamed_union_v", 0,
                              fractals::traits::classify_t<decltype(data.unnamed_union_v)>{});

  std::ostringstream expected;
  expected << "union unnamed_union_v: [union]";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestStructEqualitySuccess)
{
  NamedTypedefStruct_t expected_NamedTypedefStruct_rhs{.x = 42, .y = 42.24};

  ASSERT_EQ(namedStructTypedefData, expected_NamedTypedefStruct_rhs);

  NamedStruct expected_NamedStruct_rhs{.x = 'x', .y = 'y'};

  ASSERT_EQ(namedStructData, expected_NamedStruct_rhs);

  UnnamedTypdefStruct_t expected_UnnamedTypedefStruct_rhs{.x = 42.24, .y = "42"};

  ASSERT_EQ(unnamedTypedefStructData, expected_UnnamedTypedefStruct_rhs);
}

TEST(TestData, TestStructMessage)
{
  uint32_t sender = 42;
  Message  sender_msg{.Context = &sender, .Id = sender};
  sender_msg.Payload.U64 = 64;

  uint32_t receiver = 42;
  Message  receiver_msg{
       .Context = &receiver,
       .Id      = receiver,
  };
  receiver_msg.Payload.I32 = 32;

  EXPECT_NE(sender_msg, receiver_msg);
}
