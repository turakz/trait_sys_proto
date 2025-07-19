#ifndef _DATA_PRINTER_HPP
#define _DATA_PRINTER_HPP

#include <iostream>

// printer module
#include "Printer.hpp"
// test struct dependency printer module
#include "TestDataDependencyPrinter.hpp"
// test struct
#include "TestData.hpp"

// inject custom struct type and tag at compile-time
namespace fractals {
namespace traits {
namespace detail {
// struct TestData_tag {};
// template<>
// struct classify<TestData> {
//   using type = TestData_tag;
// };
struct TestData_tag {};
template <>
struct classify<TestData_t> {
  using type = TestData_tag;
};
struct TestDataUnnamed_t_tag {};
template <>
struct classify<TestDataUnnamed_t> {
  using type = TestDataUnnamed_t_tag;
};
};  // namespace detail
};  // namespace traits
};  // namespace fractals

namespace printer {
inline std::ostream& print(std::ostream& os, const TestData& object, fractals::traits::detail::TestData_tag)
{
  os << "tagged dispatch for struct type TestData\n";

  // integral output
  printer::print(os, object.int8_t_v, fractals::traits::classify_t<decltype(object.int8_t_v)>{}) << "\n";
  printer::print(os, object.uint8_t_v, fractals::traits::classify_t<decltype(object.uint8_t_v)>{}) << "\n";

  printer::print(os, object.int16_t_v, fractals::traits::classify_t<decltype(object.int16_t_v)>{}) << "\n";
  printer::print(os, object.uint16_t_v, fractals::traits::classify_t<decltype(object.uint16_t_v)>{}) << "\n";

  printer::print(os, object.int32_t_v, fractals::traits::classify_t<decltype(object.int32_t_v)>{}) << "\n";
  printer::print(os, object.uint32_t_v, fractals::traits::classify_t<decltype(object.uint32_t_v)>{}) << "\n";

  printer::print(os, object.int64_t_v, fractals::traits::classify_t<decltype(object.int64_t_v)>{}) << "\n";
  printer::print(os, object.uint64_t_v, fractals::traits::classify_t<decltype(object.uint64_t_v)>{}) << "\n";

  printer::print(os, object.long_v, fractals::traits::classify_t<decltype(object.long_v)>{}) << "\n";
  printer::print(os, object.ulong_v, fractals::traits::classify_t<decltype(object.ulong_v)>{}) << "\n";

  printer::print(os, object.longlong_v, fractals::traits::classify_t<decltype(object.longlong_v)>{}) << "\n";
  printer::print(os, object.ulonglong_v, fractals::traits::classify_t<decltype(object.ulonglong_v)>{}) << "\n";

  // char output
  printer::print(os, object.char_v, fractals::traits::classify_t<decltype(object.char_v)>{}) << "\n";
  printer::print(os, object.char_null_v, fractals::traits::classify_t<decltype(object.char_null_v)>{}) << "\n";

  // bool output
  printer::print(os, object.bool_true_v, fractals::traits::classify_t<decltype(object.bool_true_v)>{}) << "\n";

  // ptr output
  printer::print(os, object.const_char_v, fractals::traits::classify_t<decltype(object.const_char_v)>{}) << "\n";
  printer::print(os, object.ptr_v, fractals::traits::classify_t<decltype(object.ptr_v)>{}) << "\n";
  printer::print(os, object.nullptr_v, fractals::traits::classify_t<decltype(object.nullptr_v)>{}) << "\n";
  printer::print(os, object.nullptr_t_v, fractals::traits::classify_t<decltype(object.nullptr_t_v)>{}) << "\n";
  printer::print(os, nullptr, fractals::traits::classify_t<decltype(nullptr)>{}) << "\n";
  printer::print(os, object.void_ptr_v, fractals::traits::classify_t<decltype(object.void_ptr_v)>{}) << "\n";

  // c-array output
  printer::print(os, object.c_array_v, fractals::traits::classify_t<decltype(object.c_array_v)>{}) << "\n";
  printer::print(os, object.c_char_array_v, fractals::traits::classify_t<decltype(object.c_char_array_v)>{}) << "\n";
  // enum output
  printer::print(os, object.enum_v, fractals::traits::classify_t<decltype(object.enum_v)>{}) << "\n";
  // union output
  printer::print(os, object.union_v, fractals::traits::classify_t<decltype(object.union_v)>{}) << "\n";
  // struct dependency output
  printer::print(os, object.struct_dep_v, fractals::traits::classify_t<decltype(object.struct_dep_v)>{}) << std::endl;

  return os;
}
};  // namespace printer
inline std::ostream& operator<<(std::ostream& os, const TestData& object)
{
  os << "operator << entry point for struct type TestData\n";
  // TODO(fractals): trait system needs to be able to handle const qualifiers
  printer::print(os, object.union_v, fractals::traits::classify_t<decltype(object.union_v)>{}) << std::endl;
  // and references etc
  return printer::print(os, object, fractals::traits::classify_t<std::decay_t<decltype(object)>>{});
}

namespace printer {
inline std::ostream& print(std::ostream& os, const TestDataUnnamed_t& object,
                           fractals::traits::detail::TestDataUnnamed_t_tag)
{
  os << "tagged dispatch for struct type TestDataUnnamed_t\n";

  // dump the struct member
  printer::print(os, object.unnamed_v_data, fractals::traits::classify_t<decltype(object.unnamed_v_data)>{})
      << std::endl;

  return os;
}
};  // namespace printer
inline std::ostream& operator<<(std::ostream& os, const TestDataUnnamed_t& object)
{
  os << "operator << entry point for struct type TestData\n";
  // TODO(fractals): trait system needs to be able to handle const qualifiers
  // and references etc
  return printer::print(os, object, fractals::traits::classify_t<std::decay_t<decltype(object)>>{});
}
#endif
