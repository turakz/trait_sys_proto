#ifndef _TEST_DATA_DEPENDENCY_PRINTER_HPP
#define _TEST_DATA_DEPENDENCY_PRINTER_HPP
#include <iostream>

// printer module
#include "Printer.hpp"
#include "TestDataDependency.hpp"

// inject custom struct type and tag at compile-time
namespace fractals {
namespace traits {
namespace detail {
struct TestDataDependency_tag {};
template <>
struct classify<TestDataDependency> {
  using type = TestDataDependency_tag;
};
// struct TestDataDependency_tag {};
// template <>
// struct classify<TestDataDependency_t> {
//   using type = TestDataDependency_tag;
// };
};  // namespace detail
};  // namespace traits
};  // namespace fractals

namespace printer {
inline std::ostream& print(std::ostream& os, const TestDataDependency& object,
                           fractals::traits::detail::TestDataDependency_tag)
{
  os << "tagged dispatch for struct type TestDataDependency\n";

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

  printer::print(os, object.char_v, fractals::traits::classify_t<decltype(object.char_v)>{}) << "\n";
  printer::print(os, object.char_null_v, fractals::traits::classify_t<decltype(object.char_null_v)>{}) << "\n";

  printer::print(os, object.bool_true_v, fractals::traits::classify_t<decltype(object.bool_true_v)>{}) << "\n";

  printer::print(os, object.const_char_v, fractals::traits::classify_t<decltype(object.const_char_v)>{}) << "\n";
  printer::print(os, object.ptr_v, fractals::traits::classify_t<decltype(object.ptr_v)>{}) << "\n";
  printer::print(os, object.nullptr_v, fractals::traits::classify_t<decltype(object.nullptr_v)>{}) << "\n";
  printer::print(os, object.nullptr_t_v, fractals::traits::classify_t<decltype(object.nullptr_t_v)>{}) << "\n";
  printer::print(os, nullptr, fractals::traits::classify_t<decltype(nullptr)>{}) << "\n";
  printer::print(os, object.void_ptr_v, fractals::traits::classify_t<decltype(object.void_ptr_v)>{}) << "\n";

  printer::print(os, object.c_array_v, fractals::traits::classify_t<decltype(object.c_array_v)>{}) << "\n";
  printer::print(os, object.c_char_array_v, fractals::traits::classify_t<decltype(object.c_char_array_v)>{}) << "\n";

  printer::print(os, object.enum_v, fractals::traits::classify_t<decltype(object.enum_v)>{}) << std::endl;

  printer::print(os, object.union_v, fractals::traits::classify_t<decltype(object.union_v)>{}) << std::endl;

  // does not have a struct dep

  return os;
}
};  // namespace printer
inline std::ostream& operator<<(std::ostream& os, const TestDataDependency& object)
{
  os << "operator << entry point for struct type TestDataDependency\n";
  // TODO(fractals): trait system needs to be able to handle const qualifiers
  // and references etc
  return printer::print(os, object, fractals::traits::classify_t<std::decay_t<decltype(object)>>{});
}
#endif
