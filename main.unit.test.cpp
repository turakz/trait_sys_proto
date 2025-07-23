#include <gtest/gtest.h>

#include <iostream>

#include "Printer.hpp"
#include "TestData.hpp"
#include "TestDataDependency.hpp"
#include "TestDataPrinter.hpp"

class TestDataFixture : public ::testing::Test {
 protected:
  TestData           data{};
  TestDataDependency dependencyData{};
  TestDataUnnamed_t  unnamedData{};
  void               SetUp() override
  {
    // numeric
    data.int8_t_v            = INT8_MIN;
    dependencyData.int8_t_v  = INT8_MIN;
    data.uint8_t_v           = INT8_MAX;
    dependencyData.uint8_t_v = INT8_MAX;

    data.int16_t_v            = INT16_MIN;
    dependencyData.int16_t_v  = INT16_MIN;
    data.uint16_t_v           = INT16_MAX;
    dependencyData.uint16_t_v = INT16_MAX;

    data.int32_t_v            = INT32_MIN;
    dependencyData.int32_t_v  = INT32_MIN;
    data.uint32_t_v           = INT32_MAX;
    dependencyData.uint32_t_v = INT32_MAX;

    data.int64_t_v            = INT64_MIN;
    dependencyData.int64_t_v  = INT64_MIN;
    data.uint64_t_v           = INT64_MAX;
    dependencyData.uint64_t_v = INT64_MAX;

    data.long_v            = INT64_MIN;
    dependencyData.long_v  = INT64_MIN;
    data.ulong_v           = INT64_MAX;
    dependencyData.ulong_v = INT64_MAX;

    data.longlong_v            = INT64_MIN;
    dependencyData.longlong_v  = INT64_MIN;
    data.ulonglong_v           = INT64_MAX;
    dependencyData.ulonglong_v = INT64_MAX;

    // special cases
    data.const_char_v =
        "]{}@!#$6^*)%*&__+_--42forty$@#@#4two!!@#%..';::'''"
        ""
        ";;'lf\0";
    dependencyData.const_char_v =
        "]{}@!#$6^*)%*&__+_--42forty$@#@#4two!!@#%..';::'''"
        ""
        ";;'lf\0";
    data.char_v                = 'x';
    dependencyData.char_v      = 'x';
    data.char_null_v           = '\0';
    dependencyData.char_null_v = '\0';

    data.bool_true_v           = true;
    dependencyData.bool_true_v = true;

    // ptrs handled in their unit tests

    // data.c_array_v gets initialized at struct definition
    // data.c_char_array_v gets initialized at struct definition

    data.enum_v           = TestDataEnum::TestDataEnum_X;
    dependencyData.enum_v = TestDataDependencyEnum::TestDataDependency_X;

    data.union_v.x           = 42;
    dependencyData.union_v.x = 42;

    // save struct dependency for last so that its values get assigned to for unit testing
    data.struct_dep_v = dependencyData;
  };
  void TearDown() override{};
};

TEST_F(TestDataFixture, TestOutputOperatorsCompileAndBuild)
{
  // printer entry point
  std::cout << "---- TestData struct print start ----\n";
  std::cout << data;
  std::cout << "---- TestData struct print end   ----" << std::endl;

  std::cout << "---- TestData dep struct print start ----\n";
  std::cout << data.struct_dep_v;
  std::cout << "---- TestData dep struct print end   ----" << std::endl;

  std::cout << "---- TestDataDependency struct print start ----\n";
  std::cout << dependencyData;
  std::cout << "---- TestDataDependency struct print end   ----" << std::endl;

  std::cout << "---- TestDataUnnamed_t struct print start ----\n";
  std::cout << unnamedData;
  std::cout << "---- TestDataUnnamed_t struct print end   ----" << std::endl;
}

