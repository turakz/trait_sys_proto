#ifndef _PRINTER_HPP
#define _PRINTER_HPP
#include <iostream>

#include "lib/FractalsTraits.hpp"

namespace printer {
// catch-all for unimplemented `T`
template <typename T>
std::ostream& print(std::ostream& os, const T& value, fractals::traits::detail::unsupported_tag)
{
  return (os << "unsupported dispatch: [unsupported type]");
}

// int8_t dispatches
inline std::ostream& print(std::ostream& os, const std::int8_t value, fractals::traits::detail::int8_tag)
{
  // cast to prevent printing as `char`
  return (os << "int8_t dispatch: " << static_cast<int>(value));
}

inline std::ostream& print(std::ostream& os, const std::uint8_t value, fractals::traits::detail::uint8_tag)
{
  return (os << "uint8_t dispatch: " << static_cast<unsigned int>(value));
}

// int16_t dispatches
inline std::ostream& print(std::ostream& os, const std::int16_t value, fractals::traits::detail::int16_tag)
{
  return (os << "int16_t dispatch: " << value);
}

inline std::ostream& print(std::ostream& os, const std::uint16_t value, fractals::traits::detail::uint16_tag)
{
  return (os << "uint16_t dispatch: " << value);
}

// int32_t dispatches (int is aliased as in32_t on most platforms)
inline std::ostream& print(std::ostream& os, const int32_t value, fractals::traits::detail::int32_tag)
{
  return (os << "int32_t dispatch: " << value);
}

inline std::ostream& print(std::ostream& os, const uint32_t value, fractals::traits::detail::uint32_tag)
{
  return (os << "uint32_t dispatch: " << value);
}

// int64_t dispatches (long is aliased as int64_t on most platforms)
inline std::ostream& print(std::ostream& os, const std::int64_t value, fractals::traits::detail::int64_tag)
{
  return (os << "int64_t dispatch: " << value);
}

inline std::ostream& print(std::ostream& os, const std::uint64_t value, fractals::traits::detail::uint64_tag)
{
  return (os << "uint64_t dispatch: " << value);
}

// long long dispatches (no alias here)
inline std::ostream& print(std::ostream& os, const long long value, fractals::traits::detail::longlong_tag)
{
  return (os << "long long dispatch: " << value);
}

inline std::ostream& print(std::ostream& os, const unsigned long long value, fractals::traits::detail::ulonglong_tag)
{
  return (os << "unsigned long long dispatch: " << value);
}

// bool dispatch
inline std::ostream& print(std::ostream& os, const bool value, fractals::traits::detail::bool_tag)
{
  return (os << "bool dispatch: " << (value ? "true" : "false"));
}

// char dispatches
inline std::ostream& print(std::ostream& os, const char value, fractals::traits::detail::char_tag)
{
  return (os << "char dispatch: \'" << value << "\'");
}

inline std::ostream& print(std::ostream& os, const char* value, fractals::traits::detail::const_char_tag)
{
  return (os << "const char* dispatch: \"" << value << "\"");
}

// ptr dispatches
template <typename T>
std::ostream& print(std::ostream& os, const T* value, fractals::traits::detail::ptr_tag)
{
  os << "ptr dispatch: " << value << " -> ";
  if (value)
  {
    os << (*value);
  }
  else
  {
    os << "nullptr";
  }
  return os;
}

inline std::ostream& print(std::ostream& os, const std::nullptr_t value, fractals::traits::detail::nullptr_tag)
{
  return (os << "nullptr_t dispatch: " << value);
}

inline std::ostream& print(std::ostream& os, const void* value, fractals::traits::detail::void_ptr_tag)
{
  return (os << "void ptr dispatch: " << value);
}

template <typename T, std::size_t Extent>
std::ostream& print(std::ostream& os, const T (&arr)[Extent], fractals::traits::detail::c_array_tag)
{
  os << "c_array dispatch: " << arr << " -> {";
  for (std::size_t idx = 0; idx < Extent; ++idx)
  {
    os << arr[idx];
    if (idx + 1 != Extent)
    {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

template <typename T>
std::ostream& print(std::ostream& os, const T& value, fractals::traits::detail::enum_tag)
{
  return (os << "enum dispatch: " << value);  // how do enums work? can they be expanded easily or need printer?
}

// union
template <typename T>
std::ostream& print(std::ostream& os, const T& value, fractals::traits::detail::union_tag)
{
  return (os << "union dispatch: [union]");  // union needs a printer to resolve
                                             // its value
}

};  // namespace printer
#endif
