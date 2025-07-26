#ifndef _FRACTALS_PRINTER_HPP
#define _FRACTALS_PRINTER_HPP
#include <cstring>
#include <ostream>
#include "FractalsTraits.hpp"
namespace fractals {
namespace printer {
// simple print impl
template <typename T_Value>
inline std::ostream& simplesimple_print(std::ostream& os, const T_Value& value, const char* label, std::size_t spaceCount)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << value);
  }
  return (os << label << ": " << value);
}
// catch-all for unimplemented `T`
template <typename T>
std::ostream& print(std::ostream& os, const T& /*value*/, const char* label, std::size_t spaceCount,
                    fractals::traits::detail::unsupported_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << "[unsupported type]");
  }
  return (os << label << ": [unsupported type]");
}
// int8_t dispatches (promoted to int for printing)
inline std::ostream& print(std::ostream& os, const int8_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::int8_tag)
{
  return simple_print(os, static_cast<int>(value), label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const uint8_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::uint8_tag)
{
  return simple_print(os, static_cast<unsigned int>(value), label, spaceCount);
}
// int16_t dispatches
inline std::ostream& print(std::ostream& os, const int16_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::int16_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const uint16_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::uint16_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// int32_t dispatches
inline std::ostream& print(std::ostream& os, const int32_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::int32_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const uint32_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::uint32_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// int64_t dispatches
inline std::ostream& print(std::ostream& os, const int64_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::int64_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const uint64_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::uint64_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// platform-specific/compiler-specific dispatches
inline std::ostream& print(std::ostream& os, const long value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::long_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const unsigned long value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::ulong_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const wchar_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::wchar_tag)
{
  // wchar_t prints its numeric value by default to std::ostream
  return simple_print(os, static_cast<long>(value), label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const size_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::size_t_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const ptrdiff_t value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::ptrdiff_t_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// overlapping dispatches
inline std::ostream& print(std::ostream& os, const long long value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::longlong_tag)
{
  return simple_print(os, value, label, spaceCount);
}

inline std::ostream& print(std::ostream& os, const unsigned long long value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::ulonglong_tag)
{
  return simple_print(os, value, label, spaceCount);
}

inline std::ostream& print(std::ostream& os, const long double value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::long_double_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// distinct dispatches (generally)
inline std::ostream& print(std::ostream& os, const bool value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::bool_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << std::boolalpha << value << std::noboolalpha);
  }
  return (os << label << ": " << std::boolalpha << value << std::noboolalpha);
}
// char dispatches
inline std::ostream& print(std::ostream& os, const char value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::char_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << "\'" << value << "\'");
  }
  return (os << label << ": \'" << value << "\'");
}
inline std::ostream& print(std::ostream& os, const char* value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::const_char_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << "\"" << (value ? value : "(null)") << "\"");
  }
  return (os << label << ": \"" << (value ? value : "(null)") << "\"");
}
inline std::ostream& print(std::ostream& os, const float value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::float_tag)
{
  return simple_print(os, value, label, spaceCount);
}
inline std::ostream& print(std::ostream& os, const double value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::double_tag)
{
  return simple_print(os, value, label, spaceCount);
}
// ptr dispatches: void ptr, data ptr, func ptr
inline std::ostream& print(std::ostream& os, const void* value, const char* label, std::size_t spaceCount,
                           fractals::traits::detail::void_ptr_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << value << " -> void");
  }
  return (os << label << ": " << value << " -> void");
}
template <typename T>
std::ostream& print(std::ostream& os, const T* value, const char* label, std::size_t spaceCount,
                    fractals::traits::detail::ptr_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    os << value << " -> ";
  }
  else
  {
    os << label << ": " << value << " -> ";
  }
  if (value)
  {
    os << (*value);
  }
  else
  {
    os << "NULL";
  }
  return os;
}
template <typename T>
std::ostream& print(std::ostream& os, const T& value, const char* label, std::size_t spaceCount,
                    fractals::traits::detail::func_ptr_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << reinterpret_cast<const void*>(value) << " -> [func_ptr]");
  }
  return (os << label << ": " << reinterpret_cast<const void*>(value) << " -> [func_ptr]");
}
// c-array dispatch
template <typename T, std::size_t Extent>
std::ostream& print(std::ostream& os, const T (&arr)[Extent], const char* label, std::size_t spaceCount,
                    fractals::traits::detail::c_array_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    // cast to void* to ensure address is printed for char arrays, not string content
    os << static_cast<const void*>(arr) << "{";
  }
  else
  {
    os << label << ": " << static_cast<const void*>(arr) << " -> {";
  }
  for (std::size_t idx = 0; idx < Extent; ++idx)
  {
    os << arr[idx];
    if (idx + 1 != Extent)
    {
      os << ", ";
    }
  }
  return os << "}";
}
// enum dispatch
template <typename T>
std::ostream& print(std::ostream& os, const T& value, const char* label, std::size_t spaceCount,
                    fractals::traits::detail::enum_tag)
{
  return simple_print(os, static_cast<typename std::underlying_type<T>::type>(value), label, spaceCount);
}
// union dispatch
template <typename T>
std::ostream& print(std::ostream& os, const T& /*value*/, const char* label, std::size_t spaceCount,
                    fractals::traits::detail::union_tag)
{
  if ((std::strcmp(label, "") == 0) && spaceCount == 0)
  {
    return (os << "[union]");
  }
  return (os << label << ": [union]");
}
// default dispatch
template <typename T>
std::ostream& print(std::ostream& os, const T& value, const char* label = "", std::size_t spaceCount = 0)
{
  return fractals::printer::print(os, value, label, spaceCount, fractals::traits::classify_t<T>{});
}
}; // namespace printer
}; // namespace fractals
#endif