TEST_F(TestDataFixture, TestUnsupportedTag)
{
  std::ostringstream oss;
  printer::print(oss, data.unsupported_v, fractals::traits::classify_t<decltype(data.unsupported_v)>{});
  std::ostringstream expected;
  expected << "unsupported dispatch: [unsupported type]";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt8Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.int8_t_v, fractals::traits::classify_t<decltype(data.int8_t_v)>{});
  std::ostringstream expected;
  expected << "int8_t dispatch: " << INT8_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUInt8Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.uint8_t_v, fractals::traits::classify_t<decltype(data.uint8_t_v)>{});
  std::ostringstream expected;
  expected << "uint8_t dispatch: " << INT8_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt16Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.int16_t_v, fractals::traits::classify_t<decltype(data.int16_t_v)>{});
  std::ostringstream expected;
  expected << "int16_t dispatch: " << INT16_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint16Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.uint16_t_v, fractals::traits::classify_t<decltype(data.uint16_t_v)>{});
  std::ostringstream expected;
  expected << "uint16_t dispatch: " << INT16_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt32Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.int32_t_v, fractals::traits::classify_t<decltype(data.int32_t_v)>{});
  std::ostringstream expected;
  expected << "int32_t dispatch: " << INT32_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint32Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.uint32_t_v, fractals::traits::classify_t<decltype(data.uint32_t_v)>{});
  std::ostringstream expected;
  expected << "uint32_t dispatch: " << INT32_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestInt64Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.int64_t_v, fractals::traits::classify_t<decltype(data.int64_t_v)>{});
  std::ostringstream expected;
  expected << "int64_t dispatch: " << INT64_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUint64Tag)
{
  std::ostringstream oss;
  printer::print(oss, data.uint64_t_v, fractals::traits::classify_t<decltype(data.uint64_t_v)>{});
  std::ostringstream expected;
  expected << "uint64_t dispatch: " << INT64_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestLongTag)
{
  std::ostringstream oss;
  printer::print(oss, data.long_v, fractals::traits::classify_t<decltype(data.long_v)>{});
  std::ostringstream expected;
  expected << "int64_t dispatch: " << INT64_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUlongTag)
{
  std::ostringstream oss;
  printer::print(oss, data.ulong_v, fractals::traits::classify_t<decltype(data.ulong_v)>{});
  std::ostringstream expected;
  expected << "uint64_t dispatch: " << INT64_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestLonglongTag)
{
  std::ostringstream oss;
  printer::print(oss, data.longlong_v, fractals::traits::classify_t<decltype(data.longlong_v)>{});
  std::ostringstream expected;
  expected << "long long dispatch: " << INT64_MIN;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUlonglongTag)
{
  std::ostringstream oss;
  printer::print(oss, data.ulonglong_v, fractals::traits::classify_t<decltype(data.ulonglong_v)>{});
  std::ostringstream expected;
  expected << "unsigned long long dispatch: " << INT64_MAX;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCharTag)
{
  std::ostringstream oss;
  printer::print(oss, data.char_v, fractals::traits::classify_t<decltype(data.char_v)>{});
  std::ostringstream expected;
  expected << "char dispatch: \'" << data.char_v << "\'";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCharTagNull)
{
  std::ostringstream oss;
  printer::print(oss, data.char_null_v, fractals::traits::classify_t<decltype(data.char_null_v)>{});
  std::ostringstream expected;
  expected << "char dispatch: \'" << data.char_null_v << "\'";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestBoolTag)
{
  std::ostringstream oss;
  printer::print(oss, data.bool_true_v, fractals::traits::classify_t<decltype(data.bool_true_v)>{});
  std::ostringstream expected;
  expected << "bool dispatch: true";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestConstCharTag)
{
  std::ostringstream oss;
  printer::print(oss, data.const_char_v, fractals::traits::classify_t<decltype(data.const_char_v)>{});
  std::ostringstream expected;
  expected << "const char* dispatch: \"" << data.const_char_v << "\"";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestPtrTag)
{
  int32_t expected_v = 42;
  data.ptr_v         = &expected_v;
  std::ostringstream oss;
  printer::print(oss, data.ptr_v, fractals::traits::classify_t<decltype(data.ptr_v)>{});
  std::ostringstream expected;
  ASSERT_NE(data.ptr_v, nullptr);
  expected << "ptr dispatch: " << data.ptr_v << " -> " << (*data.ptr_v);
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestPtrTagNullptr)
{
  data.nullptr_v = nullptr;
  std::ostringstream oss;
  printer::print(oss, data.nullptr_v, fractals::traits::classify_t<decltype(data.nullptr_v)>{});
  std::ostringstream expected;
  ASSERT_EQ(data.nullptr_v, nullptr);
  expected << "ptr dispatch: " << data.nullptr_v << " -> nullptr";
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestPtrTagNullPtrT)
{
  data.nullptr_t_v = nullptr;
  std::ostringstream oss;
  printer::print(oss, nullptr, fractals::traits::classify_t<decltype(nullptr)>{});
  std::ostringstream expected;
  ASSERT_EQ(data.nullptr_v, nullptr);
  expected << "nullptr_t dispatch: " << nullptr;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestFuncPtrTag)
{
  std::ostringstream oss;
  printer::print(oss, data.func_ptr, fractals::traits::classify_t<decltype(data.func_ptr)>{});
}

TEST_F(TestDataFixture, TestVoidPtrTag)
{
  // TODO(fractals): how to test void ptr?
  int32_t expected_v = 42;
  data.void_ptr_v    = &expected_v;
  std::ostringstream oss;
  printer::print(oss, data.void_ptr_v, fractals::traits::classify_t<decltype(data.void_ptr_v)>{});
  std::ostringstream expected;
  expected << "void ptr dispatch: " << data.void_ptr_v;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestCarrayTag)
{
  std::ostringstream oss;
  printer::print(oss, data.c_array_v, fractals::traits::classify_t<decltype(data.c_array_v)>{});
  std::string output = oss.str();
  ASSERT_NE(output.find("c_array dispatch:"), std::string::npos);
  ASSERT_NE(output.find(" -> {42, -42, 42, -42, 42}"), std::string::npos);
}

TEST_F(TestDataFixture, TestCharCarrayTag)
{
  std::ostringstream oss;
  printer::print(oss, data.c_char_array_v, fractals::traits::classify_t<decltype(data.c_char_array_v)>{});
  std::string output = oss.str();
  ASSERT_NE(output.find("c_array dispatch:"), std::string::npos);
  ASSERT_NE(output.find(" -> {a, b, c, d, 3}"), std::string::npos);
}

TEST_F(TestDataFixture, TestEnumTag)
{
  std::ostringstream oss;
  printer::print<decltype(data.enum_v)>(oss, data.enum_v, fractals::traits::classify_t<decltype(data.enum_v)>{});
  std::ostringstream expected;
  expected << "enum dispatch: " << data.enum_v;
  ASSERT_EQ(oss.str(), expected.str());
}

TEST_F(TestDataFixture, TestUnionTag)
{
  std::ostringstream oss;
  printer::print<decltype(data.union_v)>(oss, data.union_v, fractals::traits::classify_t<decltype(data.union_v)>{});
  std::ostringstream expected;
  expected << "union dispatch: [union]";
  ASSERT_EQ(oss.str(), expected.str());
}
